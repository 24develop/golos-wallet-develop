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
        socketsender.cpp socketsender.h
        Response.cpp Response.h
        Transaction.cpp Transaction.h
        lib/bs58/base58_c.cpp lib/bs58/libbase58.h
        lib/bs58/QBS58.cpp lib/bs58/QBS58.h
        lib/Auth.cpp lib/Auth.h
        lib/Signer.cpp lib/Signer.h
        )

set(TEST_FILES tests/main.cpp tests/TestCommand.cpp tests/TestCommand.h
        commandsender.cpp commandsender.h
        socketsender.cpp socketsender.h
        apicaller.cpp apicaller.h
        api.cpp api.h
        command.cpp command.h
        Response.h Response.cpp
        tests/TestResponse.cpp tests/TestResponse.h
        lib/bs58/base58_c.cpp lib/bs58/libbase58.h lib/bs58/QBS58.cpp lib/bs58/QBS58.h tests/TestQBS58.cpp tests/TestQBS58.h lib/Auth.cpp lib/Auth.h tests/TestAuth.cpp tests/TestAuth.h Transaction.cpp Transaction.h tests/TestTransaction.cpp tests/TestTransaction.h lib/Signer.cpp lib/Signer.h tests/TestSigner.cpp tests/TestSigner.h)

link_directories(/usr/local/lib)

add_executable(hackaton_wallet ${SOURCE_FILES})

target_link_libraries(hackaton_wallet Qt5::Widgets Qt5::Core Qt5::WebSockets cryptopp secp256k1)
