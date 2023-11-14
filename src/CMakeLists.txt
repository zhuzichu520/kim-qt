cmake_minimum_required(VERSION 3.20)

project(kim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${KIM_OUTPUT_DIRECTORY})
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${KIM_OUTPUT_DIRECTORY})
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick WebSockets)

set(PROJECT_SOURCES
    qml.qrc
    main.cpp
    singleton.h
    stdafx.h
    db/export.h
    db/precompiled.h
    db/Message.h db/Message.cpp
    db/Session.h db/Session.cpp
    manager/IMManager.h manager/IMManager.cpp
    manager/DBManager.h manager/DBManager.cpp
    helper/SettingsHelper.h helper/SettingsHelper.cpp
    helper/TextDocumentHelper.h helper/TextDocumentHelper.cpp
    proto/Message.pb.h proto/Message.pb.cc
    proto/ReplyBody.pb.h proto/ReplyBody.pb.cc
    proto/SentBody.pb.h proto/SentBody.pb.cc
    controller/ContactController.h controller/ContactController.cpp
    model/ImageModel.h model/ImageModel.cpp
    model/UserModel.h model/UserModel.cpp
    model/BaseListModel.h
    model/SessionModel.h model/SessionModel.cpp
    model/MessageModel.h model/MessageModel.cpp
    model/MessageListModel.h model/MessageListModel.cpp
    model/SessionListModel.h model/SessionListModel.cpp
    model/SessionListSortProxyModel.h model/SessionListSortProxyModel.cpp
    model/MessageListSortProxyModel.h model/MessageListSortProxyModel.cpp
    model/ContactListModel.h model/ContactListModel.cpp
    provider/UserProvider.h provider/UserProvider.cpp
    component/CircularReveal.h component/CircularReveal.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(kim
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET kim APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(kim SHARED
            ${PROJECT_SOURCES}
        )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    add_executable(kim
        ${PROJECT_SOURCES}
    )
endif()
endif()

target_link_libraries(kim PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::WebSockets
    protobuf::libprotobuf
    fluentuiplugin
    QxOrm
)

target_compile_definitions(kim PRIVATE
    -D_BUILDING_QX_KIM
)

set_target_properties(kim PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(kim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/QxOrm/include
)

install(TARGETS kim
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(kim)
    qt_finalize_executable(kim)
endif()
