/****************************************************************************
** Meta object code from reading C++ file 'settingwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../settingwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingWin_t {
    QByteArrayData data[11];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingWin_t qt_meta_stringdata_SettingWin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SettingWin"
QT_MOC_LITERAL(1, 11, 8), // "canApply"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 27), // "on_pushButton_Apply_clicked"
QT_MOC_LITERAL(4, 49, 34), // "on_pushButton_ProfilePhoto_cl..."
QT_MOC_LITERAL(5, 84, 27), // "on_pushButton_Model_clicked"
QT_MOC_LITERAL(6, 112, 24), // "on_pushButton_OK_clicked"
QT_MOC_LITERAL(7, 137, 28), // "on_pushButton_Cancel_clicked"
QT_MOC_LITERAL(8, 166, 35), // "on_pushButton_AudioPortTest_c..."
QT_MOC_LITERAL(9, 202, 36), // "on_pushButton_TestListenPort_..."
QT_MOC_LITERAL(10, 239, 34) // "on_pushButton_TestCallPort_cl..."

    },
    "SettingWin\0canApply\0\0on_pushButton_Apply_clicked\0"
    "on_pushButton_ProfilePhoto_clicked\0"
    "on_pushButton_Model_clicked\0"
    "on_pushButton_OK_clicked\0"
    "on_pushButton_Cancel_clicked\0"
    "on_pushButton_AudioPortTest_clicked\0"
    "on_pushButton_TestListenPort_clicked\0"
    "on_pushButton_TestCallPort_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

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

       0        // eod
};

void SettingWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->canApply(); break;
        case 1: _t->on_pushButton_Apply_clicked(); break;
        case 2: _t->on_pushButton_ProfilePhoto_clicked(); break;
        case 3: _t->on_pushButton_Model_clicked(); break;
        case 4: _t->on_pushButton_OK_clicked(); break;
        case 5: _t->on_pushButton_Cancel_clicked(); break;
        case 6: _t->on_pushButton_AudioPortTest_clicked(); break;
        case 7: _t->on_pushButton_TestListenPort_clicked(); break;
        case 8: _t->on_pushButton_TestCallPort_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SettingWin::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SettingWin.data,
    qt_meta_data_SettingWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
