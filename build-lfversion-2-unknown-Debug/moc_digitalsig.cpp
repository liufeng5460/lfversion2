/****************************************************************************
** Meta object code from reading C++ file 'digitalsig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lfversion-2/ui/digitalsig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'digitalsig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DigitalSigWindow_t {
    QByteArrayData data[8];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DigitalSigWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DigitalSigWindow_t qt_meta_stringdata_DigitalSigWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DigitalSigWindow"
QT_MOC_LITERAL(1, 17, 14), // "selectSrcFile1"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 14), // "selectSrcFile2"
QT_MOC_LITERAL(4, 48, 14), // "selectSigFile1"
QT_MOC_LITERAL(5, 63, 14), // "selectSigFile2"
QT_MOC_LITERAL(6, 78, 9), // "createSig"
QT_MOC_LITERAL(7, 88, 9) // "verifySig"

    },
    "DigitalSigWindow\0selectSrcFile1\0\0"
    "selectSrcFile2\0selectSigFile1\0"
    "selectSigFile2\0createSig\0verifySig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DigitalSigWindow[] = {

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
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DigitalSigWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DigitalSigWindow *_t = static_cast<DigitalSigWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectSrcFile1(); break;
        case 1: _t->selectSrcFile2(); break;
        case 2: _t->selectSigFile1(); break;
        case 3: _t->selectSigFile2(); break;
        case 4: _t->createSig(); break;
        case 5: _t->verifySig(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DigitalSigWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DigitalSigWindow.data,
      qt_meta_data_DigitalSigWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DigitalSigWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DigitalSigWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DigitalSigWindow.stringdata0))
        return static_cast<void*>(const_cast< DigitalSigWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int DigitalSigWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
