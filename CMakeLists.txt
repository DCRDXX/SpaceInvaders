cmake_minimum_required(VERSION 3.16)

project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(game
    main.cpp
    Controller.h
    Controller.cpp
)

qt_add_qml_module(game
    URI SpaceInvaders
    QML_FILES
        main.qml
)

target_link_libraries(game
    PRIVATE Qt6::Quick
)

