#include "projectionbodywidget.h"
#include "ui_projectionbodywidget.h"

#include "model/demoobject.h"
#include "paramselectwidget.h"
ProjectionBodyWidget::ProjectionBodyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectionBodyWidget)
{
    init();
}

ProjectionBodyWidget::ProjectionBodyWidget(const DemoObject &object, QWidget *parent) {
    paramSelectWidget = new ParamSelectWidget(object, parent);

    QString dataFilePath(":/json/config/dataImport.json");
    dataImportWidget = new ParamSelectWidget(dataFilePath, parent);
    title = new QLabel(object.toString());
    init();
}

ProjectionBodyWidget::~ProjectionBodyWidget()
{
    //TODO crush
    delete ui;

    delete title;
    delete paramSelectWidget;
}

QString ProjectionBodyWidget::filename() const{
    return title->text();
}
bool ProjectionBodyWidget::saveProjection() const {
    return paramSelectWidget->saveAndExportPara();
}
void ProjectionBodyWidget::init() {
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(title);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(dataImportWidget);
    hLayout->addWidget(paramSelectWidget);
    layout->addLayout(hLayout);

    this->setLayout(layout);
}
