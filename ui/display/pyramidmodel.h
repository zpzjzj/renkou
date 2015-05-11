#ifndef PYRAMIDMODEL_H
#define PYRAMIDMODEL_H

#include <QStringList>
#include <QVector>
#include <QMap>
#include <QColor>
#include <vector>
#include <algorithm>
#include "FileInfo.h"
using namespace std;

struct PyramidModel
{
    PyramidModel(int sy, int ey, QVector<QString> curve, QVector<FileInfo> files);
    QMap<QString, vector<vector<double> > > m_maleData; // String表示曲线名，vector<vector<double>>表示每一年每个年龄的人数
    QMap<QString, vector<vector<double> > > m_femaleData;
    QMap<QString, vector<double> > m_totalPopulation;   // 每年的总人口
    QMap<QString, vector<double> > m_aveAge;    //每年的人口平均年龄
    QMap<QString, vector<double> > m_middleAge; //每年的人口中位数
    QMap<QString, vector<int> > m_minPopulationAge; //每年人口数量最多的年龄
    QMap<QString, vector<int> > m_maxPopulationAge; //每年人口数量最少的年龄
    QMap<QString, QColor> m_color;
    double m_maxValue;              //全部中的最大值
    double m_minValue;              //全部中的最小值
    int m_startYear;
    int m_endYear;
};

#endif // PYRAMIDMODEL_H
