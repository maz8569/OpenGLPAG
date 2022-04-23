#pragma once
#include "glm/glm.hpp"
#include <string>
#include "typedefs.h"
#include <vector>
#include <Scene/GObject.h>
#include "Camera.h"

namespace GameEngine {
	class Scene
	{
	private:
		std::string m_name;
		Ref<GObject> m_root;
		std::vector<Ref<GObject>> m_GObjects;
		Ref<Camera> m_camera;

	public:
		glm::mat4 m_lightSpace;

		Scene(std::string name);
		//virtual ~Scene();

		void Start();
		void Update();
		void FixedUpdate();
		void LateUpdate();
		void Render();

		virtual Ref<GObject> getObjectByName(const std::string& name);
		virtual std::vector<Ref<GObject>> getAllObjects();
		virtual std::vector<Ref<GObject>> getAllObjectsByName(const std::string& name);
		virtual Ref<GObject> getObjectByID(unsigned int ID);
		
		Ref<Camera> getCamera();
	};
}

