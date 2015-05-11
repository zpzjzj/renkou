#include <QTextCodec>
#include <QProgressDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "sequencemodel.h"

SequenceModel::SequenceModel(int sy, int ey, QVector<QString> curves, QVector<FileInfo> files)
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

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
        QFile file(files[k].m_FileName);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(0, QObject::tr("错误！"),
                                 QObject::tr("未找到数据文件")+curvename,
                                 QMessageBox::Ok);
            qDebug()<<files[k].m_FileName;
            continue;
        }
        QTextStream in(&file);
        int index = files[k].m_index;
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
//            qDebug()<<datastr;
            db.m_data[year-sy] = datastr.toDouble();
            if(m_maxValue < db.m_data[year-sy])
                m_maxValue = db.m_data[year-sy];
            if(m_minValue > db.m_data[year-sy])
                m_minValue = db.m_data[year-sy];
        }

//        qDebug()<<m_minValue<<m_maxValue;

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
}
