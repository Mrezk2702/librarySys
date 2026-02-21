cmake_minimum_required(VERSION 3.15)

project(LibSystem
    VERSION 1.0.0
    DESCRIPTION "Project description"
    LANGUAGES CXX
)

# ============================================================================
# Configuration Options
# ============================================================================
option(BUILD_SHARED_LIBS "Build shared library instead of static" OFF)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================================
# Source Files
# ============================================================================
# Collect all source files
# Only look in the source directory, not subdirectories
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

# set(SOURCES
#     "*.cpp"
# )

# set(HEADERS
#      "*.hpp"
# )

# ============================================================================
# Target Definition
# ============================================================================
# For an executable:
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# For a library:
# add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# ============================================================================
# Compiler Options
# ============================================================================
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# ============================================================================
# Dependencies (example)
# ============================================================================
# find_package(SomeLibrary REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SomeLibrary::SomeLibrary)

# ============================================================================
# Include Directories
# ============================================================================
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)