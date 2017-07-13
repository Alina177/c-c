/****************************************************************************
** Meta object code from reading C++ file 'diagram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../Рабочий стол/курсач/Diagrams/diagram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diagram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Diagram_t {
    QByteArrayData data[13];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Diagram_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Diagram_t qt_meta_stringdata_Diagram = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Diagram"
QT_MOC_LITERAL(1, 8, 19), // "editingFinishedSlot"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "checkTableSlot"
QT_MOC_LITERAL(4, 44, 13), // "fillTableSlot"
QT_MOC_LITERAL(5, 58, 12), // "buildDiagram"
QT_MOC_LITERAL(6, 71, 15), // "buildDiagramBig"
QT_MOC_LITERAL(7, 87, 22), // "on_actionWindow_column"
QT_MOC_LITERAL(8, 110, 19), // "on_actionWindow_pie"
QT_MOC_LITERAL(9, 130, 22), // "on_actionWindow_linear"
QT_MOC_LITERAL(10, 153, 25), // "on_actionWindowBig_column"
QT_MOC_LITERAL(11, 179, 22), // "on_actionWindowBig_pie"
QT_MOC_LITERAL(12, 202, 25) // "on_actionWindowBig_linear"

    },
    "Diagram\0editingFinishedSlot\0\0"
    "checkTableSlot\0fillTableSlot\0buildDiagram\0"
    "buildDiagramBig\0on_actionWindow_column\0"
    "on_actionWindow_pie\0on_actionWindow_linear\0"
    "on_actionWindowBig_column\0"
    "on_actionWindowBig_pie\0on_actionWindowBig_linear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Diagram[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Diagram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Diagram *_t = static_cast<Diagram *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editingFinishedSlot(); break;
        case 1: _t->checkTableSlot(); break;
        case 2: _t->fillTableSlot(); break;
        case 3: _t->buildDiagram(); break;
        case 4: _t->buildDiagramBig(); break;
        case 5: _t->on_actionWindow_column(); break;
        case 6: _t->on_actionWindow_pie(); break;
        case 7: _t->on_actionWindow_linear(); break;
        case 8: _t->on_actionWindowBig_column(); break;
        case 9: _t->on_actionWindowBig_pie(); break;
        case 10: _t->on_actionWindowBig_linear(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Diagram::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Diagram.data,
      qt_meta_data_Diagram,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Diagram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Diagram::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Diagram.stringdata0))
        return static_cast<void*>(const_cast< Diagram*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Diagram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
