#include <QProgressDialog>
#include <QMutableMapIterator>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include <cstring>
#include "dataprovider.h"

#define NEW_IMPL
DataProvider::DataProvider(int sy, int ey, QStringList , DataSources files)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    m_startYear = sy;
    m_endYear = ey;

    const QString province[34] = {
        QObject::tr("北京"),
        QObject::tr("天津"),
        QObject::tr("上海"),
        QObject::tr("重庆"),
        QObject::tr("河北"),
        QObject::tr("河南"),
        QObject::tr("云南"),
        QObject::tr("辽宁"),
        QObject::tr("黑龙江"),
        QObject::tr("湖南"),
        QObject::tr("安徽"),
        QObject::tr("山东"),
        QObject::tr("新疆"),
        QObject::tr("江苏"),
        QObject::tr("浙江"),
        QObject::tr("江西"),
        QObject::tr("湖北"),
        QObject::tr("广西"),
        QObject::tr("甘肃"),
        QObject::tr("山西"),
        QObject::tr("内蒙古"),
        QObject::tr("陕西"),
        QObject::tr("吉林"),
        QObject::tr("福建"),
        QObject::tr("贵州"),
        QObject::tr("广东"),
        QObject::tr("青海"),
        QObject::tr("西藏"),
        QObject::tr("四川"),
        QObject::tr("宁夏"),
        QObject::tr("海南"),
        QObject::tr("香港"),
        QObject::tr("澳门"),
        QObject::tr("台湾"),
    };

    bool mark[34];
    memset(mark, 0, sizeof mark);

    const int size = ey - sy + 1;
    QProgressDialog progress(QProgressDialog::tr("正在读取数据..."), QString(), 0, size);
    progress.setMinimumDuration(1000);
    progress.setMinimumSize(200, 10);
    progress.setModal(Qt::WindowModal);

    m_maxValue = 0;
    m_minValue = 0;
    m_data.clear();
#ifdef NEW_IMPL
    for(auto& indicator : files) {
        QString name = indicator.getScheme()->getName();
        size_t provinceId = 0;
        for(; provinceId < 34; ++provinceId) {
            if(name.contains(province[provinceId]))
                break;
        }
        progress.setWindowTitle(QProgressDialog::tr("读取 %1 的数据").arg(province[provinceId]));
        progress.setValue(0);

        auto& qv = m_data[province[provinceId]];
        qv.resize(size);
        for(size_t i = 0; i < size; ++i) {
            qv[i] = indicator[sy + i];
            progress.setValue(i+1);
        }
        m_minValue = std::min(m_minValue, indicator.min(sy, ey));
        m_maxValue = std::max(m_maxValue, indicator.max(sy, ey));
        progress.hide();
        mark[provinceId] = true;
    }
#else
    for(int i=0; i<files.size(); ++i){
        int j;
        for(j=0; j<34; ++j){
            if(files[i].getScheme()->toInternalName().contains(province[j]))
                break;
        }
        if(j == 34){
            qDebug()<<files[i].getScheme()->toInternalName();
        }
        else{
            QString title = QObject::tr("读取") + province[j] + QObject::tr("的数据");
            progress.setWindowTitle(title);
            progress.setRange(0, ey-sy+1);
            progress.setMinimumDuration(0);
            progress.setMinimumSize(200, 10);
            progress.setAcceptDrops(false);
            progress.setValue(0);
            progress.show();

            QString filename = files[i].getScheme()->toInternalName();
            QFile file(filename);
            if(!file.open(QFile::ReadOnly | QFile::Text)){
                qDebug()<<filename<<"doesn't exist";
                continue;
            }

            QTextStream in(&file);
            int index = files[0].getIndex() + 1;
            int year = sy;

            vector<double> qv;
            qv.resize(ey - sy + 1);
            while(!in.atEnd()){
                QString line = in.readLine();
                year = line.section(",", 0, 0).toInt();
                if(year < sy)
                    continue;
                if(year > ey)
                    break;
                QString readdata = line.section(",", index, index);
                double v = readdata.toDouble();
                if(v > m_maxValue)
                    m_maxValue = v;
                else if(v < m_minValue)
                    m_minValue = v;
                qv[year-sy] = v;
                progress.setValue(year-sy+1);
            }
            file.close();

            m_data[province[j]] = qv;
            mark[j] = true;
            progress.hide();
        }//if(j == 34)

    }// for(int i=0; i<files.size(); ++i)
#endif
    for(int i = 0; i < 34; ++i){
        if(!mark[i]){
            auto& qv = m_data[province[i]];
            qv.resize(size);
            std::fill(qv.begin(), qv.end(), 0);
        }
    }

    for(size_t i = 0; i < 34; ++i) {
        if(mark[i]) {
            qDebug() << "province" << province[i];
            auto& v = m_data[province[i]];
            for(auto value : v) {
                qDebug() << value;
            }
        }
    }
    qDebug() << "m_minValue" << m_minValue;
    qDebug() << "m_maxValue" << m_maxValue;
}
