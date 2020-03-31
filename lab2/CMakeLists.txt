cmake_minimum_required(VERSION 3.5)

project(TestCmake LANGUAGES CXX)
set(CMAKE_PREFIX_PATH C:\\Qt\\5.14.1\\mingw73_64\\lib\\cmake\\Qt5)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql)

add_executable(TestCmake
  main.cpp
        mainwindow.h
        StampDialog.h StampModel.h PhilatelyModel.h DialogDelegate.h ImageDelegate.h)

target_link_libraries(TestCmake PRIVATE Qt5::Widgets)
target_link_libraries(TestCmake PRIVATE Qt5::Sql)
