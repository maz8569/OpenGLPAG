#pragma once

#include <string>
#include <vector>
#include <typedefs.h>
#include <Rendering/MasterRenderer.h>
#include <Scene/Scene.h>
#include <Rendering/WindowManager.h>

namespace GameEngine {

	enum GameState : uint8_t {
		MenuState = 0,
		PlayingState
	};

	class Application
	{
	public:
		WindowManager windowManager;

		Application();
		~Application();

		void OnUpdate();

		inline Scene* getScene() {
			return m_scene;
		}

		inline GameState getState()
		{
			return m_gameState;
		}

	private:
		void handleEvents();
		
		GameState m_gameState;
		bool m_cursorLocked;
		bool m_VSync = true;

		Scene* m_scene;

	};

}
