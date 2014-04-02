#include "objectlist.h"
#include "EnumClass.h"
#include "studyobject.h"

#include <QtWidgets>
ObjectList::ObjectList(QWidget *parent) :
    QWidget(parent)
{
    objectList = new QListWidget;
    addBtn = new QPushButton(tr("添加"));
    removeBtn = new QPushButton(tr("移除"));
    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->addWidget(addBtn);
    h_layout->addWidget(removeBtn);

    QVBoxLayout *v_layout = new QVBoxLayout;
    v_layout->addWidget(objectList);
    v_layout->addLayout(h_layout);

    setLayout(v_layout);

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
            StudyObject* object = new StudyObject(year.toInt(), area);

            QListWidgetItem* item = new QListWidgetItem;

            QString text = year + " " + area;
            item->setText(text);
            objectList->addItem(item);
            objectForItem.insert(item, object);
        }
    } else {

    }


}

void ObjectList::removeBtnClicked(){
    QListWidgetItem *item = objectList->currentItem();

    qDebug()<<objectList->currentRow();
}
