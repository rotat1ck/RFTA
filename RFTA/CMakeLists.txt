cmake_minimum_required(VERSION 3.19)
project(RFTA LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RESOURCE_FILES res.qrc)

qt_add_executable(RFTA
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h

    ${RESOURCE_FILES}
    login.h login.cpp login.ui
    dashboard.h dashboard.cpp dashboard.ui
    UI-Dashboard.cpp
    UI-DashboardStyle.h
    loadingscreen.h loadingscreen.cpp loadingscreen.ui

)

target_link_libraries(RFTA
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS RFTA
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET RFTA
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
