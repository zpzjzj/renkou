#include "datatreemodel.h"

DataTreeModel::DataTreeModel(QObject * parent = 0)
    :QStandardItemModel(parent)
{
    setHorizontalHeaderLabels(QStringList()
                              <<tr("字段名称")
                              <<tr("文件路径")
                              <<tr(" "));

    QStandardItem* itemProject = new QStandardItem(QStringLiteral("项目"));
    this->appendRow(itemProject);
    this->setItem(this->indexFromItem(itemProject).row(),1,new QStandardItem(QStringLiteral("项目信息说明")));
    QStandardItem* itemFolder = new QStandardItem(QIcon(tr(":/res/icon/Checkbox empty 16x16.png")),
                                                        QStringLiteral("文件夹1"));
    itemProject->appendRow(itemFolder);
    itemProject->setChild(itemFolder->index().row(),1,new QStandardItem(QStringLiteral("信息说明")));
    itemProject->setChild(itemFolder->index().row(), 2, new QStandardItem(QStringLiteral("信息说明")));
    itemFolder = new QStandardItem(QStringLiteral("文件夹2"));
    itemProject->appendRow(itemFolder);
    for(int i=0;i<5;++i){
        QStandardItem* itemgroup = new QStandardItem(QStringLiteral("组%1").arg(i+1));
        itemFolder->appendRow(itemgroup);
        for(int j=0;j<(i+1);++j){
            QStandardItem* itemchannel = new QStandardItem(QStringLiteral("频道%1").arg(j+1));
            itemgroup->appendRow(itemchannel);
            itemgroup->setChild(itemchannel->index().row(),1,new QStandardItem(QStringLiteral("频道%1信息说明").arg(j+1)));
        }
    }
    itemProject->setChild(itemFolder->index().row(),1,new QStandardItem(QStringLiteral("文件夹2信息说明")));
    itemProject = new QStandardItem(QStringLiteral("项目2"));
    this->appendRow(itemProject);
}
