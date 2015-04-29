/****************************************************************************
** Meta object code from reading C++ file 'QuickMeshViewer.h'
**
** Created: Mon Apr 15 01:38:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MeshViewer/QuickMeshViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QuickMeshViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QuickMeshViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      44,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   57,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QuickMeshViewer[] = {
    "QuickMeshViewer\0\0gotFocus(QuickMeshViewer*)\0"
    "meshLoaded()\0fileName\0loadMesh(QString)\0"
};

void QuickMeshViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QuickMeshViewer *_t = static_cast<QuickMeshViewer *>(_o);
        switch (_id) {
        case 0: _t->gotFocus((*reinterpret_cast< QuickMeshViewer*(*)>(_a[1]))); break;
        case 1: _t->meshLoaded(); break;
        case 2: _t->loadMesh((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QuickMeshViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QuickMeshViewer::staticMetaObject = {
    { &QGLViewer::staticMetaObject, qt_meta_stringdata_QuickMeshViewer,
      qt_meta_data_QuickMeshViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QuickMeshViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QuickMeshViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QuickMeshViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QuickMeshViewer))
        return static_cast<void*>(const_cast< QuickMeshViewer*>(this));
    return QGLViewer::qt_metacast(_clname);
}

int QuickMeshViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QuickMeshViewer::gotFocus(QuickMeshViewer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QuickMeshViewer::meshLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
