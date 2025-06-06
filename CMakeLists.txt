cmake_minimum_required(VERSION 3.19)
project(messenger LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

# Явное добавление ресурсов
qt_add_resources(RESOURCE_FILES
    "icons.qrc"
)

qt_add_executable(messenger
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${RESOURCE_FILES}
    icons/call.png
    icons/logo.png
    icons/profile.png
    icons/videoCall.png
)

target_link_libraries(messenger
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)
install(TARGETS messenger
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET messenger
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
