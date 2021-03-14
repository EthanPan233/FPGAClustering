cmake_minimum_required(VERSION 3.10)

# Message
message(STATUS "UBC Mar 2021 Ethan Pan")
message(STATUS "CPEN 513 Assignment3")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${PROJECT_SOURCE_DIR})

# set the project name
project(Clustering)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add src files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# set(SRC_FILES ${SRC_DIR}/Circuit.cpp ${SRC_DIR}/Cell.cpp ${SRC_DIR}/main.cpp ${SRC_DIR}/graphics.h ${SRC_DIR}/graphics.cpp ${SRC_DIR}/draw.cpp)
set(SRC_FILES ${SRC_DIR}/Circuit.cpp ${SRC_DIR}/Cell.cpp ${SRC_DIR}/main.cpp ${SRC_DIR}/graphics.cpp ${SRC_DIR}/draw.cpp)

######################
# Check Dependencies #
######################
# uncommment this line if you are using self-compiled boost lib
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system filesystem program_options REQUIRED)

include_directories(/usr/openwin/lib)
include_directories(/usr/openwin/include)

# add X11
find_package(X11 REQUIRED)


include_directories(${X11_INCLUDE_DIR})

link_directories(${X11_LIBRARIES})
# add the executable
add_executable(Clustering ${SRC_FILES})



target_include_directories(Clustering PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# Boost
target_include_directories(Clustering PUBLIC ${Boost_INCLUDE_DIR} /usr/openwin/lib /usr/openwin/include)
target_link_libraries(Clustering PUBLIC ${Boost_LIBRARIES} ${X11_LIBRARIES})
