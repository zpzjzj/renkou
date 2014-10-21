#ifndef DATATREEWIDGETLEAF_H
#define DATATREEWIDGETLEAF_H
///
/// \brief The DataTreeWidgetLeaf class
/// leaf node, except for title
/// also including editLine, import button
#include "datatreewidgetitem.h"
class QString;
class QLineEdit;
class QPushButton;
class DataTreeWidgetLeaf:public DataTreeWidgetItem
{
public:
    DataTreeWidgetLeaf(DataTreeWidget *parent);
    ~DataTreeWidgetLeaf();
    void setHref(QString& href);
private:
    QLineEdit* m_path;
    QPushButton* m_importBtn;
};

#endif // DATATREEWIDGETLEAF_H
