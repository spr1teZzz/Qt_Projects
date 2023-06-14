/****************************************************************************
** Meta object code from reading C++ file 'screenwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../screenwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScreenWidget_t {
    QByteArrayData data[9];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenWidget_t qt_meta_stringdata_ScreenWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ScreenWidget"
QT_MOC_LITERAL(1, 13, 18), // "colorwidget_signal"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "mainShow_signal"
QT_MOC_LITERAL(4, 49, 10), // "saveScreen"
QT_MOC_LITERAL(5, 60, 14), // "saveFullScreen"
QT_MOC_LITERAL(6, 75, 15), // "saveScreenOther"
QT_MOC_LITERAL(7, 91, 13), // "saveFullOther"
QT_MOC_LITERAL(8, 105, 4) // "quit"

    },
    "ScreenWidget\0colorwidget_signal\0\0"
    "mainShow_signal\0saveScreen\0saveFullScreen\0"
    "saveScreenOther\0saveFullOther\0quit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScreenWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScreenWidget *_t = static_cast<ScreenWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorwidget_signal(); break;
        case 1: _t->mainShow_signal(); break;
        case 2: _t->saveScreen(); break;
        case 3: _t->saveFullScreen(); break;
        case 4: _t->saveScreenOther(); break;
        case 5: _t->saveFullOther(); break;
        case 6: _t->quit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScreenWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenWidget::colorwidget_signal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ScreenWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenWidget::mainShow_signal)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ScreenWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScreenWidget.data,
      qt_meta_data_ScreenWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScreenWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenWidget.stringdata0))
        return static_cast<void*>(const_cast< ScreenWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScreenWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ScreenWidget::colorwidget_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ScreenWidget::mainShow_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
