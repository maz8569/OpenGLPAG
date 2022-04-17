#pragma once
#include <rapidjson/document.h>     // rapidjson's DOM-style API
#include <rapidjson/prettywriter.h> // for stringify JSON

namespace GameEngine {
	class Json
	{
	public:
		rapidjson::Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
		Json() = default;

		int print();
	};
}

