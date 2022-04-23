#include "ECS/ecsComponent.h"

typedef std::uint32_t uint32;

static uint32 componentID = 0;

uint32 GameEngine::BaseECSComponent::nextID()
{
	return componentID++;
}
