cmake_minimum_required(VERSION 3.0)
project(Drago2D)

set(
    CXX_SCRS
    "src/Application.cpp"
    "src/IBO.cpp"
    "src/Log.cpp"
    "src/Mesh.cpp"
    "src/Transform.cpp"
    "src/Shader.cpp"
    "src/VAO.cpp"
    "src/VBO.cpp"
    "src/Window.cpp"
    "src/Draw.cpp")

add_compile_options("-std=c++17")

if (UNIX)
    set(GL_LIB "GL")
    set(GLFW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lib/linux/libglfw.so")
    set(GLEW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lib/linux/libGLEW.so")
else()
    set(D2D_PLATFORM_WINDOWS "D2D_PLATFORM_WINDOWS")
    set(D2D_BUILD_DLLS "D2D_BUILD_DLLS")
    set(GL_LIB "opengl32.lib")
    set(GLFW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lib/windows/glfw3.lib")
    set(GLEW_LIB "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lib/windows/glew32s.lib")
endif()

set(BASIC_FRAG_SHADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/Basic.fs.glsl")      
set(BASIC_VERTEX_SHADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/Basic.vs.glsl") 

set(TRANSFORM_FRAG_SHADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/Transform.fs.glsl")
set(TRANSFORM_VERTEX_SHADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/Transform.vs.glsl")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/Core.hpp.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/Core.hpp")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/d2dpch.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/d2dpch.h")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer.hpp.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer.hpp")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/include")

function(my_export_target _target _include_dir)

    file(
        WRITE "${CMAKE_CURRENT_BINARY_DIR}/${_target}Config.cmake"
            "include(\"${CMAKE_CURRENT_LIST_DIR}/build/${_target}Targets.cmake\")
            set_property(
                TARGET ${_target}
                APPEND PROPERTY
                    INTERFACE_INCLUDE_DIRECTORIES \"${_include_dir}\"
            )
            add_compile_options(\"-std=c++17\")"
    )
    export(TARGETS ${_target} FILE "${CMAKE_CURRENT_BINARY_DIR}/${_target}Targets.cmake")
    # NOTE: The following call can pollute your PC's CMake package registry
    #       See comments/alternatives below
    export(PACKAGE ${_target})

endfunction(my_export_target)

add_library(
    drago2d SHARED
    ${CXX_SCRS}
)
target_link_libraries(
    drago2d
    ${GL_LIB}
    ${GLFW_LIB}
    ${GLEW_LIB}
)

target_include_directories (
    drago2d PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/include" 
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

my_export_target(drago2d "${CMAKE_CURRENT_SOURCE_DIR}")
