#pragma once

#include "Core.hpp"

#include "Renderer.hpp"

namespace d2d::renderer
{
    /* A class which is used to draw stuff on screen
    mVertices constains positions of vertices relative to center, and center coords are in mTransform*/

    struct Vertex
    {
        float x, y;
        Vertex(const float x, const float y) noexcept
            : x(x), y(y) {}
    };

    class D2D_API Actor
    {
    private:
        d2d::Color mColor;
        std::string mVertexShaderFile, mFragShaderFile;
        std::vector<Vertex> mVertices;
        Transform mTransform;
        int mUsage;

    public:

        Actor();
        Actor(const int usage, const d2d::Color& c, const std::string& shaderFile, const std::string &fragShaderFile, const std::vector<Vertex>& vertices);

        void AddVertex(const Vertex& vertex);
        void AddVertex(const float x, const float y);

        void ChangeColor(const float r, const float g, const float b, const float a);

        void ChangeColor(const float r, const float g, const float b);

        void ChangeColor(const float val);

        void ChangeColor(const d2d::Color& color);

        void SetUsage(const int usage);

        void SetTransform(const float xPos, const float yPos, const float rotation, const float xScale, const float yScale);

        void Draw(const glm::mat4& projection, uint drawType);

    };
    
} // namespace d2d::renderer