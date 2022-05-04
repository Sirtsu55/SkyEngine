#pragma once
#include <GLFW/glfw3.h>
#include "Graphics/RenderCanvas.h"

int main(void);


namespace sky
{
	class Window
	{

	public:

		struct CreateInfo
		{
			std::string name;
			int xRes;
			int yRes;
		};


		Window(const CreateInfo& cInfo);
		~Window() = default;

		Window(const Window&) = delete;

		bool Active();



		void Close();



		GLFWwindow* GetGLFWwindow() const { return m_Window; }

		int GetX() const { return m_xRes; }
		int GetY() const { return m_yRes; }
		void Resize(int x, int y);

		float GetDeltaTime() const { return static_cast<float>(DeltaTime); }

		//returns double
		double GetDeltaTimed() const { return DeltaTime; }



		void PollEvents();

		void StartFrame();
		

		void EndFrame();

		void OnDestroy();


		//Statics
		static bool InitWindow();
		static void TerminateWindow();

		static bool InitGLAD();
		
	private:

		//Only called by mousecbackglfw
		void UpdateMouse(const glm::vec2& pos);


		ImGuiContext* m_ImguiCtx;
		GLFWwindow* m_Window;

		SimpleTimer FrameTimer;

		int m_xRes;
		int m_yRes;

		Sptr<RenderCanvas> m_Canvas;
		Sptr<Shader> m_DeferredShader;


		mutable double DeltaTime = 0.0f;

		inline static bool GLFWInitialized = false;
		inline static bool GLADInitialized = false;


		//Friends
		friend int ::main();
		friend void mousecbackglfw(GLFWwindow* win, double x, double y);
	};
	void window_focus_callback(GLFWwindow* window, int focused);
	void resizewindowcallback(GLFWwindow* win, int x, int y);
	void errorcallglfw(int ecode, const char* str);
	void GLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	void mousecbackglfw(GLFWwindow* win, double x, double y);
}