cmake_minimum_required(VERSION 3.10)
project(CMakeProject1)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add source to this project's executable.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# Include directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Link OpenCV libraries
target_link_libraries(CMakeProject1 ${OpenCV_LIBS})
