cmake_minimum_required(VERSION 3.1)

project(QSyncable LANGUAGES CXX)

find_package(Qt5 REQUIRED
    Core
    Qml
    )

# Module version
set(QS_MAJOR 1)
set(QS_MINOR 0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON) # This is to find generated *.moc and *.h files in build dir

set(SOURCES
    qsdiffrunner.cpp
    qspatch.cpp
    qslistmodel.cpp
    qsuuid.cpp
    qsdiffrunneralgo.cpp
    qstree.cpp
    qstreenode.cpp
    qsjsonlistmodel.cpp
    qsyncableqmltypes.cpp
    qsyncablefunctions.cpp
    qsyncableqmlwrapper.cpp
    )

add_library(QSyncable OBJECT ${SOURCES})

# --- Object library to link directly with the application
target_link_libraries(QSyncable PUBLIC
    Qt5::Core
    Qt5::Qml
    )
set_target_properties(QSyncable
    PROPERTIES
        CXX_STANDARD 11
        EXCLUDE_FROM_ALL TRUE
    )

# --- Plugin library
add_library(QSyncablePlugin SHARED
    ${SOURCES}
    qsplugin.cpp
    )
target_link_libraries(QSyncablePlugin PUBLIC
    Qt5::Core
    Qt5::Qml
    )
target_compile_definitions(QSyncablePlugin
    PRIVATE
        QML_PLUGIN
        QML_IMPORT_MAJOR_VERSION=${QS_MAJOR}
        QML_IMPORT_MINOR_VERSION=${QS_MINOR}
    )
set_target_properties(QSyncablePlugin
    PROPERTIES
        CXX_STANDARD 11
        OUTPUT_NAME qsyncable
        DEBUG_POSTFIX d
        EXCLUDE_FROM_ALL TRUE
    )

# --- Create installed package
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
set(PACKAGE_NAME ${CMAKE_PROJECT_NAME})

set(QML_MODULE_PATH qml_module)
configure_package_config_file(
    QSyncableConfig.cmake.in
    ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
    INSTALL_DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${PACKAGE_NAME}
    PATH_VARS
        QML_MODULE_PATH
    )

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}ConfigVersion.cmake
    VERSION
        "${QS_MAJOR}.${QS_MINOR}"
    COMPATIBILITY
        SameMajorVersion
    )

set(QS_INSTALL_PATH "${QML_MODULE_PATH}/QSyncable")

# qml module
install(TARGETS QSyncablePlugin
    RUNTIME DESTINATION ${QS_INSTALL_PATH}
    COMPONENT qsyncable
    )
install(
    FILES module/qmldir module/qsyncable.qmltypes
    DESTINATION ${QS_INSTALL_PATH}
    COMPONENT qsyncable
    )

# cmake package config
install(
    FILES
        ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}Config.cmake
        ${CMAKE_BINARY_DIR}/${PACKAGE_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PACKAGE_NAME}
    )
