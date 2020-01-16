#include "Mesh.hpp"


namespace d2d
{
    namespace renderer
    {
        Mesh::Mesh(float *vertices, size_t size, int usage)
        {
            mVao = new VAO();
            mVao->Bind();
            mVBO = new VBO();
            mVBO->Bind();

            mVBO->UploadData(size, vertices, usage);

            mVao->VertexAttribPointer(0, 2, 8, 0);

            mVBO->Unbind();
            mVao->Unbind();

            useIBO = false;
            mIBO = nullptr;
        }

        Mesh::~Mesh()
        {
            mVBO->Unbind();
            mVao->Unbind();

            if (mIBO)
            {
                mIBO->Unbind();
                delete mIBO;
            }

            if (mShader)
            {
                mShader->Unbind();
                delete mShader;
            }

            delete mVao;
            delete mVBO;
        }

        void Mesh::UploadIBOData(uint *indices, size_t size, int usage)
        {
            mVao->Bind();
            mIBO->Bind();

            mIBO->UploadData(indices, size, usage);
        }

        void Mesh::Draw(uint mode, uint start, uint count)
        {
            mVao->Bind();
            mVBO->Bind();
            mShader->Bind();
            
            if (!useIBO)
                mVao->Draw(false, mode, start, count);
            else
            {
                mIBO->Bind();
                mVao->Draw(true, mode, start, count);
            }
            
        }

        void Mesh::CreateIBO()
        {
            useIBO = true;
            mIBO = new IBO();
        }

        void Mesh::UploadData(float *vertices, size_t size, int usage)
        {
            mVao->Bind();
            mVBO->Bind();

            mVBO->UploadData(size, vertices, usage);

            mVao->VertexAttribPointer(0, 2, 8, 0);

            mVBO->Unbind();
            mVao->Unbind();
        }

        void Mesh::AddShader(const std::string &vsSource, const std::string &fsSource)
        {
            mShader = new Shader(vsSource, fsSource);
        }

        void Mesh::SetColor(float r, float g, float b, float a)
        {
            mShader->Bind();
            mShader->Uniform4f("uColor", r, g, b, a);
        }

        void Mesh::SetMP(const glm::mat4& MP)
        {
            mShader->Bind();
            mShader->UniformMatrix4("uMVP", MP);
        }

    }
}