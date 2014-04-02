#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include <QHash>
#include <QWidget>

class StudyObject;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class ObjectList : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectList(QWidget *parent = 0);
    enum {

    } Distrct;

signals:

public slots:
private slots:
    void addBtnClicked();
    void removeBtnClicked();
private:
    QListWidget* objectList;
    QHash<QListWidgetItem*, StudyObject*> objectForItem;

    QPushButton* addBtn;
    QPushButton* removeBtn;
};

#endif // OBJECTLIST_H
