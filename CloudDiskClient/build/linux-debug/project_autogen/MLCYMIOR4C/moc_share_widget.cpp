/****************************************************************************
** Meta object code from reading C++ file 'share_widget.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ShareWidget/share_widget.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'share_widget.hpp' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSShareWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSShareWidgetENDCLASS = QtMocHelpers::stringData(
    "ShareWidget",
    "selectAllBtnClicked",
    "",
    "cancelSelectedBtnClicked",
    "confirmBtnClicked",
    "cancelBtnClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSShareWidgetENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[12];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[18];
    char stringdata5[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSShareWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSShareWidgetENDCLASS_t qt_meta_stringdata_CLASSShareWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "ShareWidget"
        QT_MOC_LITERAL(12, 19),  // "selectAllBtnClicked"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 24),  // "cancelSelectedBtnClicked"
        QT_MOC_LITERAL(58, 17),  // "confirmBtnClicked"
        QT_MOC_LITERAL(76, 16)   // "cancelBtnClicked"
    },
    "ShareWidget",
    "selectAllBtnClicked",
    "",
    "cancelSelectedBtnClicked",
    "confirmBtnClicked",
    "cancelBtnClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSShareWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    0,   40,    2, 0x08,    3 /* Private */,
       5,    0,   41,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ShareWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSShareWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSShareWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSShareWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ShareWidget, std::true_type>,
        // method 'selectAllBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancelSelectedBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'confirmBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cancelBtnClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ShareWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShareWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectAllBtnClicked(); break;
        case 1: _t->cancelSelectedBtnClicked(); break;
        case 2: _t->confirmBtnClicked(); break;
        case 3: _t->cancelBtnClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ShareWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShareWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSShareWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ShareWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
