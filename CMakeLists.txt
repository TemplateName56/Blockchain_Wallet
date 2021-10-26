cmake_minimum_required(VERSION 3.5)

project(Blockchain_Wallet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        client/gui/mainwindow.cpp
        client/gui/mainwindow.h
        client/gui/mainwindow.ui
        client/gui/auth_form.h
        client/gui/auth_form.cpp
        client/gui/auth_form.ui
        client/scripts/json_func.h
        client/scripts/json_func.cpp
        client/scripts/new_wallet.h
        client/scripts/new_wallet.cpp
        client/tests/program_exception.h
        client/tests/program_exception.cpp
        client/gui/settings_form.h
        client/gui/settings_form.cpp
        client/gui/settings_form.ui
        client/gui/about_program_form.h
        client/gui/about_program_form.cpp
        client/gui/about_program_form.ui
        includes/effolkronium/random.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Blockchain_Wallet
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Blockchain_Wallet APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Blockchain_Wallet SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Blockchain_Wallet
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Blockchain_Wallet PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)

set_target_properties(Blockchain_Wallet PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Blockchain_Wallet)
endif()
