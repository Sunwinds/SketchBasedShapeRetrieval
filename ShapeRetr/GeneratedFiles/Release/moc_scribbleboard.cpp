/****************************************************************************
** Meta object code from reading C++ file 'scribbleboard.h'
**
** Created: Mon Apr 15 01:38:01 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scribbleboard.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scribbleboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScribbleBoard[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      28,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScribbleBoard[] = {
    "ScribbleBoard\0\0clearImage()\0print()\0"
};

void ScribbleBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScribbleBoard *_t = static_cast<ScribbleBoard *>(_o);
        switch (_id) {
        case 0: _t->clearImage(); break;
        case 1: _t->print(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ScribbleBoard::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScribbleBoard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScribbleBoard,
      qt_meta_data_ScribbleBoard, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScribbleBoard::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScribbleBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScribbleBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScribbleBoard))
        return static_cast<void*>(const_cast< ScribbleBoard*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScribbleBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
