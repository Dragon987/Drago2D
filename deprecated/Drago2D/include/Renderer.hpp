#pragma once

#include "VAO.hpp"
#include "IBO.hpp"
#include "Mesh.hpp"
#include "VBO.hpp"

namespace d2d
{
    struct Color
    {
        float r{0}, g{0}, b{0}, a{0};

        inline Color(float val) 
            : r(val), g(val), b(val), a(1) {}

        inline Color(float _r, float _g, float _b, float _a) 
            : r(_r), g(_g), b(_b), a(_a) {}

        inline Color(float _r, float _g, float _b) 
            : r(_r), g(_g), b(_b), a(1) {}
        
        inline Color() = default;
        
    };

    namespace renderer
    {
        inline std::string basic_frag_shader_file =   "/home/dragomir/dev/Drago2D/Drago2D/Shaders/Basic.fs.glsl";
        inline std::string basic_vertex_shader_file = "/home/dragomir/dev/Drago2D/Drago2D/Shaders/Basic.vs.glsl";

        inline std::string transform_frag_shader_file =   "/home/dragomir/dev/Drago2D/Drago2D/Shaders/Transform.fs.glsl";
        inline std::string transform_vertex_shader_file = "/home/dragomir/dev/Drago2D/Drago2D/Shaders/Transform.vs.glsl";
    } // namespace renderer

} // namespace d2d
