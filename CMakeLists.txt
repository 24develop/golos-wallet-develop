cmake_minimum_required(VERSION 3.8)
project(hackaton_wallet)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH "/home/artem/SDK/Qt/5.9.3/gcc_64/")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5WebSockets REQUIRED)
find_package(Qt5Test REQUIRED)

set(SOURCE_FILES
        api.cpp
        api.h
        apicaller.cpp
        apicaller.h
        cmdsender.cpp
        cmdsender.h
        command.cpp
        command.h
        commandsender.cpp
        commandsender.h
        loginwindow.cpp
        loginwindow.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        paymentdialog.cpp
        paymentdialog.h
        socketsender.cpp
        socketsender.h)

set(TEST_FILES TestCommand.cpp TestCommand.h command.cpp command.h)

add_executable(hackaton_wallet ${SOURCE_FILES})
add_executable(hackaton_wallet_tests ${TEST_FILES})

target_link_libraries(hackaton_wallet Qt5::Widgets Qt5::Core Qt5::WebSockets)
target_link_libraries(hackaton_wallet_tests Qt5::Test Qt5::Widgets Qt5::Core Qt5::WebSockets)
