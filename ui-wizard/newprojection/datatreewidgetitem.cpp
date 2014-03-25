#include "datatreewidgetitem.h"
#include <QWidget>
DataTreeWidgetItem::DataTreeWidgetItem()
{
}

void DataTreeWidgetItem::setText(QString &text){
    if (m_text != nullptr){
        delete m_text;
        m_text = nullptr;
    }

    m_text = new QString(text);
}
