/****************************************************************************
** Meta object code from reading C++ file 'clockmainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../clockmainwidget.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clockmainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
struct qt_meta_tag_ZN3lon15ClockMainWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto lon::ClockMainWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3lon15ClockMainWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "lon::ClockMainWidget",
        "displayClock",
        "",
        "label",
        "target",
        "displayTarget",
        "displayChart",
        "clockFinished",
        "clockBreaked",
        "displaySetting",
        "saveSettingToFile",
        "ClockOptions",
        "option",
        "iconActivated",
        "::QSystemTrayIcon::ActivationReason",
        "reason",
        "showMainWindow",
        "showTranslateWindow",
        "showCalculatorWindow",
        "exitApplication"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'displayClock'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Slot 'displayTarget'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'displayChart'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'clockFinished'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'clockBreaked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'displaySetting'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'saveSettingToFile'
        QtMocHelpers::SlotData<void(const ClockOptions &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'iconActivated'
        QtMocHelpers::SlotData<void(::QSystemTrayIcon::ActivationReason)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 },
        }}),
        // Slot 'showMainWindow'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'showTranslateWindow'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'showCalculatorWindow'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'exitApplication'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ClockMainWidget, qt_meta_tag_ZN3lon15ClockMainWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject lon::ClockMainWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<Widget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3lon15ClockMainWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3lon15ClockMainWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3lon15ClockMainWidgetE_t>.metaTypes,
    nullptr
} };

void lon::ClockMainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ClockMainWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->displayClock((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->displayTarget(); break;
        case 2: _t->displayChart(); break;
        case 3: _t->clockFinished(); break;
        case 4: _t->clockBreaked(); break;
        case 5: _t->displaySetting(); break;
        case 6: _t->saveSettingToFile((*reinterpret_cast< std::add_pointer_t<ClockOptions>>(_a[1]))); break;
        case 7: _t->iconActivated((*reinterpret_cast< std::add_pointer_t<::QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        case 8: _t->showMainWindow(); break;
        case 9: _t->showTranslateWindow(); break;
        case 10: _t->showCalculatorWindow(); break;
        case 11: _t->exitApplication(); break;
        default: ;
        }
    }
}

const QMetaObject *lon::ClockMainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lon::ClockMainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3lon15ClockMainWidgetE_t>.strings))
        return static_cast<void*>(this);
    return Widget::qt_metacast(_clname);
}

int lon::ClockMainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
