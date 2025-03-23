cmake_minimum_required(VERSION 3.19)
project(RFTA LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RESOURCE_FILES res.qrc)

qt_add_executable(RFTA
    WIN32 MACOSX_BUNDLE

    ${RESOURCE_FILES}

    # - - Main file and mainwindow - -
    main.cpp
    src/mainwindow.cpp
    src/UI-SetupHelper.cpp
    src/NET-SetupHelper.cpp
    header/mainwindow.h


    # - - SOURCES - -

    # UI Source files
    src/login/login.cpp
    src/dashboard/UI-Dashboard.cpp
    src/dashboard/NET-Dashboard.cpp
    src/dashboard/dashboard.cpp
    src/dashboard/mods.cpp
    src/loadScreen/loadingscreen.cpp

    # Helping source files
    src/misc/clickQLabel.cpp
    src/misc/hasher.cpp
    src/misc/infobar.cpp

    # Net source files
    src/net/loginHandler.cpp
    src/net/serverHandler.cpp


    # - - HEADERS - -

    # UI Header files
    header/login/login.h
    header/dashboard/UI-dashboardStyle.h
    header/dashboard/dashboard.h
    header/dashboard/mods.h
    header/loadScreen/loadingscreen.h

    # Helper header files
    header/misc/clickQLabel.h
    header/misc/hasher.h
    header/misc/infobar.h
    header/utils/httplib.h
    header/utils/json.hpp

    # Net header files
    header/net/loginHandler.h
    header/net/serverHandler.h
)

qt_add_ui(RFTA SOURCES
    forms/login.ui
    forms/dashboard.ui
    forms/loadingscreen.ui
    forms/mods.ui
)


target_link_libraries(RFTA
    PRIVATE
        Qt::Core
        Qt::Widgets
)

if(WIN32)
    set(LIBRARY_PATH "C:/msys64/ucrt64/lib")
    target_link_libraries(RFTA PRIVATE
        ${LIBRARY_PATH}/libssl.a
        ${LIBRARY_PATH}/libcrypto.a
        ${LIBRARY_PATH}/libcrypt32.a
        ${LIBRARY_PATH}/libbcrypt.a
        ${LIBRARY_PATH}/libws2_32.a
    )
elseif(UNIX)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(RFTA PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
    )
endif()

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
