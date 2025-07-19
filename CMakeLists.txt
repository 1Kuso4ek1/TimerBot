cmake_minimum_required(VERSION 3.10)
project(TimerBot)

set(CMAKE_CXX_STANDARD 23)

add_executable(TimerBot main.cpp
    src/core/Application.cpp
    include/core/Application.hpp
    src/view/BotUi.cpp
    include/view/BotUi.hpp
    src/handlers/StartHandler.cpp
    include/handlers/StartHandler.hpp
    src/handlers/TimeHandler.cpp
    include/handlers/TimeHandler.hpp
    src/handlers/KillHandler.cpp
    include/handlers/KillHandler.hpp)

target_link_libraries(TimerBot TgBot)
target_include_directories(TimerBot PUBLIC ${TgBot_INCLUDE_DIRECTORIES} include/)

add_subdirectory(libraries/tgbot-cpp)
