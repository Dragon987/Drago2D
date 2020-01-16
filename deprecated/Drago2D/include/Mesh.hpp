#pragma once

#include "Core.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "IBO.hpp"
#include "Shader.hpp"

namespace d2d
{
    namespace renderer
    {
        class D2D_API Mesh
        {
        private:
            VAO *mVao;
            VBO *mVBO;
            uint start, count;
            IBO *mIBO;
            bool useIBO;
            Shader *mShader;

        public:
            Mesh(float *vertices, size_t size, int usage);
            ~Mesh();

            void CreateIBO();

            void UploadIBOData(uint *indices, size_t size, int usage);

            void UploadData(float *vertices, size_t size, int usage);

            void Draw(uint mode, uint start, uint count);

            void AddShader(const std::string &vsSource, const std::string &fsSource);
            void SetColor(float r, float g, float b, float a);
            void SetMP(const glm::mat4& MP);

        };
    }
}