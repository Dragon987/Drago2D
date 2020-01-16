#pragma once

#include "GLEW/glew.h"
#include "Core.hpp"


#define D2D_LINES            GL_LINES 
#define D2D_LINE_LOOP        GL_LINE_LOOP 
#define D2D_LINE_STRIP       GL_LINE_STRIP 
#define D2D_TRIANGLES        GL_TRIANGLES
#define D2D_TRIANGLE_STRIP   GL_TRIANGLE_STRIP
#define D2D_TRIANGLE_FAN     GL_TRIANGLE_FAN

namespace d2d
{
    namespace renderer
    {
        
        class D2D_API VAO
        {
        private:
            uint mVAO;

        public:
            VAO();
            ~VAO();

            void VertexAttribPointer(uint index, uint size, size_t stride, const void *offset);

            void Bind();
            void Unbind();

            void Draw(bool useIBO, uint mode, uint startIdx, uint count);

        };

    } // namespace renderer
    
} // namespace d2d
