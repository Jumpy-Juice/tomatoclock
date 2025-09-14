/****************************************************************************
** Meta object code from reading C++ file 'labelsandtargetswidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../labelsandtargetswidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'labelsandtargetswidget.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto lon::LabelsAndTargetsWidget::qt_create_metaobjectdata<qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "lon::LabelsAndTargetsWidget",
        "changeSetting",
        "",
        "showChart",
        "showCalculator",
        "showTranslate",
        "startClock",
        "label_name",
        "target_name",
        "redrawWidget",
        "addLabel",
        "addTarget",
        "closeAddLabelWidget",
        "closeAddTargetWidget",
        "labelAdded",
        "text",
        "onLabelButtonClicked",
        "targetAdded",
        "label",
        "target",
        "targetFinished",
        "deleteLabel",
        "deleteLabelWithConfirmation"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'changeSetting'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showChart'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showCalculator'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'showTranslate'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'startClock'
        QtMocHelpers::SignalData<void(QString, QString)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'redrawWidget'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'addLabel'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'addTarget'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'closeAddLabelWidget'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'closeAddTargetWidget'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'labelAdded'
        QtMocHelpers::SlotData<void(QString)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'onLabelButtonClicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'targetAdded'
        QtMocHelpers::SlotData<void(QString, QString)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 18 }, { QMetaType::QString, 19 },
        }}),
        // Slot 'targetFinished'
        QtMocHelpers::SlotData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Slot 'deleteLabel'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'deleteLabelWithConfirmation'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<LabelsAndTargetsWidget, qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject lon::LabelsAndTargetsWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t>.metaTypes,
    nullptr
} };

void lon::LabelsAndTargetsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LabelsAndTargetsWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->changeSetting(); break;
        case 1: _t->showChart(); break;
        case 2: _t->showCalculator(); break;
        case 3: _t->showTranslate(); break;
        case 4: _t->startClock((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->redrawWidget(); break;
        case 6: _t->addLabel(); break;
        case 7: _t->addTarget(); break;
        case 8: _t->closeAddLabelWidget(); break;
        case 9: _t->closeAddTargetWidget(); break;
        case 10: _t->labelAdded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->onLabelButtonClicked(); break;
        case 12: _t->targetAdded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->targetFinished((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->deleteLabel(); break;
        case 15: _t->deleteLabelWithConfirmation(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LabelsAndTargetsWidget::*)()>(_a, &LabelsAndTargetsWidget::changeSetting, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LabelsAndTargetsWidget::*)()>(_a, &LabelsAndTargetsWidget::showChart, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LabelsAndTargetsWidget::*)()>(_a, &LabelsAndTargetsWidget::showCalculator, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LabelsAndTargetsWidget::*)()>(_a, &LabelsAndTargetsWidget::showTranslate, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (LabelsAndTargetsWidget::*)(QString , QString )>(_a, &LabelsAndTargetsWidget::startClock, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (LabelsAndTargetsWidget::*)()>(_a, &LabelsAndTargetsWidget::redrawWidget, 5))
            return;
    }
}

const QMetaObject *lon::LabelsAndTargetsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lon::LabelsAndTargetsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN3lon22LabelsAndTargetsWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lon::LabelsAndTargetsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void lon::LabelsAndTargetsWidget::changeSetting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lon::LabelsAndTargetsWidget::showChart()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void lon::LabelsAndTargetsWidget::showCalculator()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void lon::LabelsAndTargetsWidget::showTranslate()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void lon::LabelsAndTargetsWidget::startClock(QString _t1, QString _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void lon::LabelsAndTargetsWidget::redrawWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
