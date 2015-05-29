#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <QObject>
#include "mapinformation.h"

MapInformation *MapInformation::m_map = NULL;
QString mapfile = ":/display/data/mapData.txt";

MapInformation::MapInformation()
{
//    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    // open the file and read the map data
    QFile file(mapfile);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"error in MapInformation()"<<mapfile;
        return ;
    }

    QTextStream stream(&file);
    stream.setCodec("GBK");
    QString pname;
    int n;
    m_provinces.clear();

    //reads data for every province
    while(!stream.atEnd()){

        vector<Region> v;
        stream>>pname>>n;
        v.clear();

        //read data for every region in a province
        for(int i=0; i<n; ++i){
            Region r;
            int m;          //number of points
            double px, py;
            stream>>m>>px>>py;
            r.m_centerX = px;
            r.m_centerY = py;
            r.m_bound.clear();
            for(int j=0; j<m; ++j){
                stream>>px>>py;
                r.m_bound.push_back(make_pair(px, py));
            }
            v.push_back(r);
        }
        pname.replace(QObject::tr("省"), "");
        pname.replace(QObject::tr("市"), "");
        m_provinces[pname] = v;

    }//while(!stream.atEnd())

    file.close();
}

MapInformation* MapInformation::getMapInformationSingleton()
{
    if(NULL == m_map){
        m_map = new MapInformation();
    }

    return m_map;
}
