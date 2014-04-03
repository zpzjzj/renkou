#ifndef OBJECTLIST_H
#define OBJECTLIST_H

#include <QHash>
#include <QWidget>
#include "studyobject.h"
class StudyObject;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class ObjectList : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectList(QWidget *parent = 0);

signals:
    void itemClicked(StudyObject *object);
public slots:
private slots:
    void addBtnClicked();
    void removeBtnClicked();
    void emitListItemClicked(QListWidgetItem *item);
private:
    QListWidget* objectListWidget;
    QHash<StudyObject*, QListWidgetItem*> objectForItem;
    //QList<StudyObject> objects;
    QPushButton* addBtn;
    QPushButton* removeBtn;
};

#endif // OBJECTLIST_H
