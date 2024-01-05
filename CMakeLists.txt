cmake_minimum_required(VERSION 3.26)
project(MeshLoading)

set(CMAKE_CXX_STANDARD 17)

# GLFW settings https://www.glfw.org/docs/3.3/build_guide.html
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Assimp settings
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

add_executable(MeshLoading
        src/main.cpp
        external/glad/src/glad.c
        external/stb/stb_image.cpp
)

include_directories(include)
include_directories(external/glad/include)
include_directories(external/assimp/include)
include_directories(external/glm)
include_directories(external/stb)

add_subdirectory(external/glfw)
add_subdirectory(external/assimp)
add_subdirectory(external/glm)

target_link_libraries(MeshLoading
        glfw
        assimp
        glm::glm
)

# Copy all necessary DLL files
install(FILES $<TARGET_RUNTIME_DLLS:MeshLoading> TYPE BIN)