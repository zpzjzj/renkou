/*
 * 新建预测界面
 */

#include "projectionmanagement.h"
#include "ui_projectionmanagement.h"

#include "model/yearitemmodel.h"
#include "model/areaitemmodel.h"
#include "model/demoobject.h"

#include "controller/objectlistmanager.h"

#include <QtWidgets>

ProjectionManagement::ProjectionManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectionManagement)
{
    ui->setupUi(this);
    ui->hintLabel->setText(tr("Please set all parameters below in order to create your projecttion"));

    QVBoxLayout *scrollLayout = new QVBoxLayout();

    //limit the start year and the area
    QGroupBox *yearAndAreaBox = new QGroupBox(tr("select the year and area"));

    QLabel *yearLabel = new QLabel(tr("start year"));
    yearLabel->setMaximumWidth(120);

    QComboBox *yearBox = new QComboBox();
    YearItemModel *yearItems = new YearItemModel(this);
    yearBox->setModel(yearItems);
    this->year = yearBox->itemText(0).toInt();

    QLabel *areaLabel = new QLabel(tr("study area"));
    areaLabel->setMaximumWidth(120);

    QComboBox *areaBox = new QComboBox();
    AreaItemModel *areaItems = new AreaItemModel(this);
    areaBox->setModel(areaItems);
    this->area = areaBox->itemText(0);

    QHBoxLayout *yearAndAreaLayout = new QHBoxLayout();
    yearAndAreaLayout->addWidget(yearLabel);
    yearAndAreaLayout->addWidget(yearBox);
    yearAndAreaLayout->addWidget(areaLabel);
    yearAndAreaLayout->addWidget(areaBox);

    yearAndAreaBox->setLayout(yearAndAreaLayout);

    scrollLayout->addWidget(yearAndAreaBox);

    //select the name and the path
    QGroupBox *nameAndPathBox = new QGroupBox(tr("name and path"));

    QHBoxLayout *nameAndPathLayout = new QHBoxLayout();

    QPushButton *nameAndPathButton = new QPushButton(tr("projection name"));
    nameAndPathLayout->addWidget(nameAndPathButton);

    filePathLabel = new QLabel();
    nameAndPathLayout->addWidget(filePathLabel);
    this->reloadData();

    nameAndPathBox->setLayout(nameAndPathLayout);

    scrollLayout->addWidget(nameAndPathBox);

    //if anything more

    ui->scrollAreaWidgetContents->setLayout(scrollLayout);

    //actionss
    connect(nameAndPathButton, SIGNAL(clicked()), this, SLOT(saveProjection()));
    connect(yearBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(yearChanged(QString)));
    connect(areaBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(areaChanged(QString)));

}

ProjectionManagement::~ProjectionManagement()
{
    delete ui;
}

void ProjectionManagement::saveProjection() {
    QString fileName = getFileName(year, area);
    filePath = QFileDialog::getSaveFileName(this, tr("选择保存对象路径"),
                               fileName,
                               tr("Demography Object File (*.dof)"));

    if (filePath != nullptr && filePath.size() > 0) {
        this->filePathLabel->setText(filePath);
    }
}

void ProjectionManagement::yearChanged(QString _year) {
    this->year = _year.toInt();
    reloadData();
}

void ProjectionManagement::areaChanged(QString _area) {
    this->area = _area;
    reloadData();
}

void ProjectionManagement::accept() {
    this->finish();
    QDialog::accept();
}

void ProjectionManagement::finish() {
    DemoObject dObject = DemoObject(year, area);
    dObject.saveToFile(filePath);
    ObjectListManager *instance = ObjectListManager::getInstance();
    instance->addObject(dObject);
}

QString ProjectionManagement::getFileName(int year, const QString area) {
    QString fileName = QVariant(year).toString()
            .append("_")
            .append(area)
            .append(".dof");
    return fileName;
}

void ProjectionManagement::reloadData() {
    QString fileName = getFileName(year, area);
    filePath = QDir::currentPath()
            .append("/")
            .append(fileName);

    QFileInfo info(filePath);
    int existCount = 0;
    while (QFile::exists(filePath)) {
        existCount++;
        filePath = QDir::currentPath()
                .append("/")
                .append(info.baseName())
                .append('_')
                .append(QString::number(existCount))
                .append('.')
                .append(info.suffix());
    }
    this->filePathLabel->setText(filePath);
}
