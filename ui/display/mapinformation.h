#ifndef MAPINFORMATION_H
#define MAPINFORMATION_H

#include <QString>
#include "Constants.h"
#include <QMap>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

// a single bounded part of the province
struct Region
{
    double m_centerX;
    double m_centerY;
    vector<pair<double, double> > m_bound;
};

typedef QMap<QString, vector<Region> > Province;

class MapInformation
{
public:
    static MapInformation *getMapInformationSingleton();

private:
    MapInformation();

public:
    Province m_provinces;

private:
    static MapInformation *m_map;
};

#endif // MAPINFORMATION_H
