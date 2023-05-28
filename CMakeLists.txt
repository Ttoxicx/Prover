cmake_minimum_required (VERSION 3.15)

project (Prover)

set(MY_WORKING_DIR Prover)
message(STATUS "PROJECT NAME =  ${CMAKE_PROJECT_NAME}")
message(STATUS "PROJECT SOURCE DIR =  ${PROJECT_SOURCE_DIR}")

set(CMAKE_UTILS_DIR "${CMAKE_SOURCE_DIR}/cmake")
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_UTILS_DIR}")

include (UtilFunction)

add_subdirectory(Prover)
