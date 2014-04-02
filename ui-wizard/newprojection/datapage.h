#ifndef DATAPAGE_H
#define DATAPAGE_H

#include <QWizardPage>
class DataTreeWidget;
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

public slots:
    void open();
    void saveAs(int index);
private:
    void savePath(int year, const QString &area);
    void createActions();
};

#endif // DATAPAGE_H
