#include "datatreewidgetitem.h"
#include <QtWidgets>
#include <QWidget>
DataTreeWidgetItem::DataTreeWidgetItem(DataTreeWidget *parent)
    :m_treeWidget(parent), m_parent(nullptr)
{
    qDebug()<<"DataTreeWidgetItem::DataTreeWidgetItem(DataTreeWidget *parent)"<<endl;
    m_titleLabel = new QLabel("Title");
    m_text = new QString("Title");
    m_checkbox = new QCheckBox();
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
