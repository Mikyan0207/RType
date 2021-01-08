#include "pch.h"
#include "CppUnitTest.h"

#include <Entities/Entity.hpp>
#include <Components/Button.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::Entities::EntityTests
{
	TEST_CLASS(EntityTests)
	{
	public:
		TEST_METHOD(Entity_AddComponent)
		{
			Entity e(1);
			auto* button = new Button();

			e.AddComponent(button, Button::Id);

			Assert::AreEqual(static_cast<size_t>(1), e.GetSize());
		}

	public:
		TEST_METHOD(Entity_GetComponent)
		{
			Entity e(1);
			auto* button = new Button();

			e.AddComponent(button, Button::Id);

			const auto c = e.GetComponent<Button>();

			Assert::IsTrue(c.has_value());

			if (c.has_value())
			{
				Assert::IsNotNull(c.value());
			}
		}

	public:
		TEST_METHOD(Entity_RemoveComponent)
		{
			Entity e(1);
			auto* button = new Button();

			e.AddComponent(button, Button::Id);
			Assert::AreEqual(static_cast<size_t>(1), e.GetSize());
			
			e.RemoveComponent<Button>();
			Assert::AreEqual(static_cast<size_t>(0), e.GetSize());
		}

	public:
		TEST_METHOD(IEntity_AsEntity)
		{
			IEntity* e = new Entity(1);

			Assert::IsNotNull(e->AsEntity());
			
			delete e;
		}
	};
}
