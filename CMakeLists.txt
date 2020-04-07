cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(NonogramsSolver VERSION 0.0.1)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-sign-compare")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

file(GLOB SOURCE_FILES "src/*cpp")
file(GLOB MODEL_SOURCE_FILES "src/model/*cpp")
set(INCLUDE_DIRS ${INCLUDE_DIRS} include/ spdlog/include/ args/ src/model)
if(WIN32)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} dirent/include)
endif(WIN32)

add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=8)  # for ImageMagick
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0)  # for ImageMagick
add_definitions(-DBUGGY_MAGIC)  # can't write gif images

find_package(ImageMagick 7 COMPONENTS Magick++ REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})

find_package(Threads)

find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
  # Stand-alone build
  add_subdirectory(spdlog)
endif()

include_directories(${INCLUDE_DIRS})
add_executable(nonograms_solver ${SOURCE_FILES} ${MODEL_SOURCE_FILES})

target_link_libraries(nonograms_solver PRIVATE ${ImageMagick_LIBRARIES})
target_link_libraries(nonograms_solver PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(nonograms_solver PRIVATE spdlog::spdlog)
