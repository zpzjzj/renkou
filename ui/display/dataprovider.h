#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <QStringList>
#include <QMap>
#include <vector>
#include <algorithm>
#include "FileInfo.h"
#include "../Scheme/Scheme.hpp"
using namespace std;

struct DataProvider
{
    using DataSources = std::vector<SchemeIndicator<schDouble> >;
    DataProvider(int sy, int ey, QStringList curve, DataSources files);
    QMap<QString, vector<double> > m_data;
    double m_minValue;
    double m_maxValue;
    QStringList m_curveName;
    int m_startYear;
    int m_endYear;
};

#endif // DATAPROVIDER_H
