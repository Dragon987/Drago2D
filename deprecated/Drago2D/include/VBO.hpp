#pragma once

#include "Core.hpp"

#define D2D_STATIC_DRAW GL_STATIC_DRAW
#define D2D_DYNAMIC_DRAW GL_DYNAMIC_DRAW
#define D2D_STREAM_DRAW GL_STREAM_DRAW

namespace d2d
{
    namespace renderer
    {
        typedef unsigned int uint;

        class D2D_API VBO
        {
        private:
            uint mBuffer;

        public:
            VBO();
            ~VBO();

            void UploadData(size_t dataSize, const void *data, int usage);            

            void Bind();
            void Unbind();
        };
    }
}