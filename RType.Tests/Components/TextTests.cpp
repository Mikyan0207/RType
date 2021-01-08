#include "pch.h"
#include "CppUnitTest.h"

#include <Components/Text.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::Components::TextTests
{
	TEST_CLASS(Component_Text)
	{
	public:
		TEST_METHOD(Text_Initialize)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2,2), 30, sf::Color::Black, sf::Font()));

			Assert::AreEqual(std::string("Ceci est un test"), text.GetString());
			Assert::AreEqual(2.0f, text.GetTextPosition().x);
			Assert::AreEqual(2.0f, text.GetTextPosition().y);
		}

	public:
		TEST_METHOD(Text_Position)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			Assert::AreEqual(2.0f, text.GetTextPosition().x);
			Assert::AreEqual(2.0f, text.GetTextPosition().y);
		}

	public:
		TEST_METHOD(Text_CharacterSize)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			Assert::AreEqual(static_cast<uint32_t>(30), text.GetTextCharSize());
		}

	public:
		TEST_METHOD(Text_Color)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			Assert::AreEqual(sf::Color::Black.toInteger(), text.GetTextColor().toInteger());
		}

	public:
		TEST_METHOD(Text_Content)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			Assert::AreEqual(std::string("Ceci est un test"), text.GetString());
		}

	public:
		TEST_METHOD(Text_SetString)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			text.SetString("Ce test est incroyable");

			Assert::AreEqual(std::string("Ce test est incroyable"), text.GetString());
		}

	public:
		TEST_METHOD(Text_SetCharSize)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			text.SetTextCharSize(15);

			Assert::AreEqual(static_cast<uint32_t>(15), text.GetTextCharSize());
		}

	public:
		TEST_METHOD(Text_SetTextPosition)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			text.SetTextPosition(sf::Vector2f(15,15));

			Assert::AreEqual(15.0f, text.GetTextPosition().x);
			Assert::AreEqual(15.0f, text.GetTextPosition().y);
		}

	public:
		TEST_METHOD(Text_SetColor)
		{
			auto text = Text();

			Assert::IsTrue(text.Initialize("Ceci est un test", sf::Vector2f(2, 2), 30, sf::Color::Black, sf::Font()));

			text.SetTextColor(sf::Color::Blue);

			Assert::AreEqual(sf::Color::Blue.toInteger(), text.GetTextColor().toInteger());
		}
	};
}