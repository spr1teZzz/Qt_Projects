/****************************************************************************
** Meta object code from reading C++ file 'QToolButtonDemo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../QToolButtonDemo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QToolButtonDemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QToolButtonDemo_t {
    QByteArrayData data[8];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QToolButtonDemo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QToolButtonDemo_t qt_meta_stringdata_QToolButtonDemo = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QToolButtonDemo"
QT_MOC_LITERAL(1, 16, 18), // "slotToolButtonChat"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 19), // "slotToolButtonDebug"
QT_MOC_LITERAL(4, 56, 19), // "slotToolButtonParam"
QT_MOC_LITERAL(5, 76, 17), // "slotToolButtonLog"
QT_MOC_LITERAL(6, 94, 20), // "slotToolButtonExtern"
QT_MOC_LITERAL(7, 115, 14) // "slotActionShow"

    },
    "QToolButtonDemo\0slotToolButtonChat\0\0"
    "slotToolButtonDebug\0slotToolButtonParam\0"
    "slotToolButtonLog\0slotToolButtonExtern\0"
    "slotActionShow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QToolButtonDemo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QToolButtonDemo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QToolButtonDemo *_t = static_cast<QToolButtonDemo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotToolButtonChat(); break;
        case 1: _t->slotToolButtonDebug(); break;
        case 2: _t->slotToolButtonParam(); break;
        case 3: _t->slotToolButtonLog(); break;
        case 4: _t->slotToolButtonExtern(); break;
        case 5: _t->slotActionShow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QToolButtonDemo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QToolButtonDemo.data,
      qt_meta_data_QToolButtonDemo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QToolButtonDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QToolButtonDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QToolButtonDemo.stringdata0))
        return static_cast<void*>(const_cast< QToolButtonDemo*>(this));
    return QWidget::qt_metacast(_clname);
}

int QToolButtonDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
