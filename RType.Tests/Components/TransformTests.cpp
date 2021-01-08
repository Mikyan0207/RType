#include "pch.h"
#include "CppUnitTest.h"

#include <Components/Transform.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::Components::TransformTests
{
	TEST_CLASS(Component_Transform)
	{
	public:
		TEST_METHOD(Transform_Initialize)
		{
			const auto transform = Transform(sf::Vector2f(1,1));

			Assert::AreEqual(1.0f, transform.GetPosition().x);
			Assert::AreEqual(1.0f, transform.GetPosition().y);
		}

	public:
		TEST_METHOD(Transform_GetPosition)
		{
			const auto transform = Transform(sf::Vector2f(1, 1));

			Assert::AreEqual(1.0f, transform.GetPosition().x);
			Assert::AreEqual(1.0f, transform.GetPosition().y);
		}

	public:
		TEST_METHOD(Transform_GetRotation)
		{
			const auto transform = Transform(sf::Vector2f(1, 1), 15.0f);

			Assert::AreEqual(15.0f, transform.GetRotation());
		}

	public:
		TEST_METHOD(Transform_GetScale)
		{
			const auto transform = Transform(sf::Vector2f(1, 1), 15.0f, sf::Vector2f(3.0f, 3.0f));

			Assert::AreEqual(15.0f, transform.GetRotation());
			Assert::AreEqual(3.0f, transform.GetScale().x);
			Assert::AreEqual(3.0f, transform.GetScale().y);
		}

	public:
		TEST_METHOD(Transform_SetPosition)
		{
			auto transform = Transform(sf::Vector2f(1, 1));

			transform.SetPosition({5.0f, 25.0f});
			
			Assert::AreEqual(5.0f, transform.GetPosition().x);
			Assert::AreEqual(25.0f, transform.GetPosition().y);
		}

	public:
		TEST_METHOD(Transform_SetScale)
		{
			auto transform = Transform(sf::Vector2f(1, 1));

			transform.SetScale({ 5.0f, 25.0f });

			Assert::AreEqual(5.0f, transform.GetScale().x);
			Assert::AreEqual(25.0f, transform.GetScale().y);
		}

	public:
		TEST_METHOD(Transform_SetRotation)
		{
			auto transform = Transform(sf::Vector2f(1, 1));

			transform.SetRotation(28.5f);

			Assert::AreEqual(28.5f, transform.GetRotation());
		}

	public:
		TEST_METHOD(Transform_SetVelocity)
		{
			auto transform = Transform(sf::Vector2f(1,1));

			transform.SetVelocity(11.5004);

			Assert::AreEqual(11.5004, transform.GetVelocity());
		}

	public:
		TEST_METHOD(Transform_SetRect)
		{
			auto transform = Transform(sf::Vector2f(1, 1));

			transform.SetRect({11.50f,9.50f,90.0f,250.0f});

			Assert::AreEqual(11.50f, transform.GetRect().left);
			Assert::AreEqual(9.50f, transform.GetRect().top);
			Assert::AreEqual(90.0f, transform.GetRect().width);
			Assert::AreEqual(250.0f, transform.GetRect().height);
		}
	};
}