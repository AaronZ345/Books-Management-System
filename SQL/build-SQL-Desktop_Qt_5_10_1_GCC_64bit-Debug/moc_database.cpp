/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SQL/database.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Database_t {
    QByteArrayData data[32];
    char stringdata0[430];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Database_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Database_t qt_meta_stringdata_Database = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Database"
QT_MOC_LITERAL(1, 9, 12), // "WindowClosed"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "updateTime"
QT_MOC_LITERAL(4, 34, 14), // "setLoginWindow"
QT_MOC_LITERAL(5, 49, 17), // "setRegisterWindow"
QT_MOC_LITERAL(6, 67, 15), // "registerRequest"
QT_MOC_LITERAL(7, 83, 14), // "registerCancel"
QT_MOC_LITERAL(8, 98, 11), // "loginCancel"
QT_MOC_LITERAL(9, 110, 9), // "loginUser"
QT_MOC_LITERAL(10, 120, 12), // "loginManager"
QT_MOC_LITERAL(11, 133, 19), // "showBorrowableBooks"
QT_MOC_LITERAL(12, 153, 10), // "BorrowBook"
QT_MOC_LITERAL(13, 164, 10), // "ReturnBook"
QT_MOC_LITERAL(14, 175, 12), // "quitRegister"
QT_MOC_LITERAL(15, 188, 15), // "judgeBorrowable"
QT_MOC_LITERAL(16, 204, 13), // "judgeReturned"
QT_MOC_LITERAL(17, 218, 17), // "showMSearchWindow"
QT_MOC_LITERAL(18, 236, 14), // "quitManageUser"
QT_MOC_LITERAL(19, 251, 16), // "searchManageUser"
QT_MOC_LITERAL(20, 268, 23), // "showAskDeleteUserWindow"
QT_MOC_LITERAL(21, 292, 10), // "DeleteUser"
QT_MOC_LITERAL(22, 303, 9), // "grantUser"
QT_MOC_LITERAL(23, 313, 20), // "releaseUserAuthority"
QT_MOC_LITERAL(24, 334, 11), // "insertBooks"
QT_MOC_LITERAL(25, 346, 15), // "showManageBooks"
QT_MOC_LITERAL(26, 362, 9), // "linkToZJU"
QT_MOC_LITERAL(27, 372, 8), // "linkToHZ"
QT_MOC_LITERAL(28, 381, 8), // "linkToZJ"
QT_MOC_LITERAL(29, 390, 8), // "linkToCN"
QT_MOC_LITERAL(30, 399, 16), // "insertMultiBooks"
QT_MOC_LITERAL(31, 416, 13) // "readFileBooks"

    },
    "Database\0WindowClosed\0\0updateTime\0"
    "setLoginWindow\0setRegisterWindow\0"
    "registerRequest\0registerCancel\0"
    "loginCancel\0loginUser\0loginManager\0"
    "showBorrowableBooks\0BorrowBook\0"
    "ReturnBook\0quitRegister\0judgeBorrowable\0"
    "judgeReturned\0showMSearchWindow\0"
    "quitManageUser\0searchManageUser\0"
    "showAskDeleteUserWindow\0DeleteUser\0"
    "grantUser\0releaseUserAuthority\0"
    "insertBooks\0showManageBooks\0linkToZJU\0"
    "linkToHZ\0linkToZJ\0linkToCN\0insertMultiBooks\0"
    "readFileBooks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Database[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  164,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  165,    2, 0x08 /* Private */,
       4,    0,  166,    2, 0x08 /* Private */,
       5,    0,  167,    2, 0x08 /* Private */,
       6,    0,  168,    2, 0x08 /* Private */,
       7,    0,  169,    2, 0x08 /* Private */,
       8,    0,  170,    2, 0x08 /* Private */,
       9,    0,  171,    2, 0x08 /* Private */,
      10,    0,  172,    2, 0x08 /* Private */,
      11,    0,  173,    2, 0x08 /* Private */,
      12,    0,  174,    2, 0x08 /* Private */,
      13,    0,  175,    2, 0x08 /* Private */,
      14,    0,  176,    2, 0x08 /* Private */,
      15,    0,  177,    2, 0x08 /* Private */,
      16,    0,  178,    2, 0x08 /* Private */,
      17,    0,  179,    2, 0x08 /* Private */,
      18,    0,  180,    2, 0x08 /* Private */,
      19,    0,  181,    2, 0x08 /* Private */,
      20,    0,  182,    2, 0x08 /* Private */,
      21,    0,  183,    2, 0x08 /* Private */,
      22,    0,  184,    2, 0x08 /* Private */,
      23,    0,  185,    2, 0x08 /* Private */,
      24,    0,  186,    2, 0x08 /* Private */,
      25,    0,  187,    2, 0x08 /* Private */,
      26,    0,  188,    2, 0x08 /* Private */,
      27,    0,  189,    2, 0x08 /* Private */,
      28,    0,  190,    2, 0x08 /* Private */,
      29,    0,  191,    2, 0x08 /* Private */,
      30,    0,  192,    2, 0x08 /* Private */,
      31,    0,  193,    2, 0x08 /* Private */,

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

void Database::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Database *_t = static_cast<Database *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->WindowClosed(); break;
        case 1: _t->updateTime(); break;
        case 2: _t->setLoginWindow(); break;
        case 3: _t->setRegisterWindow(); break;
        case 4: _t->registerRequest(); break;
        case 5: _t->registerCancel(); break;
        case 6: _t->loginCancel(); break;
        case 7: _t->loginUser(); break;
        case 8: _t->loginManager(); break;
        case 9: _t->showBorrowableBooks(); break;
        case 10: _t->BorrowBook(); break;
        case 11: _t->ReturnBook(); break;
        case 12: _t->quitRegister(); break;
        case 13: _t->judgeBorrowable(); break;
        case 14: _t->judgeReturned(); break;
        case 15: _t->showMSearchWindow(); break;
        case 16: _t->quitManageUser(); break;
        case 17: _t->searchManageUser(); break;
        case 18: _t->showAskDeleteUserWindow(); break;
        case 19: _t->DeleteUser(); break;
        case 20: _t->grantUser(); break;
        case 21: _t->releaseUserAuthority(); break;
        case 22: _t->insertBooks(); break;
        case 23: _t->showManageBooks(); break;
        case 24: _t->linkToZJU(); break;
        case 25: _t->linkToHZ(); break;
        case 26: _t->linkToZJ(); break;
        case 27: _t->linkToCN(); break;
        case 28: _t->insertMultiBooks(); break;
        case 29: _t->readFileBooks(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Database::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Database::WindowClosed)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Database::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Database.data,
      qt_meta_data_Database,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Database::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Database::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Database.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Database::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void Database::WindowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
