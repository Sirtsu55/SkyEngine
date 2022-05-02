#include "SkyCore.h"
#include "Application/Application.h"
#include "Window/Window.h"


static bool Init()
{
	Log::Init();
	TimerWriter::StartSession("Sky Engine Profile");

	if (!sky::Window::InitWindow())
		return false;
	return true;

}
static void DeInit()
{
	sky::Window::TerminateWindow();
	TimerWriter::EndSession();

}

int ::main(void)
{
	if (!Init())
		return 1;

	sky::Application* App = sky::Application::GetApplication();

	App->Init();


	App->Start();
	while (App->AppWindow->Active())
	{
		PROFILE_FUNCTION_NO_LOG();
		App->AppWindow->StartFrame();

		App->OnUpdate(App->AppWindow->GetDeltaTime());
		App->OnWidgetRender(App->AppWindow->GetDeltaTime());

		App->AppWindow->EndFrame();


	}
	App->AppWindow->OnDestroy();
	App->OnDestroy();


	sky::Application::_DestroyApp();

	DeInit();
}