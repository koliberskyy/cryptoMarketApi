cmake_minimum_required(VERSION 3.5)

project(CryptoMarketApi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Network REQUIRED)

include_directories(
    src
    src/AbstractMarket
    src/Bybit
    )

set(PROJECT_SOURCES
        src/main.cpp
        src/AbstractRequests/abstractrequests.h

        src/AbstractMarket/abstractmarket.h

        src/Bybit/bybitapi.h

        README.md
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CryptoMarketApi
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    else()
        add_executable(CryptoMarketApi
            ${PROJECT_SOURCES}
        )
    endif()

target_link_libraries(CryptoMarketApi
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Threads::Threads)
set_target_properties(CryptoMarketApi PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

