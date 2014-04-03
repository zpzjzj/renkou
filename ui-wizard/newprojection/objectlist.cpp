
#include "objectlist.h"
#include <QList>
#include <QtWidgets>

#include "EnumClass.h"
ObjectList::ObjectList(QWidget *parent) :
    QWidget(parent)
{
    objectListWidget = new QListWidget;
    addBtn = new QPushButton(tr("添加"));
    removeBtn = new QPushButton(tr("移除"));
    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->addWidget(addBtn);
    h_layout->addWidget(removeBtn);

    QVBoxLayout *v_layout = new QVBoxLayout;
    v_layout->addWidget(objectListWidget);
    v_layout->addLayout(h_layout);

    setLayout(v_layout);

    connect(objectListWidget, SIGNAL(itemChanged(QListWidgetItem*)),
            this,SLOT(emitListItemChanged(QListWidgetItem*)));
    connect(objectListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(emitListItemClicked(QListWidgetItem*)));

    connect(addBtn, SIGNAL(clicked()), this, SLOT(addBtnClicked()));
    connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeBtnClicked()));
}

void ObjectList::addBtnClicked() {
    QStringList items;
    for (int i=EnumClass::FROM_YEAR; i<=EnumClass::TO_YEAR; i++){
        items << tr("%1").arg(i);
    }

    bool ok;
    QString year = QInputDialog::getItem(this, tr("选择年份和地区"),
                                         tr("年份"), items, 0, false, &ok);
    QString area;
    if (ok && !year.isEmpty()){
        area = QInputDialog::getItem(this, tr("选择年份和地区"),
                                     tr("年份: %1\n地区").arg(year),
                                     EnumClass::ProvinceList, 0,false, &ok);
        if (ok && !area.isEmpty()){
            StudyObject *object = new StudyObject(year.toInt(), EnumClass::NameMap.key(area));


            // if (objects.indexOf(*object) < 0){
            //objects.append(*object);

            QListWidgetItem* item = new QListWidgetItem;
            QString text = year + " " + area;
            item->setText(text);
            objectForItem.insert(object, item);
            objectListWidget->addItem(item);
            //} else {
            //already have
            //}
        }
    } else {

    }
}

void ObjectList::removeBtnClicked(){
    QListWidgetItem *item = objectListWidget->currentItem();
    int ret = QMessageBox::question(this,
                                    tr("确认移除"),
                                    tr("确认移除研究对象 %1").arg(item->text()));
    if (ret == QMessageBox::Yes){
        objectListWidget->takeItem(objectListWidget->currentRow());
    }
    qDebug()<<objectListWidget->currentRow();
}

void ObjectList::emitListItemChanged(QListWidgetItem *item){
    qDebug()<<tr("ObjectList::emitListItemChanged(QListWidgetItem %1)").arg(item->text());
    emit itemChanged(objectForItem.key(item));
}
void ObjectList::emitListItemClicked(QListWidgetItem *item){
    qDebug()<<tr("ObjectList::emitListItemClicked(QListWidgetItem %1)").arg(item->text());
    emit itemClicked(objectForItem.key(item));
}
