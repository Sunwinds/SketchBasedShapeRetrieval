/****************************************************************************
** Meta object code from reading C++ file 'QuickMesh.h'
**
** Created: Tue Apr 16 02:08:19 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MeshViewer/QuickMesh.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QuickMesh.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QuickMesh[] = {

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
      19,   11,   10,   10, 0x0a,
      33,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QuickMesh[] = {
    "QuickMesh\0\0fileame\0load(QString)\0"
    "clear()\0"
};

void QuickMesh::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QuickMesh *_t = static_cast<QuickMesh *>(_o);
        switch (_id) {
        case 0: _t->load((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->clear(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QuickMesh::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QuickMesh::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QuickMesh,
      qt_meta_data_QuickMesh, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QuickMesh::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QuickMesh::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QuickMesh::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QuickMesh))
        return static_cast<void*>(const_cast< QuickMesh*>(this));
    return QObject::qt_metacast(_clname);
}

int QuickMesh::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
