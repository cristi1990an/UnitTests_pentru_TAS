#include "pch.h"
#include "CppUnitTest.h"
#include <list>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include "../Static Vector/inc/static_vector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StaticVectorUnitTest
{
	TEST_CLASS(StaticVectorUnitTest)
	{
	public:
		
		TEST_METHOD(Initialization_1)
		{
			static_vector<int, 10> vec(10, 100);

			Assert::AreEqual(vec.size(), 10u);

			for (const auto& val : vec)
			{
				Assert::AreEqual(val, 100);
			}
		}

		TEST_METHOD(Initialization_2)
		{
			auto RunTimeExceptionThrower = []() {static_vector<int, 10> vec(11, 100); };

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Initialization_3)
		{
			static_vector<int, 10> vec = { 1,2,3,4,5,6,7,8,9 };

			Assert::AreEqual(vec.size(), 9u);

			for (int i = 1; const auto& val : vec)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Initialization_4)
		{
			auto RunTimeExceptionThrower = []()
			{
				static_vector<int, 10> vec = { 1,2,3,4,5,6,7,8,9,10,11 };
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Initialization_5)
		{
			static_vector<int, 10> vec(10);

			Assert::AreEqual(vec.size(), 10u);

			for (const auto val : vec)
			{
				Assert::AreEqual(val, 0);
			}
		}

		TEST_METHOD(Initialization_6)
		{
			auto RunTimeExceptionThrower = []()
			{
				static_vector<int, 10> vec(11);
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Initialization_7)
		{
			std::list<int> inputs = { 0,1,2,3,4,5,6,7,8,9 };

			static_vector<int, 10> vec(inputs.cbegin(), inputs.cend());

			for (int i = 0; const auto val : vec)
			{
				Assert::AreEqual(val, i++);
			}

			Assert::AreEqual(vec.size(), 10u);
		}

		TEST_METHOD(Initialization_8)
		{
			std::list<int> inputs = { 0,1,2,3,4,5,6,7,8,9,10 };

			auto RunTimeExceptionThrower = [&]()
			{
				static_vector<int, 10> vec(inputs.cbegin(), inputs.cend());
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Initialization_9)
		{
			static_vector<std::string, 50> vec_1(50, "Some long string because why not ... ... ... ");

			static_vector vec_2 = vec_1;

			Assert::IsTrue(std::equal(vec_1.cbegin(), vec_1.cend(), vec_2.cbegin(), vec_2.cend()));
		}

		TEST_METHOD(Initialization_10)
		{
			static_vector<std::string, 50> vec_1(50, "Some long string because why not ... ... ... ");

			static_vector<std::string, 100> vec_2;
			vec_2 = vec_1;

			Assert::AreEqual(vec_2.size(), 50u);
			Assert::AreEqual(vec_2.capacity(), 100u);
			Assert::IsTrue(std::equal(vec_1.cbegin(), vec_1.cend(), vec_2.cbegin(), vec_2.cend()));
		}

		TEST_METHOD(Initialization_11)
		{
			static_vector<int, 100> vec;

			for (int i = 1; i <= 50; i++)
			{
				vec.push_back(i);
			}

			Assert::AreEqual(vec.size(), 50u);

			for (int i = 1; const auto val : vec)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Initialization_12)
		{
			static_vector<std::vector<int>, 100> vec;

			for (int i = 1; i <= 50; i++)
			{
				vec.emplace_back(5, 100);
			}

			Assert::AreEqual(vec.size(), 50u);

			for (const auto& v : vec)
			{
				Assert::AreEqual(v.size(), 5u);
				for (const auto val : v)
				{
					Assert::AreEqual(val, 100);
				}
			}
		}

		TEST_METHOD(Initialization_13)
		{
			static_vector<int, 50> vec_1(50);

			std::iota(vec_1.begin(), vec_1.end(), 1);

			static_vector<int, 100> vec_2 = vec_1;

			Assert::AreEqual(vec_1.size(), vec_2.size());

			for (int i = 1; const auto val : vec_2)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Initialization_14)
		{
			static_vector<int, 50> vec_1(50);

			std::iota(vec_1.begin(), vec_1.end(), 1);

			static_vector<int, 100> vec_2;
			vec_2 = vec_1;

			Assert::AreEqual(vec_1.size(), vec_2.size());

			for (int i = 1; const auto val : vec_2)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Initialization_15)
		{
			static_vector<int, 50> vec_1(25);

			std::iota(vec_1.begin(), vec_1.end(), 1);

			static_vector<int, 25> vec_2 = vec_1;

			Assert::AreEqual(vec_1.size(), vec_2.size());

			for (int i = 1; const auto val : vec_2)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Initialization_16)
		{
			static_vector<int, 50> vec_1(25);

			std::iota(vec_1.begin(), vec_1.end(), 1);

			static_vector<int, 25> vec_2;
			vec_2 = vec_1;

			Assert::AreEqual(vec_1.size(), vec_2.size());

			for (int i = 1; const auto val : vec_2)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Initialization_17)
		{
			static_vector<int, 50> vec_1(26);

			std::iota(vec_1.begin(), vec_1.end(), 1);

			auto RunTimeExceptionThrower = [&]()
			{
				static_vector<int, 25> vec_2 = vec_1;
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Initialization_18)
		{
			static_vector<int, 50> vec_1(26);

			std::iota(vec_1.begin(), vec_1.end(), 1);

			auto RunTimeExceptionThrower = [&]()
			{
				static_vector<int, 25> vec_2;
				vec_2 = vec_1;
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Algorithms_1)
		{
			static_vector<int, 50> vec;

			std::random_device rnd_device;
			std::mt19937 engine{ rnd_device() };
			std::uniform_int_distribution<int> dist
			{ 
				std::numeric_limits<int>::min(),
				std::numeric_limits<int>::max()
			};

			std::generate_n(std::back_inserter(vec), 49, [&]()
				{
					return dist(engine);
				}
			);


			std::sort(vec.begin(), vec.end());

			Assert::IsTrue(std::is_sorted(vec.cbegin(), vec.cend()));
		}

		TEST_METHOD(Algorithms_2)
		{
			static_vector<int, 50> vec;

			std::random_device rnd_device;
			std::mt19937 engine{ rnd_device() };
			std::uniform_int_distribution<int> dist
			{
				std::numeric_limits<int>::min(),
				std::numeric_limits<int>::max()
			};

			std::generate_n(std::back_inserter(vec), 49, [&]()
				{
					return dist(engine);
				}
			);


			std::sort(vec.begin(), vec.end(), std::greater<>());

			Assert::IsTrue(std::is_sorted(vec.cbegin(), vec.cend(), std::greater<>()));
		}

		TEST_METHOD(Methods_1)
		{
			static_vector<int, 50> vec;

			for (int i = 1; i <= 50; i++)
			{
				vec.push_back(i);

				Assert::AreEqual(vec.size(), (size_t)i);
			}

			for (int i = 49; i >= 0; i--)
			{
				vec.pop_back();

				Assert::AreEqual(vec.size(), (size_t)i);
			}
		}

		TEST_METHOD(Methods_2)
		{
			static_vector<int, 50> vec(50);

			for (int i = 1; i <= 50; i++)
			{
				vec[i - 1] = i;

				Assert::AreEqual(vec[i - 1], i);
			}
		}

		struct WeirdStruct
		{
			int i;
			std::string str;
			float f;
		};

		TEST_METHOD(Methods_3)
		{
			static_vector<WeirdStruct, 50> vec;

			for (int i = 0; i < 50; i++)
			{
				vec.emplace_back(5, "5", 5.5f);
				Assert::AreEqual(vec.size(), (size_t)(i + 1));
			}

			for (const auto& structure : vec)
			{
				Assert::AreEqual(structure.i, 5);
				Assert::AreEqual(structure.str, std::string("5"));
				Assert::AreEqual(structure.f, 5.5f);
			}
		}

		TEST_METHOD(Method_4)
		{
			static_vector<int, 50> vec(50);

			auto RunTimeExceptionThrower = [&]()
			{
				vec.push_back(5);
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Method_5)
		{
			static_vector<int, 50> vec(50);

			auto RunTimeExceptionThrower = [&]()
			{
				vec.emplace_back(5);
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Method_6)
		{
			static_vector<int, 50> vec(50);

			for (int i = 1; i <= 50; i++)
			{
				vec.pop_back();
			}

			auto RunTimeExceptionThrower = [&]()
			{
				vec.pop_back();
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Method_7)
		{
			static_vector<int, 50> vec(50);

			auto OutOfRangeExceptionThrower = [&]()
			{
				vec[50];
			};

			Assert::ExpectException<std::out_of_range>(OutOfRangeExceptionThrower);
		}

		TEST_METHOD(Method_8)
		{
			static_vector<int, 50> vec(50);

			auto& const_vec = std::as_const(vec);

			auto OutOfRangeExceptionThrower = [&const_vec]()
			{
				const_vec[50];
			};

			Assert::ExpectException<std::out_of_range>(OutOfRangeExceptionThrower);
		}

		TEST_METHOD(Method_9)
		{
			static_vector<int, 10> vec(10);

			vec.assign({ 1,2,3,4 });

			Assert::AreEqual(vec.size(), 4u);

			for (int i = 1; const auto val : vec)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Method_10)
		{
			static_vector<int, 10> vec(10);

			vec.assign({ 0,1,2,3,4,5,6,7,8,9 });

			Assert::AreEqual(vec.size(), 10u);

			for (int i = 0; const auto val : vec)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Method_11)
		{
			static_vector<int, 10> vec(10);

			auto RunTimeExceptionThrower = [&]()
			{
				vec.assign({ 0,1,2,3,4,5,6,7,8,9,10 });
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Method_12)
		{
			static_vector<int, 10> vec(10);

			vec.assign(5, 5);

			Assert::AreEqual(vec.size(), 5u);

			for (const auto val : vec)
			{
				Assert::AreEqual(val, 5);
			}
		}

		TEST_METHOD(Method_13)
		{
			static_vector<int, 10> vec(10);

			vec.assign(10, 5);

			Assert::AreEqual(vec.size(), 10u);

			for (const auto val : vec)
			{
				Assert::AreEqual(val, 5);
			}
		}

		TEST_METHOD(Method_14)
		{
			static_vector<int, 10> vec(10);

			auto RunTimeExceptionThrower = [&]()
			{
				vec.assign(11, 5);
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Method_15)
		{
			static_vector<int, 10> vec;
			std::list input = { 1,2,3,4,5 };

			vec.assign(input.cbegin(), input.cend());

			Assert::AreEqual(vec.size(), 5u);

			for (int i = 1; const auto val : vec)
			{
				Assert::AreEqual(val, i++);
			}
		}

		TEST_METHOD(Method_16)
		{
			static_vector<int, 5> vec;
			std::list input = { 1,2,3,4,5,6 };

			auto RunTimeExceptionThrower = [&]()
			{
				vec.assign(input.cbegin(), input.cend());
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Method_17)
		{
			static_vector<int, 10> vec;
			char input[] = { 1,2,3,4,5 };

			vec.assign(&input[0], &input[5]);

			Assert::AreEqual(vec.size(), 5u);

			for (int i = 1; const auto val : vec)
			{
				Assert::AreEqual(val, i++);
			}
		}

		template<bool be_noexcept_moveable>
		struct MoveableObj
		{
			std::string message = "Has value";

			constexpr MoveableObj() noexcept = default;
			constexpr MoveableObj(const MoveableObj& other) noexcept
			{
				message = other.message;
			}
			constexpr MoveableObj(MoveableObj&& other) noexcept (be_noexcept_moveable)
			{
				other.message = "Value moved";
				message = "Has value";
			}
			constexpr auto& operator=(const MoveableObj& other) noexcept
			{
				message = other.message;
				return *this;
			}
			constexpr auto& operator=(MoveableObj&& other) noexcept(be_noexcept_moveable)
			{
				message = other.message;
				other.message = "Value moved";
				return *this;
			}
			constexpr ~MoveableObj() noexcept = default;
		};

		TEST_METHOD(Move_semantic_1)
		{
			static_vector<MoveableObj<true>, 100> vec_1(100);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}

			static_vector vec_2 = std::move(vec_1);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Value moved"));
			}

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_2)
		{
			static_vector<MoveableObj<true>, 100> vec_1(100);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}

			static_vector<MoveableObj<true>, 100> vec_2;
			
			vec_2 = std::move(vec_1);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Value moved"));
			}

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_3)
		{
			static_vector<MoveableObj<false>, 100> vec_1(100);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}

			static_vector vec_2 = std::move(vec_1);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_4)
		{
			static_vector<MoveableObj<false>, 100> vec_1(100);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}

			static_vector<MoveableObj<false>, 100> vec_2;

			vec_2 = std::move(vec_1);

			for (const auto& obj : vec_1)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_5)
		{
			static_vector<MoveableObj<true>, 50> vec_1(50);

			static_vector<MoveableObj<true>, 100> vec_2 = std::move(vec_1);

			Assert::AreEqual(vec_1.size(), 0u);
			Assert::AreEqual(vec_2.size(), 50u);

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_6)
		{
			static_vector<MoveableObj<true>, 50> vec_1(50);

			static_vector<MoveableObj<true>, 100> vec_2;
			vec_2 = std::move(vec_1);

			Assert::AreEqual(vec_1.size(), 0u);
			Assert::AreEqual(vec_2.size(), 50u);

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_7)
		{
			static_vector<MoveableObj<true>, 50> vec_1(25);

			static_vector<MoveableObj<true>, 25> vec_2 = std::move(vec_1);

			Assert::AreEqual(vec_1.size(), 0u);
			Assert::AreEqual(vec_2.size(), 25u);

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_8)
		{
			static_vector<MoveableObj<true>, 50> vec_1(25);

			static_vector<MoveableObj<true>, 25> vec_2;
			vec_2 = std::move(vec_1);

			Assert::AreEqual(vec_1.size(), 0u);
			Assert::AreEqual(vec_2.size(), 25u);

			for (const auto& obj : vec_2)
			{
				Assert::AreEqual(obj.message, std::string("Has value"));
			}
		}

		TEST_METHOD(Move_semantic_9)
		{
			static_vector<MoveableObj<true>, 50> vec_1(26);


			auto RunTimeExceptionThrower = [&]()
			{
				static_vector<MoveableObj<true>, 25> vec_2 = std::move(vec_1);
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Move_semantic_10)
		{
			static_vector<MoveableObj<true>, 50> vec_1(26);


			auto RunTimeExceptionThrower = [&]()
			{
				static_vector<MoveableObj<true>, 25> vec_2;
				vec_2 = std::move(vec_1);
			};

			Assert::ExpectException<std::runtime_error>(RunTimeExceptionThrower);
		}

		TEST_METHOD(Iterators_1)
		{
			static_vector<int, 50> vec = { 0,1,2,3,4,5,6,7,8,9 };

			int i = 0;
			for (auto it = vec.begin(); it != vec.end(); ++it, ++i)
			{
				Assert::AreEqual(*it, i);
			}

			i = 0;
			for (auto it = vec.cbegin(); it != vec.cend(); ++it, ++i)
			{
				Assert::AreEqual(*it, i);
			}

			i = 9;
			for (auto it = vec.rbegin(); it != vec.rend(); ++it, --i)
			{
				Assert::AreEqual(*it, i);
			}

			i = 9;
			for (auto it = vec.crbegin(); it != vec.crend(); ++it, --i)
			{
				Assert::AreEqual(*it, i);
			}

			auto& const_vec = std::as_const(vec);

			i = 0;
			for (auto it = const_vec.begin(); it != const_vec.end(); ++it, ++i)
			{
				Assert::AreEqual(*it, i);
			}

			i = 9;
			for (auto it = const_vec.rbegin(); it != const_vec.rend(); ++it, --i)
			{
				Assert::AreEqual(*it, i);
			}
		}
	};
}
