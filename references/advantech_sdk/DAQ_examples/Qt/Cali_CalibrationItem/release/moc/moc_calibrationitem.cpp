/****************************************************************************
** Meta object code from reading C++ file 'calibrationitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.18)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../calibrationitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calibrationitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalibrationItem_t {
    QByteArrayData data[19];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalibrationItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalibrationItem_t qt_meta_stringdata_CalibrationItem = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CalibrationItem"
QT_MOC_LITERAL(1, 16, 19), // "update_state_signal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 3), // "idx"
QT_MOC_LITERAL(4, 41, 9), // "CaliState"
QT_MOC_LITERAL(5, 51, 5), // "state"
QT_MOC_LITERAL(6, 57, 17), // "update_val_signal"
QT_MOC_LITERAL(7, 75, 5), // "value"
QT_MOC_LITERAL(8, 81, 18), // "ButtonStartClicked"
QT_MOC_LITERAL(9, 100, 17), // "ButtonStopClicked"
QT_MOC_LITERAL(10, 118, 22), // "ButtonConfigureClicked"
QT_MOC_LITERAL(11, 141, 17), // "ButtonSaveClicked"
QT_MOC_LITERAL(12, 159, 14), // "SpinBoxClicked"
QT_MOC_LITERAL(13, 174, 9), // "onCmbSect"
QT_MOC_LITERAL(14, 184, 9), // "onCmbSubj"
QT_MOC_LITERAL(15, 194, 11), // "TimerTicked"
QT_MOC_LITERAL(16, 206, 12), // "TimerTicked1"
QT_MOC_LITERAL(17, 219, 15), // "on_update_state"
QT_MOC_LITERAL(18, 235, 15) // "on_update_value"

    },
    "CalibrationItem\0update_state_signal\0"
    "\0idx\0CaliState\0state\0update_val_signal\0"
    "value\0ButtonStartClicked\0ButtonStopClicked\0"
    "ButtonConfigureClicked\0ButtonSaveClicked\0"
    "SpinBoxClicked\0onCmbSect\0onCmbSubj\0"
    "TimerTicked\0TimerTicked1\0on_update_state\0"
    "on_update_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalibrationItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       6,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   87,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    0,   90,    2, 0x08 /* Private */,
      12,    0,   91,    2, 0x08 /* Private */,
      13,    0,   92,    2, 0x08 /* Private */,
      14,    0,   93,    2, 0x08 /* Private */,
      15,    0,   94,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,
      17,    2,   96,    2, 0x08 /* Private */,
      18,    1,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void CalibrationItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CalibrationItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update_state_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CaliState(*)>(_a[2]))); break;
        case 1: _t->update_val_signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ButtonStartClicked(); break;
        case 3: _t->ButtonStopClicked(); break;
        case 4: _t->ButtonConfigureClicked(); break;
        case 5: _t->ButtonSaveClicked(); break;
        case 6: _t->SpinBoxClicked(); break;
        case 7: _t->onCmbSect(); break;
        case 8: _t->onCmbSubj(); break;
        case 9: _t->TimerTicked(); break;
        case 10: _t->TimerTicked1(); break;
        case 11: _t->on_update_state((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CaliState(*)>(_a[2]))); break;
        case 12: _t->on_update_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CalibrationItem::*)(int , CaliState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationItem::update_state_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CalibrationItem::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalibrationItem::update_val_signal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CalibrationItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CalibrationItem.data,
    qt_meta_data_CalibrationItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CalibrationItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalibrationItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CalibrationItem.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CalibrationItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CalibrationItem::update_state_signal(int _t1, CaliState _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalibrationItem::update_val_signal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
