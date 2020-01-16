#pragma once

#include "Core.hpp"

namespace d2d
{
    namespace renderer
    {
        class D2D_API IBO
        {
        private:
            uint mBuffer;

        public:
            IBO();
            ~IBO();

            void Bind();
            void Unbind();

            void UploadData(uint *indices, size_t size, int usage);

        };
    }
}