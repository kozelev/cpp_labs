option(TEST_SOLUTION "Build solution" OFF)
option(ENABLE_PRIVATE_TESTS "Enable private tests" OFF)
option(GRADER "Building on CI" OFF)

function(patch_include_directories TARGET)
  if (TEST_SOLUTION)
    get_filename_component(TASK_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    target_include_directories(${TARGET}
      PRIVATE ../private/${TASK_NAME})
  endif()

  target_include_directories(${TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(add_test_executable NAME)
  set(MULTI_VALUE_ARGS PRIVATE_TESTS SOLUTION_SRCS)
  cmake_parse_arguments(TEST_LIBRARY "" "" "${MULTI_VALUE_ARGS}" ${ARGN})

  get_filename_component(TASK_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
  if (TEST_SOLUTION)
    prepend(TEST_LIBRARY_SOLUTION_SRCS "../private/${TASK_NAME}" ${TEST_LIBRARY_SOLUTION_SRCS})
  endif()

  if (ENABLE_PRIVATE_TESTS)
    prepend(TEST_LIBRARY_PRIVATE_TESTS "../private/${TASK_NAME}" ${TEST_LIBRARY_PRIVATE_TESTS})
  endif()

  add_executable(${NAME}
    ${TEST_LIBRARY_UNPARSED_ARGUMENTS}
    ${TEST_LIBRARY_SOLUTION_SRCS}
    ${TEST_LIBRARY_PRIVATE_TESTS})

  patch_include_directories(${NAME})
endfunction()

add_custom_target(test-all)

function(add_catch TARGET)
  add_test_executable(${TARGET}
    ${ARGN})

  target_link_libraries(${TARGET}
    contrib_catch_main)

  if (TEST_SOLUTION)
    add_custom_target(
      run_${TARGET}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      DEPENDS ${TARGET}
      COMMAND ${CMAKE_BINARY_DIR}/${TARGET})

    add_dependencies(test-all run_${TARGET})
  endif()
endfunction()
