#pragma once

#include "Core.hpp"

#include <GLEW/glew.h>
#include "Transform.hpp"

namespace d2d::renderer
{

    class D2D_API Shader
    {
    private:
        uint mProgram;
        std::unordered_map<std::string, int> mUniforms;

        inline int UniformLocation(const std::string &name)
        {
            auto search = mUniforms.find(name);

            if (search != mUniforms.end())
            {
                return search->second;
            }

            int loc = glGetUniformLocation(mProgram, name.c_str());
            mUniforms.insert(std::pair<std::string, int>(name, loc));
            return loc;
        }

    public:
        Shader(const std::string &vsSource, const std::string &fsSource);
        ~Shader();

        void Uniform4f(const std::string &name, float v0, float v1, float v2, float v3);
        void UniformMatrix4(const std::string& name, const glm::mat4& MP);

        inline void Bind() { glUseProgram(mProgram); }
        inline void Unbind() { glUseProgram(0); }
    };

} // namespace d2d::renderer
