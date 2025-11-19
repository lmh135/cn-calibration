cmake_minimum_required(VERSION 3.5)
project(calibration_manager)

add_compile_options(-std=c++11)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(octopus_api REQUIRED)
find_package(dataset2 REQUIRED)

# YAML CPP
find_path(YAML_CPP_INCLUDE_DIR
        NAMES yaml_cpp.h
        PATHS ${YAML_CPP_INCLUDE_DIRS})

find_library(YAML_CPP_LIBRARY
        NAMES YAML_CPP
        PATHS ${YAML_CPP_LIBRARY_DIRS})
link_directories(${YAML_CPP_LIBRARY_DIRS})

# Includes and libraries
include_directories( 
  include
  ${EIGEN3_INCLUDE_DIR}
)
file(GLOB_RECURSE SOURCES "src/calibration_manager/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(${PROJECT_NAME} -lboost_filesystem -lboost_system
  ${YAML_CPP_LIBRARIES}
  dataset2
)
ament_target_dependencies(${PROJECT_NAME} octopus_api)

# # Install

install(
   DIRECTORY include/${PROJECT_NAME}
   DESTINATION include
)
install(
   TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION lib
)

#Test
add_executable(${PROJECT_NAME}_cpp_example 
  test/script/example.cpp 
)
install(
  TARGETS ${PROJECT_NAME}_cpp_example DESTINATION lib/${PROJECT_NAME}
)
target_link_libraries(${PROJECT_NAME}_cpp_example -lboost_filesystem -lboost_system calibration_manager
  ${YAML_CPP_LIBRARIES}
  dataset2
)
ament_target_dependencies(${PROJECT_NAME}_cpp_example)

# Ament Package
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(octopus_api)
ament_package()

add_subdirectory(pybind)