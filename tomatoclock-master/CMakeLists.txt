cmake_minimum_required(VERSION 3.16)
project(tc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 修复：添加所需的 Qt 组件（包含翻译功能所需的Network组件）
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts Sql Network)

# 整理项目源文件
set(PROJECT_SOURCES

    addlabelwidget.h
    addtargetwidget.h
    autodeletewidgetpointer.hpp
    button.hpp
    chartswidget.h
    clockdisplaywidget.h
    clockmainwidget.h
    clockoptions.hpp
    clockrunningwidget.h
    clocksmallwindow.h
    clocksql.hpp
    customslicewithvalue.h
    DataStructure.hpp
    displayclockbase.h
    labelsandtargetswidget.h
    listwidget.hpp
    menu.hpp
    messagebox.hpp
    piecharttest.hpp
    widget.hpp
    toolswidget.h
    progresswidget.h
    settingfileoperations.h
    settingwidget.h
    targetwidget.h
    TimeStatus.hpp
    titlebar.hpp
    tomatoclocktimer.h
    Translate.h
    Calculator.h




    addlabelwidget.cpp
    addtargetwidget.cpp
    chartswidget.cpp
    clockdisplaywidget.cpp
    clockmainwidget.cpp
    clockrunningwidget.cpp
    clocksmallwindow.cpp
    labelsandtargetswidget.cpp
    progresswidget.cpp
    settingfileoperations.cpp
    settingwidget.cpp
    targetwidget.cpp
    tomatoclocktimer.cpp
    toolswidget.cpp
    Translate.cpp
    Calculator.cpp


    main.cpp

    # UI 文件
    settingwidget.ui
    Calculator.ui


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        lon_widget.qrc
        img.qrc

    )
else()
    if(ANDROID)
        add_library(tc SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(tc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tc PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)


if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tc)
endif()

set_target_properties(tc PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tc)
endif()
