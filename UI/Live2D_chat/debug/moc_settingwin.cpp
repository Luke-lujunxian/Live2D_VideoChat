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
    QByteArrayData data[12];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingWin_t qt_meta_stringdata_SettingWin = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SettingWin"
QT_MOC_LITERAL(1, 11, 19), // "settingApplySuccess"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "canApply"
QT_MOC_LITERAL(4, 41, 27), // "on_pushButton_Apply_clicked"
QT_MOC_LITERAL(5, 69, 34), // "on_pushButton_ProfilePhoto_cl..."
QT_MOC_LITERAL(6, 104, 27), // "on_pushButton_Model_clicked"
QT_MOC_LITERAL(7, 132, 24), // "on_pushButton_OK_clicked"
QT_MOC_LITERAL(8, 157, 28), // "on_pushButton_Cancel_clicked"
QT_MOC_LITERAL(9, 186, 35), // "on_pushButton_AudioPortTest_c..."
QT_MOC_LITERAL(10, 222, 36), // "on_pushButton_TestListenPort_..."
QT_MOC_LITERAL(11, 259, 34) // "on_pushButton_TestCallPort_cl..."

    },
    "SettingWin\0settingApplySuccess\0\0"
    "canApply\0on_pushButton_Apply_clicked\0"
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
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

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
        case 0: _t->settingApplySuccess(); break;
        case 1: _t->canApply(); break;
        case 2: _t->on_pushButton_Apply_clicked(); break;
        case 3: _t->on_pushButton_ProfilePhoto_clicked(); break;
        case 4: _t->on_pushButton_Model_clicked(); break;
        case 5: _t->on_pushButton_OK_clicked(); break;
        case 6: _t->on_pushButton_Cancel_clicked(); break;
        case 7: _t->on_pushButton_AudioPortTest_clicked(); break;
        case 8: _t->on_pushButton_TestListenPort_clicked(); break;
        case 9: _t->on_pushButton_TestCallPort_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingWin::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWin::settingApplySuccess)) {
                *result = 0;
                return;
            }
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SettingWin::settingApplySuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
