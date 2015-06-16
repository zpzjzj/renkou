#include <QTextCodec>
#include <QProgressDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QMapIterator>
#include <QDebug>
#include "pyramidmodel.h"
#include "../Scheme/SchemeInstance.hpp"

#define NEW_IMPL

PyramidModel::PyramidModel(int sy, int ey, QVector<QString> curve, DataSources files)
{
    m_startYear = sy;
    m_endYear = ey;

    m_maleData.clear();
    m_femaleData.clear();
    m_totalPopulation.clear();
    m_aveAge.clear();
    m_middleAge.clear();
    m_minPopulationAge.clear();
    m_maxPopulationAge.clear();
    m_maxValue = 0;
    m_minValue = 0;

    const size_t MAX_AGE = 110;
    const int size = ey - sy + 1;
    QProgressDialog progress(QObject::tr("读取数据中"), QString(), 0, files.size() * (MAX_AGE + 1) * size);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(1000);
    progress.setMinimumSize(200, 100);

    for(size_t k=0; k<files.size(); ++k){
        QString curvename = curve.at(k);
        vector<vector<double> > v_male(size);
        vector<vector<double> > v_female(size);
        vector<double> v_total(size, 0);
#ifdef NEW_IMPL
        Scheme& scheme = *(files[k]);
        for(size_t i = 2; i <= scheme.getMetadata()->colCount(); ++i) {//for each col
            const int yearOffset = i / 2 - 1;
            auto &arr = (i % 2 == 0) ? v_male[yearOffset] : v_female[yearOffset];
            arr.resize(MAX_AGE + 1);
            auto indicator = scheme.getIndicatorInt(i);
            for(size_t index = 0; index <= MAX_AGE; ++index) {
                double val = indicator.get(index + sy);
                val /= 10000;
                arr[index] = val;
                v_total[index] += val;
                m_maxValue = std::max(m_maxValue, val);
                m_minValue = std::min(m_minValue, val);
            }
            if(i % 2 != 0) {
                progress.setValue((MAX_AGE + 1) * (k * size + i / 2));
            }
        }
#else
        qDebug() << "PyramidModel::PyramidModel" << "k" << k << curvename;
        // 读取数据
        QFile file(files[k]->toInternalName());
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            QMessageBox::warning(0, QObject::tr("错误！"),
                                 QObject::tr("未找到数据文件")+curvename,
                                 QMessageBox::Ok);
            qDebug()<<files[k]->toInternalName();
            continue;
        }
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            int age = line.section(',', 0, 0).toInt();
            int maxYear = line.count(',')/2;
            for(int i=0; i<maxYear; ++i){
                double f = line.section(',', 2*i+1, 2*i+1).toInt();
                double m = line.section(',', 2*i+2, 2*i+2).toInt();
                f /= 10000;         //显示时单位为万人，原始数据要除以10000
                m /= 10000;
                v_male[i].push_back(m);
                v_female[i].push_back(f);
                v_total[i] += f + m;
                m_maxValue = qMax(m_maxValue, f);
                m_maxValue = qMax(m_maxValue, m);
            }
            progress.setValue(k*110+age);
        }
        file.close();
#endif

        m_maleData[curvename] = v_male;
        m_femaleData[curvename] = v_female;
        m_totalPopulation[curvename] = v_total;

        // 计算关键参数
        double sum, popu;
        int minIndex, maxIndex;
        vector<double> v_ave, v_mid;
        vector<int> v_min, v_max;
        v_ave.resize(v_male.size());
        v_mid.resize(v_male.size());
        v_min.resize(v_male.size());
        v_max.resize(v_male.size());

        for(size_t year=0; year<v_male.size(); ++year){
            minIndex = maxIndex = 0;
            sum = 0;
            popu = 0;
            for(size_t age=0; age<v_male[year].size(); ++age){
                if(v_male[year][age] + v_female[year][age] <
                   v_male[year][minIndex] + v_female[year][minIndex])
                    minIndex = age;
                if(v_male[year][age] + v_female[year][age] >
                   v_male[year][maxIndex] + v_female[year][maxIndex])
                    maxIndex = age;
                sum += age * (v_male[year][age] + v_female[year][age]);
                popu += v_male[year][age] + v_female[year][age];
            }
            v_min[year] = minIndex;
            v_max[year] = maxIndex;
            v_ave[year] = sum / popu;
            popu /= 2;
            int age = 0;
            while(popu > 0){
                popu -= v_male[year][age] + v_female[year][age];
                ++age;
            }
            age--;
            v_mid[year] = age + popu/(v_male[year][age]+v_female[year][age]);
        }

        m_aveAge[curvename] = v_ave;
        m_middleAge[curvename] = v_mid;
        m_minPopulationAge[curvename] = v_min;
        m_maxPopulationAge[curvename] = v_max;
    }
}
