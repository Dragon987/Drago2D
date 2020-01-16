#pragma once

#include "Core.hpp"

#include <glm/glm.hpp>

namespace d2d
{
    namespace renderer
    {
        class D2D_API Transform
        {
        private:
            glm::vec2 mPosition, mScale;
            float mRotation;

        public:
            Transform(const glm::vec2 &position, float rotation, const glm::vec2 &scale);
            Transform();

            ~Transform();

            glm::mat4 GetModel() const;

            inline glm::vec2 GetPosition() const noexcept { return mPosition; }
            inline float GetRotation() const noexcept { return mRotation; }
            inline glm::vec2 GetScale() const noexcept    { return mScale; }

            inline void SetPositionX(float x) { mPosition.x = x; }
            inline void SetPositionY(float y) { mPosition.y = y; }

            inline void SetPosition(float x, float y) { mPosition = glm::vec2(x, y); }
            inline void SetPosition(const glm::vec2 &position) { mPosition = position; };

            inline void Rotate(float angle) { mRotation = angle; }

            inline void SetScaleX(float x) { mScale.x = x; }
            inline void SetScaleY(float y) { mScale.y = y; }

            inline void SetScale(float x, float y) { mScale = glm::vec2(x, y); }
            inline void SetScale(const glm::vec2 &scale) { mScale = scale; };

        };
    }
}