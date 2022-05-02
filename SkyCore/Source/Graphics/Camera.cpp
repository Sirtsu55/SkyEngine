#include "SkyCore.h"
#include "Camera.h"

namespace sky
{
	Camera::Camera(const CameraInfo& info)
		:m_Info(info)
	{
		m_ProjectionMat = glm::perspective(m_Info.FOV, m_Info.AspectRatio, m_Info.Near, m_Info.Far);

	}

	Camera::~Camera()
	{
        if (s_AciveCamera == this)
        {
            s_AciveCamera = nullptr;
        }
	}

    void Camera::Move(const glm::vec3& Direction)
    {
        m_Info.CameraPos += Direction * m_Info.CameraSpeed * m_Info.CameraFront;
    }


    void Camera::MoveForward(const float amount)
    {
        m_Info.CameraPos += amount * m_Info.CameraSpeed * m_Info.CameraFront;
    }    


    void Camera::MoveRight(const float amount)
    {
        m_Info.CameraPos += amount * glm::normalize(glm::cross(m_Info.CameraFront, m_Info.CameraUp)) * m_Info.CameraSpeed;
    }

    void Camera::LookUp(const float amount)
    {
        if (m_Info.Pitch > 89.0f)
        {
            m_Info.Pitch = 89.0f;
            return;
        }
        else if(m_Info.Pitch < -89.0f)
        {
            m_Info.Pitch = -89.0f;
            return;
        }

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Info.Yaw)) * cos(glm::radians(m_Info.Pitch));
        direction.y = sin(glm::radians(m_Info.Pitch));
        direction.z = sin(glm::radians(m_Info.Yaw)) * cos(glm::radians(m_Info.Pitch));
        m_Info.CameraFront = glm::normalize(direction);

        m_Info.Pitch += amount * m_Info.CameraRotationSpeed;

        
    }

    void Camera::LookRight(const float amount)
    {

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Info.Yaw)) * cos(glm::radians(m_Info.Pitch));
        direction.y = sin(glm::radians(m_Info.Pitch));
        direction.z = sin(glm::radians(m_Info.Yaw)) * cos(glm::radians(m_Info.Pitch));
        m_Info.CameraFront = glm::normalize(direction);


        m_Info.Yaw += amount * m_Info.CameraRotationSpeed;
    }


    void Camera::SetFOV(float FOV)
    {
        m_Info.FOV = FOV;
        m_ProjectionMat = glm::perspective(m_Info.FOV, m_Info.AspectRatio, m_Info.Near, m_Info.Far);
    }

    void Camera::RotateAngle(float angle, const glm::vec3& axis)
    {
        m_Info.CameraFront = glm::rotate(m_Info.CameraFront, glm::radians(angle), axis);
    }

    void Camera::RotateRadians(float angle, const glm::vec3& axis)
    {
        m_Info.CameraFront = glm::rotate(m_Info.CameraFront, angle, axis);
    }
    void Camera::Update()
    {
        m_ViewMat = glm::lookAt(m_Info.CameraPos, m_Info.CameraPos + m_Info.CameraFront , m_Info.CameraUp);
        m_MVP = m_ProjectionMat * m_ViewMat;
    }
    const Camera& Camera::GetActiveCamera()
    {
        if (s_AciveCamera == nullptr)
        {
            LOG_CRITICAL("[CAMERA]: No active camera bound and trying to access active camera");
        }
        return *s_AciveCamera;
    }
}