cmake_minimum_required(VERSION 3.5)
project(calibration_manager)

## Enable O3
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -march=native -Wno-sign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -march=native -Wno-sign-compare")

# setup build type
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(${BUILD_TYPE} MATCHES "debug")
    set(CMAKE_BUILD_TYPE "Debug")
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/debug)
else()
    set(CMAKE_BUILD_TYPE "Release") 
    # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/release)
endif()

# find OpenMP
find_package(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# find Eigen
find_package(Eigen3 QUIET)
if (NOT EIGEN3_FOUND)
    # Fallback to cmake_modules
    find_package(cmake_modules REQUIRED)
    find_package(Eigen REQUIRED)
    set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
    set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})  # Not strictly necessary as Eigen is head only
    # Possibly map additional variables to the EIGEN3_ prefix.
else ()
    set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif ()

# find Boost
find_package(Boost REQUIRED)
# find yaml-cpp
find_package(yaml-cpp REQUIRED)
# find calibration-manager
find_package(calibration_manager REQUIRED)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    ${calibration_manager_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${YAML_CPP_INCLUDE_DIRS}
)

set(LIBS
    ${calibration_manager_LIBRARIES}
    ${YAML_CPP_LIBRARIES}
    ${Boost_LIBRARIES} 
    boost_system
    boost_filesystem
)

## example
add_executable(${PROJECT_NAME}_cpp_example example.cpp)
target_link_libraries(${PROJECT_NAME}_cpp_example 
    ${PROJECT_NAME}
)