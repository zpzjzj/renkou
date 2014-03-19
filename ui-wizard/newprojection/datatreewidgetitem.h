#ifndef DATATREEWIDGETITEM_H
#define DATATREEWIDGETITEM_H
///
/// \brief The DataTreeWidgetItem class
/// manage the widget item
///

class QList;
class QString;

class DataTreeWidgetItem
{
public:
    DataTreeWidgetItem();
    virtual ~DataTreeWidgetItem();

private:
    /*whether leaf node or not*/
    bool leaf;

    DataTreeWidgetItem* m_parent;
    QString* m_text;
    QCheckBox* m_checkbox;
public:
    bool isLeaf()const{
        return leaf;
    }
};

#endif // DATATREEWIDGETITEM_H
