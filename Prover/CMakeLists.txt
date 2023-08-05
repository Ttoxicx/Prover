cmake_minimum_required (VERSION 3.15)

set(my_compile_def "")
set(my_libraries "")
set(my_include_dirs "")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
	list(APPEND my_compile_def _CRT_SECURE_NO_WARNINGS)
endif()

ConstructSolutionDirTree(${CMAKE_CURRENT_SOURCE_DIR} my_head_list my_src_list local_include_dirs)
list(APPEND my_include_dirs ${local_include_dirs})

set(PROVER_EXE "${CMAKE_PROJECT_NAME}")
message(STATUS "EXECUTABLE NAME = ${PROVER_EXE}")

add_executable(${PROVER_EXE} ${my_src_list} ${my_head_list})

set(glfwlib "${PROJECT_SOURCE_DIR}/Prover/Engine/ThirdDependencies/glfw/lib/glfw3.lib" )

list(APPEND my_libraries ${glfwlib})

#target_include_directories(${PROVER_EXE} PRIVATE ${my_include_dirs})

set(IncludeDir "")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/ThirdDependencies/glfw/include")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/ThirdDependencies/glad/include")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/ThirdDependencies/assimp/include")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/ThirdDependencies/glm/include")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Editor/Excutable")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/Runtime/Core")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/Runtime/Function")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/Runtime/Platform")
list(APPEND IncludeDir "${PROJECT_SOURCE_DIR}/Prover/Engine/Runtime/Resource")
target_include_directories(${PROVER_EXE} PRIVATE ${IncludeDir})
target_link_libraries(${PROVER_EXE} PRIVATE ${my_libraries})
target_compile_definitions(${PROVER_EXE} PRIVATE ${my_compile_def})