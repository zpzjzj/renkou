#ifndef DATATREEWIDGETLEAF_H
#define DATATREEWIDGETLEAF_H
///
/// \brief The DataTreeWidgetLeaf class
/// leaf node, except for title
/// also including editLine, import button

class QLineEdit;
class QPushButton;
class DataTreeWidgetLeaf
{
public:
    DataTreeWidgetLeaf();
private:
    QLineEdit* m_path;
    QPushButton* m_importBtn;
};

#endif // DATATREEWIDGETLEAF_H
