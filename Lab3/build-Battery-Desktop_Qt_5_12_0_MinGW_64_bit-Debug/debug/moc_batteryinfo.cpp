/****************************************************************************
** Meta object code from reading C++ file 'batteryinfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Battery/batteryinfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'batteryinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BatteryInfo_t {
    QByteArrayData data[7];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BatteryInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BatteryInfo_t qt_meta_stringdata_BatteryInfo = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BatteryInfo"
QT_MOC_LITERAL(1, 12, 16), // "sendTypeOfEnergy"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "type"
QT_MOC_LITERAL(4, 35, 15), // "sendChargeValue"
QT_MOC_LITERAL(5, 51, 5), // "value"
QT_MOC_LITERAL(6, 57, 20) // "sendTypeOfEnergySave"

    },
    "BatteryInfo\0sendTypeOfEnergy\0\0type\0"
    "sendChargeValue\0value\0sendTypeOfEnergySave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BatteryInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       6,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::UChar,    5,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void BatteryInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BatteryInfo *_t = static_cast<BatteryInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendTypeOfEnergy((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendChargeValue((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 2: _t->sendTypeOfEnergySave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BatteryInfo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatteryInfo::sendTypeOfEnergy)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BatteryInfo::*)(unsigned char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatteryInfo::sendChargeValue)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BatteryInfo::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BatteryInfo::sendTypeOfEnergySave)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BatteryInfo::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_BatteryInfo.data,
    qt_meta_data_BatteryInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BatteryInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BatteryInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BatteryInfo.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int BatteryInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BatteryInfo::sendTypeOfEnergy(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BatteryInfo::sendChargeValue(unsigned char _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BatteryInfo::sendTypeOfEnergySave(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
