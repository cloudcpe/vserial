cmake_minimum_required(VERSION 3.5)

project(vserial)

add_executable(${PROJECT_NAME} src/main.c)

install(TARGETS ${PROJECT_NAME}
        RUNTIME
        DESTINATION bin
        COMPONENT applications)

