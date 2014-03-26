#ifndef DATATREEWIDGETITEM_H
#define DATATREEWIDGETITEM_H
///
/// \brief The DataTreeWidgetItem class
/// manage the widget item
///
#include <QTreeWidgetItem>
class DataTreeWidget;
class QString;
class QCheckBox;
class QLabel;

class DataTreeWidgetItem:public QTreeWidgetItem
{
public:
    DataTreeWidgetItem(DataTreeWidget* parent);
    DataTreeWidgetItem(DataTreeWidgetItem* parent);
    virtual ~DataTreeWidgetItem();
    void setText(QString& text);

protected:
    /*whether leaf node or not*/
    bool leaf;

    DataTreeWidget* m_treeWidget;
    DataTreeWidgetItem* m_parent;
    QLabel* m_titleLabel;
    QString* m_text;
    QCheckBox* m_checkbox;
    bool m_exclusive;
public:
    bool isLeaf()const{
        return leaf;
    }

    void setExclusive(bool ex){
        m_exclusive = ex;
    }

    bool isExclusive(){
        return m_exclusive;
    }
};

#endif // DATATREEWIDGETITEM_H
