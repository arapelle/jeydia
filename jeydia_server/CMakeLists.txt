cmake_minimum_required(VERSION 3.18)

#-----
# C++ PROJECT

project(jeydia_server
        VERSION 0.1.0
#        DESCRIPTION ""
        LANGUAGES CXX)

message(STATUS "PROJECT : ${PROJECT_NAME} ${PROJECT_VERSION}")

#-----

# Headers:
set(headers
    include/jeydia_server/application.hpp
    include/jeydia_server/module.hpp
)

# Sources:
set(sources
    src/main.cpp
)

# Add C++ library
add_cpp_executable(${PROJECT_NAME}
    CXX_STANDARD 20
    INCLUDE_DIRECTORIES include
    VERSION_HEADER "version.hpp"
    HEADERS ${headers}
    SOURCES ${sources}
    )

find_package(arba 0.15 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC arba::arba)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})

#-----
