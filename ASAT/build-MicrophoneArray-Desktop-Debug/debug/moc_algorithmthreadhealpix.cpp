/****************************************************************************
** Meta object code from reading C++ file 'algorithmthreadhealpix.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ASAT/algorithmthreadhealpix.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'algorithmthreadhealpix.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_algorithmthreadhealpix_t {
    QByteArrayData data[10];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_algorithmthreadhealpix_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_algorithmthreadhealpix_t qt_meta_stringdata_algorithmthreadhealpix = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 10),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 7),
QT_MOC_LITERAL(4, 43, 7),
QT_MOC_LITERAL(5, 51, 8),
QT_MOC_LITERAL(6, 60, 5),
QT_MOC_LITERAL(7, 66, 8),
QT_MOC_LITERAL(8, 75, 2),
QT_MOC_LITERAL(9, 78, 2)
    },
    "algorithmthreadhealpix\0Calculated\0\0"
    "locsize\0double*\0Pressure\0bool*\0putvalue\0"
    "Az\0El"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_algorithmthreadhealpix[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6, 0x80000000 | 4, 0x80000000 | 4,    3,    5,    7,    8,    9,

       0        // eod
};

void algorithmthreadhealpix::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        algorithmthreadhealpix *_t = static_cast<algorithmthreadhealpix *>(_o);
        switch (_id) {
        case 0: _t->Calculated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< bool*(*)>(_a[3])),(*reinterpret_cast< double*(*)>(_a[4])),(*reinterpret_cast< double*(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (algorithmthreadhealpix::*_t)(int , double * , bool * , double * , double * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&algorithmthreadhealpix::Calculated)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject algorithmthreadhealpix::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_algorithmthreadhealpix.data,
      qt_meta_data_algorithmthreadhealpix,  qt_static_metacall, 0, 0}
};


const QMetaObject *algorithmthreadhealpix::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *algorithmthreadhealpix::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_algorithmthreadhealpix.stringdata))
        return static_cast<void*>(const_cast< algorithmthreadhealpix*>(this));
    return QThread::qt_metacast(_clname);
}

int algorithmthreadhealpix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void algorithmthreadhealpix::Calculated(int _t1, double * _t2, bool * _t3, double * _t4, double * _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
