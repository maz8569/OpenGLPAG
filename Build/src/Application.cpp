#include "Application.h"

namespace GameEngine {

	Application app;

	Application::Application()
		: m_gameState(GameState::MenuState), m_cursorLocked(true)
	{
		//windowManager = WindowManager();
	}

	Application::~Application()
	{
		
	}

	void Application::OnUpdate()
	{

	}

	void Application::handleEvents()
	{

	}

}