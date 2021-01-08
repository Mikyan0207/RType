#include "pch.h"
#include "CppUnitTest.h"

#include <Entities/Entity.hpp>
#include <Systems/ButtonSystem.hpp>
#include <Components/Button.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::Systems::ButtonSystemTests
{
	TEST_CLASS(System_ButtonSystem)
	{
	public:
		TEST_METHOD(ButtonSystem_Initialize_Add_Entity)
		{
			Entity e(1);
			ButtonSystem btnSys(1, nullptr);
			auto* button = new Button();

			e.AddComponent(button, Button::Id);
			btnSys.OnEntityCreated(e);

			Assert::AreEqual(static_cast<std::size_t>(1), btnSys.GetComponents().size());
		}

	public:
		TEST_METHOD(ButtonSystem_Initialize_Remove_Entity)
		{
			Entity e(1);
			ButtonSystem btnSys(1, nullptr);
			auto* button = new Button();

			e.AddComponent(button, Button::Id);
			btnSys.OnEntityCreated(e);

			Assert::AreEqual(static_cast<std::size_t>(1), btnSys.GetComponents().size());

			btnSys.OnEntityDestroyed(e.GetId());

			Assert::AreEqual(static_cast<std::size_t>(0), btnSys.GetComponents().size());
		}
	};
}
