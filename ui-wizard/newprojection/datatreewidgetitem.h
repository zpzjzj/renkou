#ifndef DATATREEWIDGETITEM_H
#define DATATREEWIDGETITEM_H
///
/// \brief The DataTreeWidgetItem class
/// manage the widget item
///

class DataTreeWidget;
class QString;
class QCheckBox;

class DataTreeWidgetItem
{
public:
    DataTreeWidgetItem(DataTreeWidget* parent);
    DataTreeWidgetItem(DataTreeWidgetItem* parent);
    virtual ~DataTreeWidgetItem();
    void setText(QString& text);

private:
    /*whether leaf node or not*/
    bool leaf;

    DataTreeWidget* m_treeWidget;
    DataTreeWidgetItem* m_parent;
    QString* m_text;
    QCheckBox* m_checkbox;
    bool exclusive;
public:
    bool isLeaf()const{
        return leaf;
    }

    void setExclusive(bool ex){
        exclusive = ex;
    }

    bool isExclusive(){
        return exclusive;
    }
};

#endif // DATATREEWIDGETITEM_H
