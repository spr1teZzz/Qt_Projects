/****************************************************************************
** Meta object code from reading C++ file 'framelesswidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../framelesswidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framelesswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FramelessWidget_t {
    QByteArrayData data[14];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FramelessWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FramelessWidget_t qt_meta_stringdata_FramelessWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "FramelessWidget"
QT_MOC_LITERAL(1, 16, 13), // "titleDblClick"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "windowStateChange"
QT_MOC_LITERAL(4, 49, 3), // "max"
QT_MOC_LITERAL(5, 53, 10), // "setPadding"
QT_MOC_LITERAL(6, 64, 7), // "padding"
QT_MOC_LITERAL(7, 72, 13), // "setMoveEnable"
QT_MOC_LITERAL(8, 86, 10), // "moveEnable"
QT_MOC_LITERAL(9, 97, 15), // "setResizeEnable"
QT_MOC_LITERAL(10, 113, 12), // "resizeEnable"
QT_MOC_LITERAL(11, 126, 11), // "setTitleBar"
QT_MOC_LITERAL(12, 138, 8), // "QWidget*"
QT_MOC_LITERAL(13, 147, 8) // "titleBar"

    },
    "FramelessWidget\0titleDblClick\0\0"
    "windowStateChange\0max\0setPadding\0"
    "padding\0setMoveEnable\0moveEnable\0"
    "setResizeEnable\0resizeEnable\0setTitleBar\0"
    "QWidget*\0titleBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FramelessWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x0a /* Public */,
      11,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void FramelessWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FramelessWidget *_t = static_cast<FramelessWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->titleDblClick(); break;
        case 1: _t->windowStateChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setPadding((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setMoveEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setResizeEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setTitleBar((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FramelessWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramelessWidget::titleDblClick)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FramelessWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramelessWidget::windowStateChange)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject FramelessWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FramelessWidget.data,
      qt_meta_data_FramelessWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FramelessWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FramelessWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FramelessWidget.stringdata0))
        return static_cast<void*>(const_cast< FramelessWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FramelessWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void FramelessWidget::titleDblClick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FramelessWidget::windowStateChange(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
