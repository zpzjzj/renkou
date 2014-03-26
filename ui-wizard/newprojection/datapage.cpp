#include<QtWidgets>
#include"datapage.h"
#include "datatreewidget.h"
#include "datatreewidgetleaf.h"

DataPage::DataPage(QWidget *parent)
    :QWizardPage(parent)
{
    setTitle(tr("Class Information"));
    setSubTitle(tr("Specify basic information about the class for which you "
                      "want to generate skeleton source code files."));
    classNameLabel = new QLabel(tr("&Class name:"));
    classNameLineEdit = new QLineEdit;
    classNameLabel->setBuddy(classNameLineEdit);
    baseClassLabel = new QLabel(tr("B&ase class:"));
    baseClassLineEdit = new QLineEdit;
    baseClassLabel->setBuddy(baseClassLineEdit);

    QGridLayout *layout = new QGridLayout;
    DataTreeWidget *tree = new DataTreeWidget();
    DataTreeWidgetLeaf* leaf = new DataTreeWidgetLeaf(tree);
    layout->addWidget(leaf, 0, 0);
//    layout->addWidget(classNameLabel, 0, 0);
//    layout->addWidget(classNameLineEdit, 0, 1);
//    layout->addWidget(baseClassLabel, 1, 0);
//    layout->addWidget(baseClassLineEdit, 1, 1);
    setLayout(layout);
}
