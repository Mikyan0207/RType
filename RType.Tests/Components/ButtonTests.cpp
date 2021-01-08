#include "pch.h"
#include "CppUnitTest.h"

#include <Components/Button.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::Components::ButtonTests
{
	TEST_CLASS(Component_Button)
	{
	public:
		TEST_METHOD(Button_Initialize)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));
		}

	public:
		TEST_METHOD(Button_GetPosition)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			Assert::AreEqual(100.0f, button.GetPosition().x);
			Assert::AreEqual(100.0f, button.GetPosition().y);
		}

	public:
		TEST_METHOD(Button_GetSize)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			Assert::AreEqual(300.0f, button.GetSize().x);
			Assert::AreEqual(200.0f, button.GetSize().y);
		}
		
	public:
		TEST_METHOD(Button_GetText)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			Assert::AreEqual(std::string("ButtonText"), button.GetTextString().toAnsiString());
		}

	public:
		TEST_METHOD(Button_GetTextColor)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			Assert::AreEqual(sf::Color::Green.toInteger(), button.GetTextColor().toInteger());
		}

	public:
		TEST_METHOD(Button_SetPosition)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			button.SetPosition(sf::Vector2f(25,25));
			
			Assert::AreEqual(25.0f, button.GetPosition().x);
			Assert::AreEqual(25.0f, button.GetPosition().y);
		}

	public:
		TEST_METHOD(Button_SetSize)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			button.SetSize(sf::Vector2f(250, 150));

			Assert::AreEqual(250.0f, button.GetSize().x);
			Assert::AreEqual(150.0f, button.GetSize().y);
		}

	public:
		TEST_METHOD(Button_SetText)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			button.SetTextString("ButtonText v2");

			Assert::AreEqual(std::string("ButtonText v2"), button.GetTextString().toAnsiString());
		}

	public:
		TEST_METHOD(Button_SetTextColor)
		{
			auto button = Button();

			Assert::IsTrue(button.Initialize(sf::Vector2f(100, 100), sf::Vector2f(300, 200), "Texture will not load", sf::Font(), "ButtonText", 26, sf::Color::Green));

			button.SetTextColor(sf::Color::Yellow);

			Assert::AreEqual(sf::Color::Yellow.toInteger(), button.GetTextColor().toInteger());
		}
	};
}
