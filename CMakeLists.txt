#cmake_minimum_required(VERSION 3.25)
#project(Chua_circuit)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(Chua_circuit main.cpp)

cmake_minimum_required(VERSION 3.10)
project(Chua_circuit)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(Chua_circuit ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Chua_circuit sfml-system sfml-window sfml-graphics sfml-audio sfml-network)