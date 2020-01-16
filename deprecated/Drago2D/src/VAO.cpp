#include "VAO.hpp"

namespace d2d
{
    namespace renderer
    {
        VAO::VAO()
        {
            glGenVertexArrays(1, &mVAO);
        }

        VAO::~VAO()
        {
            glDeleteVertexArrays(1, &mVAO);
        }

        void VAO::Bind()
        {
            glBindVertexArray(mVAO);
        }

        void VAO::Unbind()
        {
            glBindVertexArray(0);
        }

        void VAO::VertexAttribPointer(uint index, uint size, size_t stride, const void *offset)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE,  stride, offset);
        }

        void VAO::Draw(bool useIBO, uint mode, uint startIdx, uint count)
        {
            if (!useIBO)
                glDrawArrays(mode, startIdx, count);
            else
                glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
        }

    } // namespace renderer
    
} // namespace d2d
