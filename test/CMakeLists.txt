find_package(GTest REQUIRED)

file(GLOB_RECURSE UT_SRC gtest/*.cpp)
file(GLOB_RECURSE INTERFACE_SRC interface_test/**.cpp)

# build normal online test
foreach(TEST ${INTERFACE_SRC})
    get_filename_component(NAME ${TEST} NAME_WE)
    add_executable(${NAME} ${TEST})
    set_property(TARGET ${NAME} PROPERTY CXX_STANDARD 14)
    target_link_libraries(${NAME} PUBLIC calibration_manager octopus_api)
endforeach()

# build gtest unit test
add_executable(calibration_manager_unit_test ${UT_SRC})
target_link_libraries(calibration_manager_unit_test PUBLIC calibration_manager gtest -lboost_filesystem)
add_test(calibration_manager calibration_manager)