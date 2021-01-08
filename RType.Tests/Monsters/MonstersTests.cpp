#include "pch.h"
#include "CppUnitTest.h"

#include <Reloader/Loader.hpp>
#include <Reloader/Interfaces/IMonster.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RTypeTests::MonstersTests
{
	TEST_CLASS(Monsters)
	{
	public:
		TEST_METHOD(Monster_Load_DynamicLibrary)
		{
			auto loader = Loader::CreateLoader();

			try
			{
				loader->Load("LinearShootingMaster");
			}
			catch (...)
			{
			}
		}

	public:
		TEST_METHOD(Monster_Instantiate)
		{
			auto loader = Loader::CreateLoader();

			try
			{
				loader->Load("LinearShootingMaster");

				const auto t = loader->Instantiate<IMonster>("Instantiate");

				Assert::IsNotNull(t.get());
			}
			catch (...)
			{
			}
		}

	public:
		TEST_METHOD(Monster_Instantiate_GetId)
		{
			auto loader = Loader::CreateLoader();

			try
			{
				loader->Load("LinearShootingMaster");

				const auto t = loader->Instantiate<IMonster>("Instantiate");

				Assert::IsNotNull(t.get());
				Assert::AreNotSame(static_cast<std::size_t>(460000), t->GetId());
			}
			catch (...)
			{
			}
		}

	public:
		TEST_METHOD(Monster_Instantiate_GetBulletPosition)
		{
			auto loader = Loader::CreateLoader();
			

			try
			{
				loader->Load("LinearShootingMaster");

				const auto t = loader->Instantiate<IMonster>("Instantiate");

				Assert::IsNotNull(t.get());

				const auto _ = t->Shoot();

				Assert::AreEqual(-20.0f, t->GetBulletPosition(0).first);
				Assert::AreEqual(0.0f, t->GetBulletPosition(0).second);
			}
			catch (...)
			{
			}

		}

	public:
		TEST_METHOD(Monster_Instantiate_GetBullets)
		{
			auto loader = Loader::CreateLoader();

			try
			{
				loader->Load("LinearShootingMaster");

				const auto t = loader->Instantiate<IMonster>("Instantiate");

				Assert::IsNotNull(t.get());
				Assert::AreEqual(static_cast<std::size_t>(0), t->GetBullets());

				const auto _ = t->Shoot();

				Assert::AreEqual(static_cast<std::size_t>(1), t->GetBullets());
			}
			catch (...)
			{
			}
		}

	public:
		TEST_METHOD(Monster_Instantiate_GetPosition)
		{
			auto loader = Loader::CreateLoader();

			try
			{
				loader->Load("LinearShootingMaster");

				const auto t = loader->Instantiate<IMonster>("Instantiate");

				Assert::IsNotNull(t.get());
				Assert::AreEqual(1700.0f, t->GetPosition().first);
				Assert::AreEqual(225.0f, t->GetPosition().second);
			}
			catch (...)
			{
			}
		}
	};
}
