#include "Transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace d2d
{
    namespace renderer
    {
        Transform::Transform(const glm::vec2 &position, float rotation, const glm::vec2 &scale)
            : mPosition(position), mRotation(rotation), mScale(scale) {}

        Transform::Transform()
            : mPosition(glm::vec2(0.0f)), mRotation(0.f), mScale(glm::vec2(1.0f)) {}

        Transform::~Transform() {}

        glm::mat4 Transform::GetModel() const
        {
            glm::mat4 posMat(1.f), rotMat(1.f), sclMat(1.f);

            posMat = glm::translate(glm::vec3(mPosition, 1.f));

            auto rotZ = glm::rotate(mRotation, glm::vec3(0.f, 0, 1.0f));

            rotMat =  rotZ * (glm::mat4(1.f)) * (glm::mat4(1.f));

            sclMat = glm::scale(glm::vec3(mScale, 1.f));

            return posMat * rotMat * sclMat;

        }

        

    }
}