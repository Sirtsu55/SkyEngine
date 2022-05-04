#pragma once
#include "Graphics/VertexData.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/Mesh.h"


namespace sky
{
	class Window;

	class Application
	{
		Application();
		~Application();
		Application(const Application&) = delete;

		static inline Application* singletonApp = nullptr;
	public:


		uint32_t VBO0, VBO1, VAO;
		Sptr<Shader> sdr;


		Sptr<Window> AppWindow;
		Sptr<Camera> cam;


		Sptr<Mesh> m;
		Sptr<Mesh> m2;


		void Init();
		void Start();
		void OnUpdate(float DeltaTime);
		void OnWidgetRender(float Deltatime);
		void OnDestroy();



		
		static Application* GetApplication() 
		{
			if (singletonApp == nullptr)
			{
				singletonApp = new Application();
			}
			return singletonApp;
		}
		static void _DestroyApp()
		{
			delete singletonApp;
			
		}
	};

}