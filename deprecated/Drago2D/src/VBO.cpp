#include "VBO.hpp"

#include "GLEW/glew.h"

namespace d2d
{
    namespace renderer
    {
        VBO::VBO()
        {
            glGenBuffers(1, &mBuffer);
        }

        VBO::~VBO()
        {
            glDeleteBuffers(1, &mBuffer);
        }

        void VBO::Bind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
        }

        void VBO::Unbind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void VBO::UploadData(size_t dataSize, const void *data, int usage)
        {
            glBufferData(GL_ARRAY_BUFFER, dataSize, data, usage);
        }
    }
}