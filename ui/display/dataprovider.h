#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QStringList>
#include <QVector>
#include <QMap>
#include <vector>
#include <algorithm>
#include "FileInfo.h"
using namespace std;

struct DataProvider
{
    DataProvider(int sy, int ey, QStringList curve, QVector<FileInfo> files);
    QMap<QString, vector<double> > m_data;
    double m_minValue;
    double m_maxValue;
    QStringList m_curveName;
    int m_startYear;
    int m_endYear;
};

#endif // DATAPROVIDER_H
