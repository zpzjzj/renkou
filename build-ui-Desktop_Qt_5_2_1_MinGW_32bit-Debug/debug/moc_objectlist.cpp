/****************************************************************************
** Meta object code from reading C++ file 'objectlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ui/objectlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ObjectList_t {
    QByteArrayData data[15];
    char stringdata[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ObjectList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ObjectList_t qt_meta_stringdata_ObjectList = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 12),
QT_MOC_LITERAL(4, 37, 6),
QT_MOC_LITERAL(5, 44, 11),
QT_MOC_LITERAL(6, 56, 10),
QT_MOC_LITERAL(7, 67, 13),
QT_MOC_LITERAL(8, 81, 16),
QT_MOC_LITERAL(9, 98, 19),
QT_MOC_LITERAL(10, 118, 16),
QT_MOC_LITERAL(11, 135, 4),
QT_MOC_LITERAL(12, 140, 19),
QT_MOC_LITERAL(13, 160, 14),
QT_MOC_LITERAL(14, 175, 1)
    },
    "ObjectList\0itemChanged\0\0StudyObject*\0"
    "object\0itemClicked\0rowChanged\0"
    "addBtnClicked\0removeBtnClicked\0"
    "emitListItemChanged\0QListWidgetItem*\0"
    "item\0emitListItemClicked\0emitRowChanged\0"
    "i\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObjectList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06,
       5,    1,   57,    2, 0x06,
       6,    1,   60,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    0,   63,    2, 0x08,
       8,    0,   64,    2, 0x08,
       9,    1,   65,    2, 0x08,
      12,    1,   68,    2, 0x08,
      13,    1,   71,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void ObjectList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ObjectList *_t = static_cast<ObjectList *>(_o);
        switch (_id) {
        case 0: _t->itemChanged((*reinterpret_cast< StudyObject*(*)>(_a[1]))); break;
        case 1: _t->itemClicked((*reinterpret_cast< StudyObject*(*)>(_a[1]))); break;
        case 2: _t->rowChanged((*reinterpret_cast< StudyObject*(*)>(_a[1]))); break;
        case 3: _t->addBtnClicked(); break;
        case 4: _t->removeBtnClicked(); break;
        case 5: _t->emitListItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->emitListItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->emitRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< StudyObject* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< StudyObject* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< StudyObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ObjectList::*_t)(StudyObject * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObjectList::itemChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (ObjectList::*_t)(StudyObject * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObjectList::itemClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (ObjectList::*_t)(StudyObject * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObjectList::rowChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ObjectList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ObjectList.data,
      qt_meta_data_ObjectList,  qt_static_metacall, 0, 0}
};


const QMetaObject *ObjectList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObjectList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ObjectList.stringdata))
        return static_cast<void*>(const_cast< ObjectList*>(this));
    return QWidget::qt_metacast(_clname);
}

int ObjectList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ObjectList::itemChanged(StudyObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ObjectList::itemClicked(StudyObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ObjectList::rowChanged(StudyObject * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
