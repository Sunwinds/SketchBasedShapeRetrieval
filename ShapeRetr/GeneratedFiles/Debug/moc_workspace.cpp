/****************************************************************************
** Meta object code from reading C++ file 'workspace.h'
**
** Created: Mon Apr 22 17:28:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../workspace.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'workspace.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WorkSpace[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      18,   10,   10,   10, 0x08,
      25,   10,   10,   10, 0x08,
      33,   10,   10,   10, 0x08,
      41,   10,   10,   10, 0x08,
      69,   58,   10,   10, 0x0a,
      89,   10,   10,   10, 0x0a,
     111,  102,   10,   10, 0x0a,
     138,  136,   10,   10, 0x0a,
     158,   10,   10,   10, 0x0a,
     178,   10,   10,   10, 0x0a,
     212,   10,   10,   10, 0x0a,
     222,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WorkSpace[] = {
    "WorkSpace\0\0open()\0save()\0clear()\0"
    "about()\0genofflineData()\0using_path\0"
    "loadMeshes(QString)\0loadMeshes()\0"
    "filelist\0loadMeshes(QStringList&)\0n\0"
    "showNumViewers(int)\0loadCurrentMeshes()\0"
    "setActiveViewer(QuickMeshViewer*)\0"
    "refresh()\0search()\0"
};

void WorkSpace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WorkSpace *_t = static_cast<WorkSpace *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->save(); break;
        case 2: _t->clear(); break;
        case 3: _t->about(); break;
        case 4: _t->genofflineData(); break;
        case 5: _t->loadMeshes((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->loadMeshes(); break;
        case 7: _t->loadMeshes((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->showNumViewers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->loadCurrentMeshes(); break;
        case 10: _t->setActiveViewer((*reinterpret_cast< QuickMeshViewer*(*)>(_a[1]))); break;
        case 11: _t->refresh(); break;
        case 12: _t->search(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WorkSpace::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WorkSpace::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WorkSpace,
      qt_meta_data_WorkSpace, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WorkSpace::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WorkSpace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WorkSpace::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WorkSpace))
        return static_cast<void*>(const_cast< WorkSpace*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WorkSpace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
static const uint qt_meta_data_LoaderThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_LoaderThread[] = {
    "LoaderThread\0"
};

void LoaderThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LoaderThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoaderThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LoaderThread,
      qt_meta_data_LoaderThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoaderThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoaderThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoaderThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoaderThread))
        return static_cast<void*>(const_cast< LoaderThread*>(this));
    return QThread::qt_metacast(_clname);
}

int LoaderThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
