cmake_minimum_required(VERSION 3.22)

project(bcd LANGUAGES C VERSION 0.1)

set(SOURCES src/main.c
            src/utils.c
            src/display.c)
set(HEADERS src/utils.h
            src/display.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
