#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWizardPage>
class DataTreeWidget;
class StudyObject;
class ObjectList;

class DataPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit DataPage(QWidget *parent = 0);
private:
    DataTreeWidget *treeWidget;
    ObjectList *objectList;

    QAction *openAct;
    QAction *saveAsAct;
    QPushButton *testLoad;
signals:
    void fileLoaded(StudyObject* object);

public slots:
    void open(StudyObject* object);
    void saveAs(StudyObject* object);
    void clear();
private:
    void savePath(int year, const QString &area);
    void createActions();
    QHash<StudyObject*, DataTreeWidget*> treeForObject;
};

#endif // DATAPAGE_H
