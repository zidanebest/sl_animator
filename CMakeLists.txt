cmake_minimum_required(VERSION 3.15)

set(Application_Name "sl_animator")
set(DCMAKE_SYSTEM_VERSION 10.0)

project(sl_animator)

set(CMAKE_CXX_STANDARD 17)

set(EnginePath ${PROJECT_SOURCE_DIR}/Source/Engine)
# set(EditorPath ${PROJECT_SOURCE_DIR}/Source/Editor)
set(LibraryPath ${PROJECT_SOURCE_DIR}/Source/ThirdParty)
# set(ResourcePath ${PROJECT_SOURCE_DIR}/Resource)

add_subdirectory(${LibraryPath}/glfw)
add_subdirectory(${LibraryPath}/glad)

file(GLOB_RECURSE _sources 
  ${EnginePath}/*.cpp 
  ${EnginePath}/*.h 
  ${EnginePath}/*.hpp 
)

add_executable(${Application_Name} "")
target_sources(${Application_Name} PRIVATE
  ${_sources}
)

target_link_libraries(${Application_Name} PRIVATE
  glfw
)
target_link_libraries(${Application_Name} PRIVATE
  glad
)



target_include_directories(${Application_Name}  PUBLIC
  ${LibraryPath}/glad/include
  ${LibraryPath}/glfw/include
  ${EnginePath}
)

target_compile_definitions(${Application_Name} PRIVATE
  GLFW_INCLUDE_NONE 
)

