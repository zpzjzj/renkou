#ifndef MAINWINDOWRIGHTWIDGET_H
#define MAINWINDOWRIGHTWIDGET_H

#include <QWidget>
//主界面右边栏界面

#define _PARAM_JSON_FILE_PATH ":/json/config/param.json"
class ParamSelectionTabWidget;
class QSignalMapper;
class QTabWidget;
class DemoObject;

typedef QMap<QString, QObject*> *ParaWidgetItem;
typedef QList<ParaWidgetItem> *SubParaList;
typedef QList<SubParaList> ParaList;

class ParamSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParamSelectWidget(QString &_filename, QWidget *parent = 0);
    ParamSelectWidget(const DemoObject &object, QWidget *parent = 0);

    bool saveAndExportPara();
private:
    void init();
    bool loadJsonDocument(QString &filename);
    void parseParamTree(int tabIndex, QJsonObject &jsonObj);
    void parseSubItems(int tabIndex, QJsonObject &jsonObj);
    void parseOptions(int tabIndex, QJsonObject &jsonObj);
signals:

public slots:
    void importDataButtonPressed(int index);


private:
//     ParamSelectionTabWidget *tabWidget;

    QString filename;
    QTabWidget *tabWidget;
    ParaList *paraList;
    QList<QWidget*> *buttonList;
    QList<QWidget*> *lineEditList;

    QSignalMapper *signalMapper;
};

#endif // MAINWINDOWRIGHTWIDGET_H
