#pragma once
#include <cstdint>

#define NULL_ENTITY_HANDLE nullptr
namespace GameEngine {

	typedef void* EntityHandle;
	typedef std::uint32_t uint32;

	struct BaseECSComponent {
		static uint32 nextID();
		EntityHandle entity = NULL_ENTITY_HANDLE;
	};

	template<typename T>
	struct ECSComponent : public BaseECSComponent
	{
		//static const ECSComponentCreateFunction CREATE_FUNCTION;
		//static const ECSComponentFreeFunction FREE_FUNCTION;
		//static const uint32 ID = BaseECSComponent::nextID();
		static const size_t SIZE;
	};

	//template<typename T>
	//const uint32 ECSComponent<T>::ID(BaseECSComponent::nextID());

	template<typename T>
	const size_t ECSComponent<T>::SIZE(sizeof(T));

	struct testECSComponent : public ECSComponent<testECSComponent>
	{
		float x;
		float y;
	};
}
