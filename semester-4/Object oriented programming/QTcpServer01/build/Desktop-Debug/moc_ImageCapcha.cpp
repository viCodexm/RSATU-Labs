/****************************************************************************
** Meta object code from reading C++ file 'ImageCapcha.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.14)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../capcha/ImageCapcha.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageCapcha.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.14. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageCapcha_t {
    QByteArrayData data[7];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageCapcha_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageCapcha_t qt_meta_stringdata_ImageCapcha = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ImageCapcha"
QT_MOC_LITERAL(1, 12, 16), // "updatePressState"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "QPushButton*"
QT_MOC_LITERAL(4, 43, 6), // "button"
QT_MOC_LITERAL(5, 50, 3), // "row"
QT_MOC_LITERAL(6, 54, 6) // "column"

    },
    "ImageCapcha\0updatePressState\0\0"
    "QPushButton*\0button\0row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageCapcha[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,

       0        // eod
};

void ImageCapcha::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageCapcha *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatePressState((*reinterpret_cast< QPushButton*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPushButton* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageCapcha::staticMetaObject = { {
    QMetaObject::SuperData::link<Capcha::staticMetaObject>(),
    qt_meta_stringdata_ImageCapcha.data,
    qt_meta_data_ImageCapcha,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageCapcha::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageCapcha::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageCapcha.stringdata0))
        return static_cast<void*>(this);
    return Capcha::qt_metacast(_clname);
}

int ImageCapcha::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Capcha::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
