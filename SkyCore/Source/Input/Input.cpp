#include "SkyCore.h"
#include "Window/Window.h"
#include "Input.h"

namespace sky
{
	void Input::SetListeningWindow(Window* win)
	{
		s_ListeningWindow = win;

		
	}

	void Input::SetKeyCallback(InputKey key, InputKeyCallback cback, void* userptr)
	{
		
		auto& vec = s_CallbacksMap[key];
		vec.emplace_back(cback, userptr);

	}

	void Input::SetMousePosCallback(MouseCallback cback, void* userPtr)
	{
		s_MouseCbackData.Callback = cback;
		s_MouseCbackData.UserPointer = userPtr;
	}

	void Input::PollEvents()
	{
		for (auto& [key, vec] : s_CallbacksMap)
		{
			InputState state = (InputState)glfwGetKey(s_ListeningWindow->GetGLFWwindow(), (int)key);
			for (int i = 0; i < vec.size(); i++)
			{
				vec[i].Callback(state, { vec[i].UserPointer, s_ListeningWindow->GetDeltaTime()});
			}
			
		}
	}

	void Input::CallMouseCback(const glm::vec2& mousepos)
	{
		MouseData data{};
		data.MouseOffset = MouseData::MouseLastPos - mousepos;
		data.MousePos = mousepos;
		data.UserPointer = s_MouseCbackData.UserPointer;
		data.Delta = s_ListeningWindow->GetDeltaTime();

		if (s_MouseCbackData.Callback)
		{
			s_MouseCbackData.Callback(data);
		}
		MouseData::MouseLastPos = mousepos;
	}

	InputState Input::GetKeyState(InputKey key)
	{
		return (InputState)glfwGetKey(s_ListeningWindow->GetGLFWwindow(), (int)key);
	}

}