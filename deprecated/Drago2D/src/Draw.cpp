#include "Draw.hpp"

namespace d2d::renderer
{
    Actor::Actor()
    {
        d2d::Color c(0.f, 0.f, 0.f, 0.f);
        mColor = c;
        mVertexShaderFile = basic_vertex_shader_file;
        mFragShaderFile = basic_frag_shader_file;
        mVertices = {};
        mUsage = D2D_STATIC_DRAW;
    }

    Actor::Actor(const int usage, const d2d::Color &c, const std::string &vertexShaderFile, const std::string &fragShaderFile, const std::vector<Vertex>& vertices)
    {
        mUsage = usage;
        mColor = c;
        mVertexShaderFile = vertexShaderFile;
        mFragShaderFile = fragShaderFile;
        mVertices = vertices;
    }

    void Actor::SetUsage(const int usage) { mUsage = usage; }

    void Actor::AddVertex(const Vertex &vertex) { mVertices.push_back(vertex); }

    void Actor::AddVertex(const float x, const float y) { mVertices.emplace_back(x, y); }

    void Actor::ChangeColor(const float r, const float g, const float b, const float a) { mColor = { r, g, b, a }; }

    void Actor::ChangeColor(const float r, const float g, const float b) { mColor = { r, g, b, 1}; }

    void Actor::ChangeColor(const float val) { mColor = d2d::Color(val); }

    void Actor::ChangeColor(const d2d::Color &color) { mColor = color; }

    void Actor::SetTransform(const float xPos, const float yPos, const float rotation, const float xScale, const float yScale) { mTransform = Transform(glm::vec2(xPos, yPos), rotation, glm::vec2(xScale, yScale)); }

    void Actor::Draw(const glm::mat4& projection, uint DrawType)
    {
        glm::mat4 MP = projection * mTransform.GetModel();

        std::size_t vertSize = mVertices.size() * 2 * sizeof(float);

        float* vertices = new float[vertSize / sizeof(float)];

        for (std::size_t i = 0; i < mVertices.size(); ++i)
        {
            vertices[i * 2] = mVertices[i].x;
            vertices[i * 2 + 1] = mVertices[i].y;
        }

        Mesh mesh(vertices, vertSize, mUsage);
        mesh.AddShader(mVertexShaderFile, mFragShaderFile);

        mesh.SetMP(MP);
        mesh.SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
        
        mesh.Draw(DrawType, 0, mVertices.size());

        delete vertices;
    }

} // namespace d2d::renderer