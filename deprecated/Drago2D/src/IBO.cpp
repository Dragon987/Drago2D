#include "IBO.hpp"

#include <GLEW/glew.h>

namespace d2d
{
    namespace renderer
    {

        IBO::IBO()
        {
            glGenBuffers(1, &mBuffer);
        }

        IBO::~IBO()
        {
            glDeleteBuffers(1, &mBuffer);
        }

        void IBO::Bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffer);
        }

        void IBO::Unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void IBO::UploadData(uint *indices, size_t size, int draw)
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, draw);
        }
    } // namespace renderer
} // namespace d2d