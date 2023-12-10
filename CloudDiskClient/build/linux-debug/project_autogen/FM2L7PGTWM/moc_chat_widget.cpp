/****************************************************************************
** Meta object code from reading C++ file 'chat_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ChatWidget/chat_widget.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chat_widget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSChatWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSChatWidgetENDCLASS = QtMocHelpers::stringData(
    "ChatWidget",
    "showOnlineUserBtnClicked",
    "",
    "searchUserBtnClicked",
    "refreshFriendBtnClicked",
    "deleteFriendBtnClicked",
    "privateChatBtnClicked",
    "sendBtnClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChatWidgetENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[11];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[21];
    char stringdata4[24];
    char stringdata5[23];
    char stringdata6[22];
    char stringdata7[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSChatWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSChatWidgetENDCLASS_t qt_meta_stringdata_CLASSChatWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "ChatWidget"
        QT_MOC_LITERAL(11, 24),  // "showOnlineUserBtnClicked"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 20),  // "searchUserBtnClicked"
        QT_MOC_LITERAL(58, 23),  // "refreshFriendBtnClicked"
        QT_MOC_LITERAL(82, 22),  // "deleteFriendBtnClicked"
        QT_MOC_LITERAL(105, 21),  // "privateChatBtnClicked"
        QT_MOC_LITERAL(127, 14)   // "sendBtnClicked"
    },
    "ChatWidget",
    "showOnlineUserBtnClicked",
    "",
    "searchUserBtnClicked",
    "refreshFriendBtnClicked",
    "deleteFriendBtnClicked",
    "privateChatBtnClicked",
    "sendBtnClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChatWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChatWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSChatWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChatWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChatWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChatWidget, std::true_type>,
        // method 'showOnlineUserBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'searchUserBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshFriendBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteFriendBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'privateChatBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ChatWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showOnlineUserBtnClicked(); break;
        case 1: _t->searchUserBtnClicked(); break;
        case 2: _t->refreshFriendBtnClicked(); break;
        case 3: _t->deleteFriendBtnClicked(); break;
        case 4: _t->privateChatBtnClicked(); break;
        case 5: _t->sendBtnClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ChatWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChatWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
