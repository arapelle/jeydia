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
    include/jeydia_server/square.hpp
    include/jeydia_server/game_module.hpp
    include/jeydia_server/agent.hpp
    include/jeydia_server/physics_types.hpp
    include/jeydia_server/physics_body.hpp
    include/jeydia_server/application.hpp
    include/jeydia_server/map.hpp
    include/jeydia_server/module.hpp
    include/jeydia_server/user.hpp
)

# Sources:
set(sources
    src/agent.cpp
    src/application.cpp
    src/map.cpp
    src/main.cpp
    src/square.cpp
    src/game_module.cpp
    src/user.cpp
    src/physics_body.cpp
)

# Add C++ library
add_cpp_executable(${PROJECT_NAME}
    CXX_STANDARD 20
    INCLUDE_DIRECTORIES include
    VERSION_HEADER "version.hpp"
    HEADERS ${headers}
    SOURCES ${sources}
    )

find_package(arba 0.18 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC arba::arba)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})

file(CREATE_LINK ${PROJECT_SOURCE_DIR}/rsc ${PROJECT_BINARY_DIR}/rsc COPY_ON_ERROR SYMBOLIC)

#-----
