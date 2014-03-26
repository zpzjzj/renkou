#include "datatreewidgetleaf.h"
#include <QtWidgets>
DataTreeWidgetLeaf::DataTreeWidgetLeaf(DataTreeWidget* parent)
    : DataTreeWidgetItem(parent)
{
    qDebug()<<"DataTreeWidgetLeaf::DataTreeWidgetLeaf(DataTreeWidget* parent)"<<endl;
    m_importBtn = new QPushButton(QObject::tr("导入"));
    m_path = new QLineEdit();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_path);
    layout->addWidget(m_importBtn);

    QWidget::setLayout(layout);

}

DataTreeWidgetLeaf::~DataTreeWidgetLeaf()
{

}


void DataTreeWidgetLeaf::setHref(QString &href)
{
    m_path = new QLineEdit(href);
}
