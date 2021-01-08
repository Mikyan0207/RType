#include "pch.h"
#include "CppUnitTest.h"

#include <Components/Drawable.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::Components::DrawableTests
{
	TEST_CLASS(Component_Drawable)
	{
	public:
		TEST_METHOD(Drawable_Initialize)
		{
			const auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			Assert::AreEqual(0, drawable.GetSpriteRect().left);
		}

	public:
		TEST_METHOD(Drawable_GetAnimationFrameNb)
		{
			auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			drawable.SetAnimated(true, 5, 0.9);
			
			Assert::AreEqual( static_cast<size_t>(5), drawable.GetAnimationFrameNb());
		}

	public:
		TEST_METHOD(Drawable_GetCurrentAnimationFrame)
		{
			auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			drawable.SetAnimated(true, 5, 0.9);
			
			Assert::AreEqual(static_cast<size_t>(0), drawable.GetCurrentAnimationFrame());
		}

	public:
		TEST_METHOD(Drawable_SetPosition_GetPosition)
		{
			auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			drawable.SetPosition({154.5f, 168.78f});
			
			Assert::AreEqual(154.5f, drawable.GetPosition().x);
			Assert::AreEqual(168.78f, drawable.GetPosition().y);
		}

	public:
		TEST_METHOD(Drawable_GetType)
		{
			const auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			Assert::AreEqual(static_cast<int>(Drawable::DrawableType::Object), static_cast<int>(drawable.GetType()));
		}

	public:
		TEST_METHOD(Drawable_SetScale)
		{
			auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			drawable.SetScale({2.5f, 2.5f});

			Assert::AreEqual(2.5f, drawable.GetScale().x);
			Assert::AreEqual(2.5f, drawable.GetScale().y);
		}

	public:
		TEST_METHOD(Drawable_SetRotation_GetRotation)
		{
			auto drawable = Drawable(Drawable::DrawableType::Object, "Player_0.png", sf::IntRect(0, 0, 100, 100));

			drawable.SetRotation(12.0f);

			Assert::AreEqual(12.0f, drawable.GetRotation());
		}
	};
}