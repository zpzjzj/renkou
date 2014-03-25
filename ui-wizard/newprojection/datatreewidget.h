#ifndef DATATREEWIDGET_H
#define DATATREEWIDGET_H
class QWidget;
class DataTreeWidget
{
public:
    DataTreeWidget();
    QWidget *window()const {return m_window;}
private:
    QWidget *m_window;
};

#endif // DATATREEWIDGET_H
