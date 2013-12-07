/****************************************************************************
** Meta object code from reading C++ file 'detectedevent.h'
**
** Created: Sat Dec 7 09:29:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TestNoobaVSSAD/NoobaVSSAD/detectedevent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detectedevent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DetectedEvent[] = {

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

static const char qt_meta_stringdata_DetectedEvent[] = {
    "DetectedEvent\0"
};

void DetectedEvent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DetectedEvent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetectedEvent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DetectedEvent,
      qt_meta_data_DetectedEvent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetectedEvent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetectedEvent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetectedEvent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetectedEvent))
        return static_cast<void*>(const_cast< DetectedEvent*>(this));
    return QObject::qt_metacast(_clname);
}

int DetectedEvent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
