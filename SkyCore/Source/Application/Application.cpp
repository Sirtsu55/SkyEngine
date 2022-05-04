#include "SkyCore.h"
#include "Application/Application.h"
#include "Window/Window.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"
#include "Input/Input.h"


//TODO: Have to add a external project to handle this

namespace sky
{

	void CameraMovements(MouseData data)
	{
		Application* app = ReCast<Application*>(data.UserPointer);


		app->cam->LookUp(-data.MouseOffset.y * data.Delta);
		app->cam->LookRight(-data.MouseOffset.x * data.Delta);
	}
	Application::Application()
	{


	}

	Application::~Application()
	{
	}

	
	void ForwardMove(InputState state, InputData data)
	{
		Application* app = ReCast<Application*>(data.UserPointer);

		if (state == InputState::Pressed)
		{
			app->cam->MoveForward(data.Delta);
		}
	}
	void rightMove(InputState state, InputData data)
	{
		Application* app = ReCast<Application*>(data.UserPointer);
		if (state == InputState::Pressed)
		{
			app->cam->MoveRight(data.Delta);
		}
	}
	void leftMove(InputState state, InputData data)
	{
		Application* app = ReCast<Application*>(data.UserPointer);
		if (state == InputState::Pressed)
		{
			app->cam->MoveRight(-data.Delta);
		}
	}
	void BackMove(InputState state, InputData data)
	{
		Application* app = ReCast<Application*>(data.UserPointer);
		if (state == InputState::Pressed)
		{
			app->cam->MoveForward(-data.Delta);
		}
	}
	void Application::Init()
	{

		sky::Window::CreateInfo info{};

		info.name = "Sky Engine";
		info.xRes = 1280;
		info.yRes = 720;
		AppWindow = CreateSptr<Window>(info);

	}
	void Application::Start()
	{
		MeshConfig mconf{};

		mconf.MeshFile = "C:/Users/srija/Documents/3dModels/DamagedHelmet.glb";
		//mconf.MeshFile = "C:/Users/srija/Documents/3dModels/sculpt.gltf";
		//mconf.MeshFile = "C:/Users/srija/Documents/3dModels/car.glb";
		mconf.Material = true;

		m = CreateSptr<Mesh>(mconf);

		mconf.MeshFile = "C:/Users/srija/Documents/3dModels/sculpt.gltf";
		mconf.Material = true;

		m2 = CreateSptr<Mesh>(mconf);
		m2->Transform = glm::translate(m2->Transform, glm::vec3(0.0f, 5.0f, 0.0f));

		CameraInfo inf;
		inf.Far = 1000.0f;
		inf.CameraSpeed = 4.0f;
		inf.CameraRotationSpeed = 400.0f;
		inf.CameraPos = glm::vec3(0.0f, 0.0f, -5.0f);

		cam = CreateSptr<Camera>(inf);
		cam->Activate();
		
		
		
		Input::SetKeyCallback(InputKey::W, ForwardMove,	this);
		Input::SetKeyCallback(InputKey::A, leftMove,	this);
		Input::SetKeyCallback(InputKey::D, rightMove,	this);
		Input::SetKeyCallback(InputKey::S, BackMove,	this);
		Input::SetMousePosCallback(CameraMovements,		this);


	}


	void Application::OnUpdate(float DeltaTime)
	{

		//sdr->Bind();
		//glBindVertexArray(VAO);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		cam->Update();


		//m->Transform = glm::rotate(m->Transform, 2.0f * DeltaTime, glm::vec3(0.0f, 0.0f, 0.0f));

		//glClearColor(0.1f, 0.3f, 0.2f, 1.0f);


		m->Draw();
		m2->Draw();
	}

	void Application::OnWidgetRender(float Deltatime)
	{
		ImGui::Begin("Window");

		ImGui::Text("Delta Time: %f", AppWindow->GetDeltaTime());
		ImGui::Text("FPS: %f", 1/AppWindow->GetDeltaTime());

		ImGui::End();

	}


	
	void Application::OnDestroy()
	{

	}


}