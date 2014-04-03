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
    void itemChanged(StudyObject *object);
    void itemClicked(StudyObject *object);
    void rowChanged(StudyObject *object);
public slots:
private slots:
    void addBtnClicked();
    void removeBtnClicked();
    void emitListItemChanged(QListWidgetItem *item);
    void emitListItemClicked(QListWidgetItem *item);
    void emitRowChanged(int i);
private:
    QListWidget* objectListWidget;
    QHash<StudyObject*, QListWidgetItem*> objectForItem;
    //QList<StudyObject> objects;
    QPushButton* addBtn;
    QPushButton* removeBtn;
};

#endif // OBJECTLIST_H
