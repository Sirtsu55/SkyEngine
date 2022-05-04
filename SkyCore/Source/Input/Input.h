#include "SkyCore.h"
#include "Input/InputKeys.h"




namespace sky
{

	class Window;
	//TODO: Better implementation of Input

	enum class InputState
	{
		Pressed = GLFW_PRESS, Released = GLFW_RELEASE
	};

	//Passed to callbacks
	struct InputData
	{
		void* UserPointer;
		float Delta;

	};
	struct MouseData
	{
		glm::vec2 MousePos;

		glm::vec2 MouseOffset;


		float Delta;
		void* UserPointer;


		static inline glm::vec2 MouseLastPos = glm::vec2(0.0f);
	};

	typedef void(*InputKeyCallback)(InputState, InputData);
	typedef void(*MouseCallback)(MouseData);

	//Used to store callback info

	struct MouseCallbackData
	{
		MouseCallback Callback;
		void* UserPointer;
	};
	//Used to store callback info
	struct CallbackData
	{
		InputKeyCallback Callback;
		void* UserPointer;
	};

	class Input
	{
	public:


		static InputState GetKeyState(InputKey key);
		static void SetListeningWindow(Window* win);

		static void SetKeyCallback(InputKey key, InputKeyCallback cback, void* userptr);
		static void SetMousePosCallback(MouseCallback cback, void* userPtr);
		
	private:
		static void PollEvents();

		static void CallMouseCback(const glm::vec2& mousepos);
		inline static Window* s_ListeningWindow = nullptr;
		inline static std::unordered_map<InputKey, std::vector<CallbackData>> s_CallbacksMap;

		inline static MouseCallbackData s_MouseCbackData;
		friend class Window;

	};

}