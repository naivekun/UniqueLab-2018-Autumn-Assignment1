cmake_minimum_required (VERSION 2.8.11)
project (uniquelab_test)

add_subdirectory(googletest ${CMAKE_BINARY_DIR}/googletest)
add_subdirectory(set ${CMAKE_BINARY_DIR}/set)
add_subdirectory(priority_queue ${CMAKE_BINARY_DIR}/priority_queue)
add_subdirectory(unordered_map ${CMAKE_BINARY_DIR}/unordered_map)


option(set_test "Enable test set" off)
option(pri_test "Enable test pri" off)
option(map_test "Enable test map" off)
option(ALL "Enable ALL" off)

if (ALL)
  set(set_test on)
  set(pri_test on)
  set(map_test on)
endif()

if(set_test)
  add_executable(set_test set/set_test.cpp)
  target_link_libraries(set_test set gtest_main)
endif()

if(pri_test)
  add_executable(pri_test priority_queue/priority_queue_test.cpp)
  target_link_libraries(pri_test priority_queue gtest_main)
endif()

if(map_test)
  add_executable(map_test unordered_map/unordered_map_test.cpp)
  target_link_libraries(map_test unordered_map gtest_main)
endif()
