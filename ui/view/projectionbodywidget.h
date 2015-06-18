#ifndef PROJECTIONBODYWIDGET_H
#define PROJECTIONBODYWIDGET_H

#include <QWidget>
#include <QtWidgets>

class ParamSelectWidget;
class DemoObject;

namespace Ui {
class ProjectionBodyWidget;
}

class ProjectionBodyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectionBodyWidget(QWidget *parent = 0);
    ProjectionBodyWidget(const DemoObject& object, QWidget *parent= 0);
    ~ProjectionBodyWidget();

    QString filename() const;
    bool saveProjection() const;
private:
    void init();
private:
    Ui::ProjectionBodyWidget *ui;

    QLabel *title;
    ParamSelectWidget *paramSelectWidget;
    ParamSelectWidget *dataImportWidget;
};

#endif // PROJECTIONBODYWIDGET_H
