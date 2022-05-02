#include "SkyCore.h"
#include "Window/Window.h"
#include "Input/Input.h"


namespace sky
{




	Window::Window(const CreateInfo& cInfo)
		: m_xRes(cInfo.xRes), m_yRes(cInfo.yRes)
	{

		glfwSetErrorCallback(errorcallglfw);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


		m_Window = glfwCreateWindow(m_xRes, m_yRes, cInfo.name.c_str(), NULL, NULL);
		if (!m_Window)
		{
			throw std::exception("WINDOW CREATION FAILED");
			glfwTerminate();

		}
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, resizewindowcallback);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowFocusCallback(m_Window, window_focus_callback);
		glfwSetCursorPosCallback(m_Window, mousecbackglfw);

		Window::InitGLAD();

		Input::SetListeningWindow(this);

		glfwSwapInterval(0);

		//Imgui 

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 460");


		ImGui::StyleColorsDark();


		glDebugMessageCallback(GLCallback, nullptr);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

	}
		


	bool Window::Active()
	{
		return glfwWindowShouldClose(m_Window) ? false : true;
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
		Input::PollEvents();
	}

	void Window::UpdateMouse(const glm::vec2& pos)
	{
		Input::CallMouseCback(pos);
	}

	void Window::CreateFrambuffers()
	{
	}

	void Window::CreateGBuffers()
	{
	}

	void Window::DeferredShade()
	{
	}

	void Window::StartFrame()
	{
		FrameTimer.Start();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	}

	void Window::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
		PollEvents();

		DeltaTime = FrameTimer.Endd();
	}

	void Window::OnDestroy()
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, true);
	}





	bool Window::InitWindow()
	{
		if (!glfwInit())
		{
			GLFWInitialized = false;
			return false;
		}
		else
		{
			GLFWInitialized = true;
		}
		ImGui::CreateContext();

		return true;
	}

	void Window::TerminateWindow()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();

		glfwTerminate();
		GLFWInitialized = false;

	}

	bool Window::InitGLAD()
	{
		GLFWInitialized = true;
		return gladLoadGL();
	}

	void Window::Resize(int x, int y)
	{
		m_xRes = x;
		m_yRes = y;
	}

	void resizewindowcallback(GLFWwindow* win, int x, int y)
	{
		Window* window = ReCast<Window*>(glfwGetWindowUserPointer(win));

		window->Resize(x, y);
	}

	void window_focus_callback(GLFWwindow* win, int focused)
	{
		Window* window = ReCast<Window*>(glfwGetWindowUserPointer(win));
		if (focused)
		{
			Input::SetListeningWindow(window);
		}

	}

	void errorcallglfw(int ecode, const char* str)
	{
		LOG_ERROR("[GLFW][CODE:{}]: {}", ecode, str);
	}

	void mousecbackglfw(GLFWwindow* win, double x, double y)
	{
		Window* window = ReCast<Window*>(glfwGetWindowUserPointer(win));
		window->UpdateMouse(glm::fvec2(x, y));

	}

	void GLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
		{
			LOG_CRITICAL("[OPENGL][HIGH SEVERITY]: {}", message);
			break;
		}
		case GL_DEBUG_SEVERITY_MEDIUM:
		{
			LOG_ERROR("[OPENGL][Medium SEVERITY]: {}", message);
			break;
		}
		case GL_DEBUG_SEVERITY_LOW:
		{
			LOG_WARN("[OPENGL][LOW SEVERITY]: {}", message);
			break;
		}
		case GL_DEBUG_SEVERITY_NOTIFICATION:
		{
			LOG_TRACE("[OPENGL][NOTIFICATION]: {}", message);
			break;
		}

		}
	}


}


