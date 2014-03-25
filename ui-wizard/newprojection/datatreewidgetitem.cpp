#include "datatreewidgetitem.h"
#include <QWidget>
DataTreeWidgetItem::DataTreeWidgetItem(DataTreeWidget *parent)
    :m_treeWidget(parent)
{

}

DataTreeWidgetItem::DataTreeWidgetItem(DataTreeWidgetItem *parent)
    :m_parent(parent)
{
}

DataTreeWidgetItem::~DataTreeWidgetItem()
{

}

void DataTreeWidgetItem::setText(QString &text){
    if (m_text != nullptr){
        delete m_text;
        m_text = nullptr;
    }

    m_text = new QString(text);
}
