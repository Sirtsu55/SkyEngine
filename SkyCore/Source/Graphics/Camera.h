#pragma once


namespace sky
{

	struct CameraInfo
	{
		glm::vec3 CameraPos		= glm::vec3(0.0f, 0.0f,  0.0f);
												
		glm::vec3 CameraUp		= glm::vec3(0.0f, 1.0f,  0.0f);
		glm::vec3 CameraFront	= glm::vec3(0.0f, 0.0f, 1.0f);

		float CameraSpeed = 1.0f;
		float CameraRotationSpeed = 1.0f;

		float FOV = 45.0f;

		float AspectRatio = 16 / 9;

		float Near = 0.1f;
		float Far = 100.0f;


		float Yaw = 0.0f;
		float Pitch = 0.0f;
	};


	class Camera
	{
	public:
		Camera(const CameraInfo& info);
		~Camera();

		Camera(Camera&) = delete;
		Camera& operator=(Camera&) = delete;


		glm::vec3 GetLocation() const { return m_Info.CameraPos; }

		const glm::mat4& GetViewProjMatRef() const { return m_MVP; }
		glm::mat4 GetViewProjMat() const { return m_MVP; }
		
		float GetFOV() const { return m_Info.FOV; }

		void Move(const glm::vec3& Direction);

		void MoveForward(const float amount);
		void MoveRight(const float amount);


		void LookUp(const float amount);
		void LookRight(const float amount);

		void SetFOV(float FOV);

		void RotateAngle(float angle, const glm::vec3& axis);
		void RotateRadians(float angle, const glm::vec3& axis);

		void Activate() { s_AciveCamera = this; }
		void Deactivate() { s_AciveCamera = nullptr; }


		void Update();


		static const Camera& GetActiveCamera();
	private:


		CameraInfo m_Info;

		glm::mat4 m_ProjectionMat;
		glm::mat4 m_ViewMat;

		glm::mat4 m_MVP;

		inline static Camera* s_AciveCamera = nullptr;

	};



}