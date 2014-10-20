#ifndef MAINWINDOWRIGHTWIDGET_H
#define MAINWINDOWRIGHTWIDGET_H

#include <QWidget>
//主界面右边栏界面

#define _PARAM_JSON_FILE_PATH ":/json/config/param.json"

class MainWindowRightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindowRightWidget(QWidget *parent = 0);

private:
    void init();
    bool loadJsonDocument(const char filename[]);
    void parseParamTree(QJsonObject &jsonObj);
signals:

public slots:

};

#endif // MAINWINDOWRIGHTWIDGET_H
