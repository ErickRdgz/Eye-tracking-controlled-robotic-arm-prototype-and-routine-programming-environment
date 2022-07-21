/****************************************************************************
** Meta object code from reading C++ file 'eyetracking.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../InterfazControlOcular/eyetracking.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eyetracking.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EyeTracking_t {
    QByteArrayData data[6];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EyeTracking_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EyeTracking_t qt_meta_stringdata_EyeTracking = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EyeTracking"
QT_MOC_LITERAL(1, 12, 13), // "newVideoFrame"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "moveUp"
QT_MOC_LITERAL(4, 34, 9), // "moveRight"
QT_MOC_LITERAL(5, 44, 8) // "moveLeft"

    },
    "EyeTracking\0newVideoFrame\0\0moveUp\0"
    "moveRight\0moveLeft"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EyeTracking[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EyeTracking::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EyeTracking *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newVideoFrame(); break;
        case 1: _t->moveUp(); break;
        case 2: _t->moveRight(); break;
        case 3: _t->moveLeft(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EyeTracking::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EyeTracking::newVideoFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EyeTracking::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EyeTracking::moveUp)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EyeTracking::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EyeTracking::moveRight)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EyeTracking::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EyeTracking::moveLeft)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject EyeTracking::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_EyeTracking.data,
    qt_meta_data_EyeTracking,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EyeTracking::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EyeTracking::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EyeTracking.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int EyeTracking::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EyeTracking::newVideoFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void EyeTracking::moveUp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void EyeTracking::moveRight()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void EyeTracking::moveLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
