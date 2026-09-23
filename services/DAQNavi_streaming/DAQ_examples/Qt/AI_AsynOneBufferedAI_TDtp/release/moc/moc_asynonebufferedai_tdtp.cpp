/****************************************************************************
** Meta object code from reading C++ file 'asynonebufferedai_tdtp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.18)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../asynonebufferedai_tdtp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'asynonebufferedai_tdtp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.18. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AsynOneBufferedAI_TDtp_t {
    QByteArrayData data[14];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AsynOneBufferedAI_TDtp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AsynOneBufferedAI_TDtp_t qt_meta_stringdata_AsynOneBufferedAI_TDtp = {
    {
QT_MOC_LITERAL(0, 0, 22), // "AsynOneBufferedAI_TDtp"
QT_MOC_LITERAL(1, 23, 12), // "UpdateButton"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "UpdateGraph"
QT_MOC_LITERAL(4, 49, 19), // "samplesCountPerChan"
QT_MOC_LITERAL(5, 69, 17), // "updateTriggerFlag"
QT_MOC_LITERAL(6, 87, 17), // "ShiftValueChanged"
QT_MOC_LITERAL(7, 105, 5), // "value"
QT_MOC_LITERAL(8, 111, 15), // "DivValueChanged"
QT_MOC_LITERAL(9, 127, 22), // "ButtonConfigureClicked"
QT_MOC_LITERAL(10, 150, 20), // "ButtonGetDataClicked"
QT_MOC_LITERAL(11, 171, 12), // "ButtonEnable"
QT_MOC_LITERAL(12, 184, 15), // "GraphInitialize"
QT_MOC_LITERAL(13, 200, 11) // "TriggerFlag"

    },
    "AsynOneBufferedAI_TDtp\0UpdateButton\0"
    "\0UpdateGraph\0samplesCountPerChan\0"
    "updateTriggerFlag\0ShiftValueChanged\0"
    "value\0DivValueChanged\0ButtonConfigureClicked\0"
    "ButtonGetDataClicked\0ButtonEnable\0"
    "GraphInitialize\0TriggerFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AsynOneBufferedAI_TDtp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    1,   65,    2, 0x06 /* Public */,
       5,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   69,    2, 0x08 /* Private */,
       8,    1,   72,    2, 0x08 /* Private */,
       9,    0,   75,    2, 0x08 /* Private */,
      10,    0,   76,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    1,   78,    2, 0x08 /* Private */,
      13,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void AsynOneBufferedAI_TDtp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AsynOneBufferedAI_TDtp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->UpdateButton(); break;
        case 1: _t->UpdateGraph((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateTriggerFlag(); break;
        case 3: _t->ShiftValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->DivValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->ButtonConfigureClicked(); break;
        case 6: _t->ButtonGetDataClicked(); break;
        case 7: _t->ButtonEnable(); break;
        case 8: _t->GraphInitialize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->TriggerFlag(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AsynOneBufferedAI_TDtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsynOneBufferedAI_TDtp::UpdateButton)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AsynOneBufferedAI_TDtp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsynOneBufferedAI_TDtp::UpdateGraph)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AsynOneBufferedAI_TDtp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AsynOneBufferedAI_TDtp::updateTriggerFlag)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AsynOneBufferedAI_TDtp::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AsynOneBufferedAI_TDtp.data,
    qt_meta_data_AsynOneBufferedAI_TDtp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AsynOneBufferedAI_TDtp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AsynOneBufferedAI_TDtp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AsynOneBufferedAI_TDtp.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AsynOneBufferedAI_TDtp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void AsynOneBufferedAI_TDtp::UpdateButton()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AsynOneBufferedAI_TDtp::UpdateGraph(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AsynOneBufferedAI_TDtp::updateTriggerFlag()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
