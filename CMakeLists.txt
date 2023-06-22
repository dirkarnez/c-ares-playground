cmake_minimum_required(VERSION 3.18)

project("c-ares-playground" C CXX)

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

find_package(c-ares REQUIRED)

if(c-ares_FOUND)
    message(STATUS "YES")
else()
    message(STATUS "NO")
endif()

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} c-ares::cares_static ws2_32)