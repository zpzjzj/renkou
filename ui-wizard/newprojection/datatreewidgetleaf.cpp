#include "datatreewidgetleaf.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
DataTreeWidgetLeaf::DataTreeWidgetLeaf()
    :m_path(nullptr)
{
    m_importBtn = new QPushButton(QObject::tr("导入"));
}

DataTreeWidgetLeaf::~DataTreeWidgetLeaf()
{

}

void DataTreeWidgetLeaf::setHref(QString &href)
{
    m_path = new QLineEdit(href);
}
