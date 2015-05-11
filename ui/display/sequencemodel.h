#ifndef SEQUENCEMODEL_H
#define SEQUENCEMODEL_H

#include <QVector>
#include <QMap>
#include <QColor>
#include <vector>
#include <algorithm>
#include "FileInfo.h"
using namespace std;

struct DataBlock
{
    vector<double> m_data;              // 每年的数据
    vector<double> m_averageValue;      // 截至当前年的平均值
    vector<int> m_minValueYear;         // 截至当前年的最小值
    vector<int> m_maxValueYear;         // 截至当前年的最大值
    QColor m_color;
};

struct SequenceModel
{
    SequenceModel(int sy, int ey, QVector<QString> curves, QVector<FileInfo> files);
    QMap<QString, DataBlock> m_datas;
    double m_minValue;
    double m_maxValue;
    int m_startYear;
    int m_endYear;
};

#endif // SEQUENCEMODEL_H
