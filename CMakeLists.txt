cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME lin)
project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Werror)

enable_testing()
add_subdirectory(gtest)

add_executable(core_tests
  test/core/types_matrix_test.cpp
  test/core/types_vector_test.cpp
  test/core/operations_tensor_operations_test.cpp
  test/core/operations_tensor_operators_test.cpp
  test/core/operations_vector_operations_test.cpp
)
target_include_directories(core_tests PRIVATE
  include
)
target_link_libraries(core_tests PRIVATE
  gtest
  gtest_main
)
add_test(run_core_tests core_tests)

add_executable(factorizations_tests
  src/lin_generators_randoms.cpp
  test/factorizations/qr_test.cpp
)
target_include_directories(factorizations_tests PRIVATE
  include
)
target_link_libraries(factorizations_tests PRIVATE
  gtest
  gtest_main
)
add_test(run_factorizations_tests factorizations_tests)

add_executable(generators_tests
  src/lin_generators_randoms.cpp
  test/generators/constants_test.cpp
  test/generators/randoms_test.cpp
)
target_include_directories(generators_tests PRIVATE
  include
)
target_link_libraries(generators_tests PRIVATE
  gtest
  gtest_main
)
add_test(run_generators_tests generators_tests)

add_executable(references_tests
  test/references/base_reference_test.cpp
  test/references/stream_reference_test.cpp
)
target_include_directories(references_tests PRIVATE
  include
)
target_link_libraries(references_tests PRIVATE
  gtest
  gtest_main
)
add_test(run_references_tests references_tests)

add_executable(substitutions_tests
  src/lin_generators_randoms.cpp
  test/substitutions/backward_substitution_test.cpp
)
target_include_directories(substitutions_tests PRIVATE
  include
)
target_link_libraries(substitutions_tests PRIVATE
  gtest
  gtest_main
)
add_test(run_substitutions_tests substitutions_tests)
