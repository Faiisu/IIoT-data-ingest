/****************************************************************************
** Meta object code from reading C++ file 'updowncounter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.18)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../updowncounter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updowncounter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UpDownCounter_t {
    QByteArrayData data[10];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpDownCounter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpDownCounter_t qt_meta_stringdata_UpDownCounter = {
    {
QT_MOC_LITERAL(0, 0, 13), // "UpDownCounter"
QT_MOC_LITERAL(1, 14, 11), // "TimerTicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "ButtonStartClicked"
QT_MOC_LITERAL(4, 46, 17), // "ButtonStopClicked"
QT_MOC_LITERAL(5, 64, 22), // "ButtonConfigureClicked"
QT_MOC_LITERAL(6, 87, 23), // "ButtonResetValueClicked"
QT_MOC_LITERAL(7, 111, 15), // "ResetIndexChged"
QT_MOC_LITERAL(8, 127, 16), // "QAbstractButton*"
QT_MOC_LITERAL(9, 144, 20) // "CmbResetValueChanged"

    },
    "UpDownCounter\0TimerTicked\0\0"
    "ButtonStartClicked\0ButtonStopClicked\0"
    "ButtonConfigureClicked\0ButtonResetValueClicked\0"
    "ResetIndexChged\0QAbstractButton*\0"
    "CmbResetValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpDownCounter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,

       0        // eod
};

void UpDownCounter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UpDownCounter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->TimerTicked(); break;
        case 1: _t->ButtonStartClicked(); break;
        case 2: _t->ButtonStopClicked(); break;
        case 3: _t->ButtonConfigureClicked(); break;
        case 4: _t->ButtonResetValueClicked(); break;
        case 5: _t->ResetIndexChged((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 6: _t->CmbResetValueChanged(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UpDownCounter::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_UpDownCounter.data,
    qt_meta_data_UpDownCounter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UpDownCounter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpDownCounter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UpDownCounter.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int UpDownCounter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
