#include <QTextCodec>
#include <QProgressDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include "sequencemodel.h"

#define NEW_IMPL
SequenceModel::SequenceModel(int sy, int ey, QVector<QString> curves, DataSources files)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
#ifdef NEW_IMPL
    auto& first = files.front();
    sy = first.startYear();
    ey = first.endYear();
    m_startYear = sy;
    m_endYear = ey;
    m_datas.clear();
    m_maxValue = 0;
    m_minValue = 0;
    auto const size = ey - sy + 1;
    QProgressDialog progress(QProgressDialog::tr("正在读取数据..."), QString(), 0, files.size() * size);
    progress.setMinimumDuration(1000);//show after 1s
    progress.setMinimumSize(200, 100);
    progress.setModal(Qt::WindowModal);

    int index = 0;
    int count = 0;
    qDebug() << "index" << first.getIndex();
    for (SchemeIndicator<schDouble> &indicator : files) {
        QString curvename = curves[index];
        DataBlock& db = m_datas[curvename];
        db.m_color = Qt::black;
        db.m_averageValue.resize(size);
        db.m_data.resize(size);
        db.m_maxValueYear.resize(size);
        db.m_minValueYear.resize(size);

        for(size_t year = sy; year <= ey; ++year, ++count) {
            size_t i = year - sy;
            db.m_data[i] = indicator.get(year);
            db.m_averageValue[i] = indicator.mean(sy, year);
            db.m_minValueYear[i] = indicator.minYear(sy, year) - sy;
            db.m_maxValueYear[i] = indicator.maxYear(sy, year) - sy;
//            qDebug() << QString("minValueYear[%1]").arg(i) << db.m_minValueYear[i];
//            qDebug() << QString("maxValueYear[%1]").arg(i) << db.m_maxValueYear[i];
//            qDebug() << i << ":" <<
//                        db.m_data[i] << db.m_averageValue[i] << db.m_minValueYear[i] << db.m_maxValueYear[i];
            progress.setValue(count);
        }
        ++index;
    }
/*
    for(auto &key : m_datas.keys()) {
        qDebug() << key;
        auto db = m_datas.value(key);
        for(size_t i = 0; i < size; ++i) {
            qDebug() << i << ":" <<
                        db.m_data[i] << db.m_averageValue[i] << db.m_minValueYear[i] << db.m_maxValueYear[i];
        }
    }
    */

    {
        std::vector<double> doubleArr (files.size());
        std::transform(files.begin(), files.end(),doubleArr.begin(),
                       [sy, ey](const SchemeIndicator<schDouble> &indicator) {
            return indicator.min(sy, ey);
        });
        m_minValue = std::min(m_minValue, *std::min_element(doubleArr.begin(), doubleArr.end()));
        qDebug() << "m_minValue" << m_minValue;

        std::transform(files.begin(), files.end(), doubleArr.begin(),
                       [sy, ey](const SchemeIndicator<schDouble> &indicator) {
            return indicator.max(sy, ey);
        });
        m_maxValue = *std::max_element(doubleArr.begin(), doubleArr.end());
        qDebug() << "m_maxValue" << m_maxValue;
    }

#else
    m_startYear = sy;
    m_endYear = ey;
    m_datas.clear();
    m_maxValue = 0;
    m_minValue = 0;
    QProgressDialog *progress = new QProgressDialog;
    progress->setWindowTitle(QObject::tr("正在读取数据"));
    progress->setCancelButton(0);
    progress->setRange(0, files.size()*(ey-sy));
    progress->setMinimumDuration(0);
    progress->setMinimumSize(200, 100);
    progress->show();

    for(int k=0; k<files.size(); ++k){
        QString curvename = curves.at(k);
        DataBlock db;
        db.m_color = Qt::black;
        db.m_averageValue.resize(ey-sy+1);
        db.m_data.resize(ey-sy+1);
        db.m_maxValueYear.resize(ey-sy+1);
        db.m_minValueYear.resize(ey-sy+1);

        // Read data
        QFile file(files[k].getScheme()->toInternalName());
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(0, QObject::tr("错误！"),
                                 QObject::tr("未找到数据文件")+curvename,
                                 QMessageBox::Ok);
            qDebug()<<files[k].getScheme()->toInternalName();
            continue;
        }
        QTextStream in(&file);
        int index = files[k].getIndex() - 1;
        int year = sy;

        while(!in.atEnd()){
            QString line = in.readLine();
            year = line.section(",", 0, 0).toInt();
            if(year < sy)
                continue;
            if(year > ey)
                continue;

            progress->setValue(k*(ey-sy) + year);
            progress->update();

            QString datastr = line.section(",", index, index);
            qDebug()<<datastr;
            db.m_data[year-sy] = datastr.toDouble();
            if(m_maxValue < db.m_data[year-sy])
                m_maxValue = db.m_data[year-sy];
            if(m_minValue > db.m_data[year-sy])
                m_minValue = db.m_data[year-sy];
        }

        qDebug()<< "minValue" << m_minValue << "maxValue" << m_maxValue;

        // Calculate Key Parameters
        double sum = db.m_data[0];
        int maxyear = 0;
        int minyear = 0;
        db.m_averageValue[0] = sum;
        db.m_maxValueYear[0] = maxyear;
        db.m_minValueYear[0] = minyear;
        for(int i=sy+1; i<=year; ++i){
            double v = db.m_data[i-sy];
            sum += v;
            if(db.m_data[minyear] > v)
                minyear = i-sy;
            if(db.m_data[maxyear] < v)
                maxyear = i-sy;
            db.m_averageValue[i-sy] = sum / (i-sy+1);
            db.m_maxValueYear[i-sy] = maxyear;
            db.m_minValueYear[i-sy] = minyear;
        }

        // 如果读到的数据没有到终止年份，则补全
        for(int i = year+1; i<=ey; ++i){

            progress->setValue(k*(ey-sy) + year);
            progress->update();

            db.m_data[i-sy] = 0;
            db.m_averageValue[i-sy] = 0;
            db.m_maxValueYear[i-sy] = maxyear;
            db.m_minValueYear[i-sy] = minyear;
        }

        progress->setValue((k+1)*(ey-sy));
        progress->update();

        m_datas[curvename] = db;
    }

    progress->hide();
    delete progress;
#endif
}
