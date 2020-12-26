/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#define BOOST_TEST_MODULE Test
#include <boost/test/included/unit_test.hpp>

#include "Coordinate.h"
#include "LinkedCoordinate.h"

namespace vistart
{
	namespace orthogonal_linked_list
	{
#pragma region Coordinate 夹具
#pragma region 二维坐标
#pragma region 二维坐标标量
		struct Coordinate2DFixture
		{
			std::shared_ptr<Coordinate<2, unsigned int>> c;
			Coordinate2DFixture()
			{
				c = std::make_shared<Coordinate<2, unsigned int>>();
			}
			~Coordinate2DFixture() = default;
		};
#pragma endregion
#pragma region 二维坐标-类
#pragma endregion
#pragma endregion
#pragma region 三维坐标
#pragma region 三维坐标标量
		struct Coordinate3DFixture
		{
			std::shared_ptr<Coordinate<3, unsigned int>> c;
			Coordinate3DFixture()
			{
				c = std::make_shared<Coordinate<3, unsigned int>>();
			}
			~Coordinate3DFixture() = default;
		};
#pragma endregion
#pragma region 三维坐标-类
#pragma endregion
#pragma endregion
#pragma region 四维坐标
#pragma region 四维坐标标量
		struct Coordinate4DFixture
		{
			std::shared_ptr<Coordinate<4, unsigned int>> c;
			Coordinate4DFixture()
			{
				c = std::make_shared<Coordinate<4, unsigned int>>();
			}
			~Coordinate4DFixture() = default;
		};
#pragma endregion
#pragma endregion
#pragma endregion

#pragma region LinkedCoordinate 夹具
#pragma region 二维夹具
#pragma region 二维夹具标量
		struct LinkedCoordinate2DFixture
		{
			std::shared_ptr<LinkedCoordinate<2, unsigned int>> c;
			LinkedCoordinate2DFixture()
			{
				c = std::make_shared<LinkedCoordinate<2, unsigned int>>();
			}
			~LinkedCoordinate2DFixture() = default;
		};
#pragma endregion
#pragma endregion
#pragma region 三维夹具
#pragma region 三维夹具标量
		struct LinkedCoordinate3DFixture
		{
			std::shared_ptr<LinkedCoordinate<3, unsigned int>> c;
			LinkedCoordinate3DFixture()
			{
				c = std::make_shared<LinkedCoordinate<3, unsigned int>>();
			}
			~LinkedCoordinate3DFixture() = default;
		};
#pragma endregion
#pragma endregion
#pragma region 四维夹具
#pragma region 四维夹具标量
		struct LinkedCoordinate4DFixture
		{
			std::shared_ptr<LinkedCoordinate<4, unsigned int>> c;
			LinkedCoordinate4DFixture()
			{
				c = std::make_shared<LinkedCoordinate<4, unsigned int>>();
			}
			~LinkedCoordinate4DFixture() = default;
		};
#pragma endregion
#pragma endregion
#pragma endregion
		BOOST_AUTO_TEST_SUITE(TestCoordinate)
			/**
			* 此过程模拟实例化正交链表的过程。
			* 需要模拟2-维到16-维。
			* 类型参数 D 必须为常亮，因此不能用循环赋值，只能单独写出每一句，并分别执行。
			*/
		BOOST_AUTO_TEST_CASE(TestCoordinateInit)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			Coordinate2DFixture o2;
			const auto& c2 = { (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o2.c->get(c2) == nullptr);

			Coordinate3DFixture o3;
			const auto& c3 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o3.c->get(c3) == nullptr);

			Coordinate4DFixture o4;
			const auto& c4 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o4.c->get(c4) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<5, unsigned int>> o5 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<5, unsigned int>>();
			const auto& c5 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o5->get(c5) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<6, unsigned int>> o6 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<6, unsigned int>>();
			const auto& c6 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o6->get(c6) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<7, unsigned int>> o7 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<7, unsigned int>>();
			const auto& c7 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o7->get(c7) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<8, unsigned int>> o8 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<8, unsigned int>>();
			const auto& c8 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o8->get(c8) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<9, unsigned int>> o9 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<9, unsigned int>>();
			const auto& c9 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o9->get(c9) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<10, unsigned int>> o10 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<10, unsigned int>>();
			const auto& c10 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o10->get(c10) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<11, unsigned int>> o11 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<11, unsigned int>>();
			const auto& c11 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o11->get(c11) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<12, unsigned int>> o12 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<12, unsigned int>>();
			const auto& c12 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o12->get(c12) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<13, unsigned int>> o13 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<13, unsigned int>>();
			const auto& c13 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o13->get(c13) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<14, unsigned int>> o14 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<14, unsigned int>>();
			const auto& c14 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o14->get(c14) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<15, unsigned int>> o15 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<15, unsigned int>>();
			const auto& c15 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o15->get(c15) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<16, unsigned int>> o16 = std::make_shared<vistart::orthogonal_linked_list::Coordinate<16, unsigned int>>();
			const auto& c16 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o16->get(c16) == nullptr);
		}
		BOOST_AUTO_TEST_SUITE_END()

			/**
			 * 测试二维坐标。
			 */
		BOOST_AUTO_TEST_SUITE(TestCoordinate2D)
			/**
			 * 测试二维坐标初始化。
			 * 1. 实例化时不抛出异常。
			 * 2. 找不到随机生成的坐标值。
			 * 3. 如果坐标维度与目标空间维度不匹配，则抛出异常 CoordinateDimensionMismatchException。
			 */
		BOOST_AUTO_TEST_CASE(TestCoordinate2DInit)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			BOOST_TEST_MESSAGE("The initialization of 2-Dimension Orthogonal Linked Coordinate:");
			Coordinate2DFixture o2;
			const auto& c2 = { (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o2.c->get(c2) == nullptr);

			const auto& c3 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_CHECK_THROW(o2.c->get(c3), vistart::orthogonal_linked_list::CoordinateDimensionMismatchException);
		}

		BOOST_AUTO_TEST_CASE(TestCoordinate2DEqualBeyondDimension)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			const Coordinate<2, unsigned int>::coordinates_type& c1 = { (unsigned int)rand(), (unsigned int)rand() };
			const Coordinate<2, unsigned int>::coordinates_type& c2 = { c1[0] + 1, c1[1] };
			const auto r1 = Coordinate<2, unsigned int>::coordinates_equal_beyond_dimension(c1, c2, 0);
			const auto r2 = Coordinate<2, unsigned int>::coordinates_equal_beyond_dimension(c1, c2, 1);
			BOOST_REQUIRE_EQUAL(r1, true);
			BOOST_REQUIRE_EQUAL(r2, false);
		}

		BOOST_AUTO_TEST_CASE(TestCoordinate2DBeyondDimension)
		{
			const Coordinate<2, unsigned int>::coordinates_type& c = { 1, 2 };
			const auto r1 = Coordinate<2, unsigned int>::coordinates_beyond_dimension(c, 0);
			const auto r2 = Coordinate<2, unsigned int>::coordinates_beyond_dimension(c, 1);
			BOOST_REQUIRE_EQUAL(r1[0], 0);
			BOOST_REQUIRE_EQUAL(r1[1], 2);
			BOOST_REQUIRE_EQUAL(r2[0], 1);
			BOOST_REQUIRE_EQUAL(r2[1], 0);
		}

		/**
		 * 测试二维空间添加坐标元素。
		 * 1. 实例化时不抛出异常。
		 * 2. 找不到随机生成的坐标值。
		 * 3. 向该坐标添加一个随机值。
		 */
		BOOST_AUTO_TEST_CASE(TestCoordinate2DAdd)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			Coordinate2DFixture o2;

			// 随机二维坐标
			const std::vector<unsigned int>& c2 = { (unsigned int)rand(), (unsigned int)rand() };

			BOOST_TEST_MESSAGE("C2 Coordinate: ");
			BOOST_TEST_MESSAGE(c2[0]);
			BOOST_TEST_MESSAGE(c2[1]);

			// 随机内容
			unsigned int r2 = (unsigned int)rand();
			BOOST_TEST_MESSAGE("C2 Value: ");
			BOOST_TEST_MESSAGE(r2);

			// 在没有添加前，应该找不到
			BOOST_TEST(o2.c->get(c2) == nullptr, "在没有添加内容前，应该找不到。");
			// 此时添加内容不应该抛出异常
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2)));
			// 添加后应该找得到
			const auto r3 = o2.c->get(c2);
			BOOST_TEST(r3 != nullptr, "添加后应该找得到。");
			// 取出的值应该与原值相等。
			BOOST_TEST_CHECK(r3, r2);
			BOOST_TEST(*r3 == r2, "添加后找到的值应该与原值相等。");

			// 相同坐标添加一个不同的值
			// 添加时不应该抛出异常
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 1)));

			// 添加后取出的值应该与 r3 相等，而不应该与 r4 相等。
			BOOST_TEST(*r3 != *(o2.c->get(c2)),"在坐标已存在情况下，应该允许设置新值。");
			BOOST_TEST(r2 + 1 == *(o2.c->get(c2)), "在坐标已存在情况下，添加新值后，再次取出的应该是新值。");
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 2), false));
			BOOST_TEST(r2 + 1 == *(o2.c->get(c2)), "在坐标已存在情况下，如果不允许替换，则再次取出的应该是旧值。");
		}

		/**
		 * 测试二维坐标批量添加元素
		 */
		BOOST_AUTO_TEST_CASE(TestCoordinate2DAddBatch)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			unsigned int size = 10000;
			Coordinate2DFixture o2;
			std::vector<std::vector<unsigned int>> c2s(size);
			std::vector<unsigned int> r2s(size);
			std::vector<unsigned int> added;
			for (unsigned int i = 0; i < size; i++)
			{
				std::vector<unsigned int> c2 = { (unsigned int)(rand() * size), (unsigned int)(rand() * size) };
				c2s[i] = c2;
				unsigned int r2 = (unsigned int)(rand() * size);
				r2s[i] = r2;
				//BOOST_TEST_MESSAGE(c2[0]);
				//BOOST_TEST_MESSAGE(c2[1]);
				//BOOST_TEST_MESSAGE(r2);
				if (o2.c->get(c2) != nullptr)
				{
					BOOST_TEST_MESSAGE("The Coordinate already exists: ");
					BOOST_TEST_MESSAGE(c2[0]);
					BOOST_TEST_MESSAGE(c2[1]);
					BOOST_TEST_MESSAGE("\n");
					c2[0] = (unsigned int)(rand() * size);
					c2[1] = (unsigned int)(rand() * size);
					added.push_back(i);
					continue;
				}
				BOOST_TEST(o2.c->get(c2) == nullptr);
				BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2)));
				BOOST_TEST(o2.c->get(c2) != nullptr);
				//BOOST_TEST_CHECK(*o2->get(c2), r2);
			}
			BOOST_TEST_MESSAGE("Several Coordinate already exist: ");
			BOOST_TEST_MESSAGE(added.size());

		}

		/**
		 * 测试二维坐标删除元素。
		 */
		BOOST_AUTO_TEST_CASE(TestCoordinate2DRemove)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			Coordinate2DFixture o2;
			std::vector<unsigned int> c2 = { (unsigned int)rand(), (unsigned int)rand() };
			unsigned int r2 = (unsigned int)rand();

			BOOST_TEST(o2.c->get(c2) == nullptr, "在没有添加内容前，应该找不到。");
			// 设置元素过程中不能抛出异常
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2)));
			BOOST_TEST(o2.c->get(c2) != nullptr, "添加后应该找得到。");
			BOOST_TEST(*o2.c->get(c2) == r2, "添加后找到的值应该与原值相等。");

			BOOST_TEST(o2.c->erase(c2) == 1, "成功删除的元素数量应该为 1。");
			BOOST_TEST(o2.c->get(c2) == nullptr, "删除后元素应该找不到了。");
			BOOST_TEST(o2.c->erase(c2) == 0, "成功删除后再次删除的数量应该为 0。"); // 不能用 BOOST_TEST_CHECK(o2.c->erase(c2), 0)，会直接报不通过。
			BOOST_TEST(o2.c->get(c2) == nullptr, "删除后再查找应该找不到。");

			// 在此设置元素过程中不能抛出异常
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 1)));
			BOOST_TEST(o2.c->get(c2) != nullptr, "再次添加后应该能找到。");
			BOOST_TEST(*o2.c->get(c2) == r2 + 1, "再次添加后找到的值应该与原值相等。");
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 2)));
			BOOST_TEST(*o2.c->get(c2) == r2 + 2, "再次添加后找到的值应该与新值相等。");
			BOOST_TEST(o2.c->erase(c2) == 1, "再次添加的元素被删除的数量应该为 1。");
			BOOST_TEST(o2.c->erase(c2) == 0, "再次删除刚添加的元素被删除的数量应该为 0。");
		}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestCoordinate3D)

		BOOST_AUTO_TEST_CASE(TestCoordinate3DEqualBeyondDimension)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			const Coordinate<2, unsigned int>::coordinates_type& c1 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			const Coordinate<2, unsigned int>::coordinates_type& c2 = { c1[0] + 1, c1[1], c1[2] };
			const auto r1 = Coordinate<3, unsigned int>::coordinates_equal_beyond_dimension(c1, c2, 0);
			const auto r2 = Coordinate<3, unsigned int>::coordinates_equal_beyond_dimension(c1, c2, 1);
			const auto r3 = Coordinate<3, unsigned int>::coordinates_equal_beyond_dimension(c1, c2, 2);
			BOOST_REQUIRE_EQUAL(r1, true);
			BOOST_REQUIRE_EQUAL(r2, false);
			BOOST_REQUIRE_EQUAL(r3, false);
		}

		BOOST_AUTO_TEST_CASE(TestCoordinate3DBeyondDimension)
		{
			const Coordinate<3, unsigned int>::coordinates_type& c = { 1, 2, 3 };
			const auto r1 = Coordinate<3, unsigned int>::coordinates_beyond_dimension(c, 0);
			const auto r2 = Coordinate<3, unsigned int>::coordinates_beyond_dimension(c, 1);
			const auto r3 = Coordinate<3, unsigned int>::coordinates_beyond_dimension(c, 2);
			BOOST_REQUIRE_EQUAL(r1[0], 0);
			BOOST_REQUIRE_EQUAL(r1[1], 2);
			BOOST_REQUIRE_EQUAL(r1[2], 3);
			BOOST_REQUIRE_EQUAL(r2[0], 1);
			BOOST_REQUIRE_EQUAL(r2[1], 0);
			BOOST_REQUIRE_EQUAL(r2[2], 3);
			BOOST_REQUIRE_EQUAL(r3[0], 1);
			BOOST_REQUIRE_EQUAL(r3[1], 2);
			BOOST_REQUIRE_EQUAL(r3[2], 0);
		}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(TestLinkedCoordinate)

		/**
		 * 测试正交链接坐标初始化。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinateInit)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate2DFixture o2;
			const auto& c2 = { (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o2.c->get(c2) == nullptr);

			LinkedCoordinate3DFixture o3;
			const auto& c3 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o3.c->get(c3) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<4, unsigned int>> o4 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<4, unsigned int>>();
			const auto& c4 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o4->get(c4) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<5, unsigned int>> o5 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<5, unsigned int>>();
			const auto& c5 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o5->get(c5) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<6, unsigned int>> o6 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<6, unsigned int>>();
			const auto& c6 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o6->get(c6) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<7, unsigned int>> o7 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<7, unsigned int>>();
			const auto& c7 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o7->get(c7) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<8, unsigned int>> o8 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<8, unsigned int>>();
			const auto& c8 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o8->get(c8) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<9, unsigned int>> o9 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<9, unsigned int>>();
			const auto& c9 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o9->get(c9) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<10, unsigned int>> o10 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<10, unsigned int>>();
			const auto& c10 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o10->get(c10) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<11, unsigned int>> o11 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<11, unsigned int>>();
			const auto& c11 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o11->get(c11) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<12, unsigned int>> o12 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<12, unsigned int>>();
			const auto& c12 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o12->get(c12) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<13, unsigned int>> o13 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<13, unsigned int>>();
			const auto& c13 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o13->get(c13) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<14, unsigned int>> o14 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<14, unsigned int>>();
			const auto& c14 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o14->get(c14) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<15, unsigned int>> o15 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<15, unsigned int>>();
			const auto& c15 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o15->get(c15) == nullptr);

			std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<16, unsigned int>> o16 = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<16, unsigned int>>();
			const auto& c16 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };
			BOOST_TEST(o16->get(c16) == nullptr);
		}

		/**
		 * 测试二维正交链表坐标添加元素。只添加一次，包括添加相同位置的。添加后不删除。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate2DAddOnce)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate2DFixture o2;

			const std::vector<unsigned int>& c2 = { (unsigned int)rand(), (unsigned int)rand() };

			unsigned int r2 = (unsigned int)rand();
			// 在没有添加内容前，应该找不到。
			BOOST_REQUIRE_EQUAL(o2.c->get(c2), nullptr);
			// 向坐标中添加一个元素。添加过程中不能抛出异常。
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2)));
			// 添加后坐标内只有一个元素。此时两个维度的头尾指针均指向这个元素的坐标。
			const auto r3 = o2.c->get(c2);
			// 添加后应该找得到。
			BOOST_REQUIRE_NE(r3, nullptr);
			// 取出的值应该与原值相等。
			BOOST_REQUIRE_EQUAL(*r3, r2);

			// 因夹具为二维坐标，故头尾指针数组也应当有 2 个元素。
			BOOST_REQUIRE_EQUAL(o2.c->__debug_head_and_tail_in_all_dimensions.size(), 2);
			const auto& ht0 = o2.c->__debug_head_and_tail_in_all_dimensions[0];
			// 维度 0 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			const auto& ht1 = o2.c->__debug_head_and_tail_in_all_dimensions[1];
			// 维度 1 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			const auto& ht0r = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 0));
			const auto& ht1r = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 1));
			// 维度 0 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.head, ht0r->second.tail);
			// 维度 1 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r->second.head, ht1r->second.tail);
			// 维度 0 头指针和维度 1 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.head, ht1r->second.head);
			// 维度 0 尾指针和维度 1 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.tail, ht1r->second.tail);

			BOOST_REQUIRE_EQUAL(ht0r->second.head->size(), 2);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[0], c2[0]);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[1], c2[1]);
									
			// 相同坐标添加一个不同的值
			// 添加时不应该抛出异常
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 1)));

			// 添加后取出的值应该与 r3 相等，而不应该与 r4 相等。
			// 在坐标已存在情况下，应该允许设置新值。
			BOOST_REQUIRE_NE(*r3, *o2.c->get(c2));
			// 在坐标已存在情况下，添加新值后，再次取出的应该是新值。
			BOOST_REQUIRE_EQUAL(r2 + 1, *o2.c->get(c2));
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 2), false));
			// 在坐标已存在情况下，如果不允许替换，则再次取出的应该是旧值。
			BOOST_REQUIRE_EQUAL(r2 + 1, *o2.c->get(c2));

			const auto& ht0r0 = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 0));
			const auto& ht1r0 = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 1));
			// 维度 0 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r0->second.head, ht0r0->second.tail);
			// 维度 1 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r0->second.head, ht1r0->second.tail);
			// 维度 0 头指针和维度 1 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r0->second.head, ht1r0->second.head);
			// 维度 0 尾指针和维度 1 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r0->second.tail, ht1r0->second.tail);
		}

		/**
		 * 测试二维正交链表坐标添加元素。
		 * 添加一次后，在另一个位置，按下列情况再添加：（设第一次添加的元素坐标为 c1）
		 * 1. c1 的坐标与 c2 的坐标完全不同；
		 * 2. c1 的维度 0 与 c3 的维度 0 相同，维度 1 不同；
		 * 3. c1 的维度 1 与 c4 的维度 1 相同，维度 0 不同。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate2DAddTwice)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate2DFixture o1;
			// 为了方便调试，此处使用固定坐标，而非随机坐标。
			// const std::vector<unsigned int>& c1 = { 5, 7 };
			const std::vector<unsigned int>& c1 = { static_cast<unsigned int>(rand()), static_cast<unsigned int>(rand()) };
			// 维度 0 头尾指针组。因为此处测试的是二维坐标，故头尾指针组应该是一维数据。但为了普适处理，头尾指针组坐标依然与坐标保持相同维度，而当前维度全部置零，下同。
			const auto& ht0 = o1.c->__debug_head_and_tail_in_all_dimensions[0];
			// 维度 1 头尾指针组。
			const auto& ht1 = o1.c->__debug_head_and_tail_in_all_dimensions[1];
			unsigned int r1 = static_cast<unsigned int>(rand());
			
			// 向坐标中添加一个元素。添加过程中不能抛出异常。
			BOOST_REQUIRE_NO_THROW(o1.c->set(c1, std::make_shared<unsigned int>(r1)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			BOOST_REQUIRE_EQUAL(ht1.size(), 1);
			// 检查指针指向的坐标尺寸是否与当前维度匹配。
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head->size(), 2);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail->size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head->size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail->size(), 2);
			// 检查头尾指针组是否指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);

			// 坐标1的维度0头指针
			auto c1_ht0r_head = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head;
			// 坐标1的维度0尾指针
			auto c1_ht0r_tail = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail;
			// 坐标1的维度1头指针
			auto c1_ht1r_head = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head;
			// 坐标1的维度1尾指针
			auto c1_ht1r_tail = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail;

			// 头尾指针都应该指向 c1 坐标，并且值也相等。
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[1], c1[1]);

			const std::vector<unsigned int>& c2 = { c1[0] + 1, c1[1] + 1 };
			unsigned int r2 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c2, std::make_shared<unsigned int>(r2)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);
			// 两个坐标的两个维度值均不相等，因此他们的头尾指针也不会改变。
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head, ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.tail);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head, ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.tail);

			const std::vector<unsigned int>& c3 = { c1[0], c1[1] + 1 };
			unsigned int r3 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c3, std::make_shared<unsigned int>(r3)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);
			// 坐标1的维度0头指针。此时应该指向（5，7）
			c1_ht0r_head = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head;
			// 坐标1的维度0尾指针。此时应该指向（5，7）
			c1_ht0r_tail = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail;
			// 坐标1的维度1头指针。此时应该指向（5，7）
			c1_ht1r_head = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head;
			// 坐标1的维度1尾指针。此时应该指向（5，8）
			c1_ht1r_tail = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail;
			
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_NE(c1_ht1r_head, c1_ht1r_tail);
			BOOST_REQUIRE_EQUAL(c1_ht0r_head, c1_ht0r_tail);
			BOOST_REQUIRE_EQUAL(c1_ht0r_head, c1_ht1r_head);

			const std::vector<unsigned int>& c4 = { c1[0] + 1, c1[1] };
			unsigned int r4 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c4, std::make_shared<unsigned int>(r4)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);

			// 坐标1的维度0头指针。此时应该指向（5，7）
			c1_ht0r_head = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head;
			// 坐标1的维度0尾指针。此时应该指向（6，7）
			c1_ht0r_tail = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail;
			// 坐标1的维度1头指针。此时应该指向（5，7）
			c1_ht1r_head = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head;
			// 坐标1的维度1尾指针。此时应该指向（5，8）
			c1_ht1r_tail = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail;

			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[0], c1[0] + 1);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_NE(c1_ht1r_head, c1_ht1r_tail);
			BOOST_REQUIRE_NE(c1_ht0r_head, c1_ht0r_tail);
			BOOST_REQUIRE_EQUAL(c1_ht0r_head, c1_ht1r_head);
			BOOST_REQUIRE_NE(c1_ht0r_tail, c1_ht1r_tail);
		}

		/**
		 * 测试二维正交链表坐标批量添加元素
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate2DAddBatch)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate2DFixture o2;
		}

		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate2DRemove)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate2DFixture o2;

			const std::vector<unsigned int>& c1 = { (unsigned int)rand(), (unsigned int)rand() };

			unsigned int r1 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o2.c->set(c1, std::make_shared<unsigned int>(r1)));
			
			const auto& ht0 = o2.c->__debug_head_and_tail_in_all_dimensions[0];
			// 维度 0 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			const auto& ht1 = o2.c->__debug_head_and_tail_in_all_dimensions[1];
			// 维度 1 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);

			BOOST_REQUIRE_EQUAL(o2.c->erase(c1), 1);
			BOOST_REQUIRE_EQUAL(o2.c->get(c1), nullptr);
			const auto& ht0r = ht0.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 0));
			const auto& ht1r = ht1.find(Coordinate<2, unsigned int>::coordinates_beyond_dimension(c1, 1));
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			BOOST_REQUIRE_EQUAL(ht1.size(), 1);
			BOOST_REQUIRE_EQUAL(ht0r->second.head, nullptr);
			BOOST_REQUIRE_EQUAL(ht0r->second.tail, nullptr);
			BOOST_REQUIRE_EQUAL(ht1r->second.head, nullptr);
			BOOST_REQUIRE_EQUAL(ht1r->second.tail, nullptr);
			
			BOOST_REQUIRE_EQUAL(o2.c->erase(c1), 0);
			
			BOOST_REQUIRE_EQUAL(ht0r->second.head, nullptr);
			BOOST_REQUIRE_EQUAL(ht0r->second.tail, nullptr);
			BOOST_REQUIRE_EQUAL(ht1r->second.head, nullptr);
			BOOST_REQUIRE_EQUAL(ht1r->second.tail, nullptr);
			
			BOOST_REQUIRE_EQUAL(o2.c->erase(c1), 0);
			
			BOOST_REQUIRE_EQUAL(ht0r->second.head, nullptr);
			BOOST_REQUIRE_EQUAL(ht0r->second.tail, nullptr);
			BOOST_REQUIRE_EQUAL(ht1r->second.head, nullptr);
			BOOST_REQUIRE_EQUAL(ht1r->second.tail, nullptr);

			BOOST_REQUIRE_NO_THROW(o2.c->set(c1, std::make_shared<unsigned int>(r1)));
			BOOST_REQUIRE_EQUAL(*o2.c->get(c1), r1);
			// 维度 0 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.head, ht0r->second.tail);
			// 维度 1 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r->second.head, ht1r->second.tail);
			// 维度 0 头指针和维度 1 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.head, ht1r->second.head);
			// 维度 0 尾指针和维度 1 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.tail, ht1r->second.tail);

			BOOST_REQUIRE_EQUAL(ht0r->second.head->size(), 2);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[1], c1[1]);

			const std::vector<unsigned int>& c2 = { c1[0] + 1, c1[1] + 1 };
			unsigned int r2 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);

			const std::vector<unsigned int>& c3 = { c1[0], c1[1] + 1 };
			unsigned int r3 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o2.c->set(c3, std::make_shared<unsigned int>(r3)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);
			
			const std::vector<unsigned int>& c4 = { c1[0] + 1, c1[1] };
			unsigned int r4 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o2.c->set(c4, std::make_shared<unsigned int>(r4)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);
		}

		/**
		 * 测试三维正交链接坐标添加元素。只添加一次，包括添加相同位置的。添加后不删除。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DAddOnce)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate3DFixture o2;

			const std::vector<unsigned int>& c2 = { (unsigned int)rand(), (unsigned int)rand(), (unsigned int)rand() };

			unsigned int r2 = (unsigned int)rand();
			// 在没有添加内容前，应该找不到。
			BOOST_REQUIRE_EQUAL(o2.c->get(c2), nullptr);
			// 向坐标中添加一个元素。添加过程中不能抛出异常。
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2)));
			// 添加后坐标内只有一个元素。此时两个维度的头尾指针均指向这个元素的坐标。
			const auto r3 = o2.c->get(c2);
			// 添加后应该找得到。
			BOOST_REQUIRE_NE(r3, nullptr);
			// 取出的值应该与原值相等。
			BOOST_REQUIRE_EQUAL(*r3, r2);

			// 因夹具为二维坐标，故头尾指针数组也应当有 2 个元素。
			BOOST_REQUIRE_EQUAL(o2.c->__debug_head_and_tail_in_all_dimensions.size(), 3);
			const auto& ht0 = o2.c->__debug_head_and_tail_in_all_dimensions[0];
			// 维度 0 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			const auto& ht1 = o2.c->__debug_head_and_tail_in_all_dimensions[1];
			// 维度 1 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			const auto& ht2 = o2.c->__debug_head_and_tail_in_all_dimensions[2];
			// 维度 2 的大小应当为 1。
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			const auto& ht0r = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0));
			const auto& ht1r = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1));
			const auto& ht2r = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2));
			// 维度 0 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.head, ht0r->second.tail);
			// 维度 1 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r->second.head, ht1r->second.tail);
			// 维度 2 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht2r->second.head, ht2r->second.tail);
			// 维度 0 头指针和维度 1 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.head, ht1r->second.head);
			// 维度 1 头指针和维度 2 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r->second.head, ht2r->second.head);
			// 维度 0 尾指针和维度 1 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r->second.tail, ht1r->second.tail);
			// 维度 1 尾指针和维度 2 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r->second.tail, ht2r->second.tail);

			BOOST_REQUIRE_EQUAL(ht0r->second.head->size(), 3);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[0], c2[0]);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[1], c2[1]);
			BOOST_REQUIRE_EQUAL((*ht0r->second.head)[2], c2[2]);

			// 相同坐标添加一个不同的值
			// 添加时不应该抛出异常
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 1)));

			// 添加后取出的值应该与 r3 相等，而不应该与 r4 相等。
			// 在坐标已存在情况下，应该允许设置新值。
			BOOST_REQUIRE_NE(*r3, *o2.c->get(c2));
			// 在坐标已存在情况下，添加新值后，再次取出的应该是新值。
			BOOST_REQUIRE_EQUAL(r2 + 1, *o2.c->get(c2));
			BOOST_REQUIRE_NO_THROW(o2.c->set(c2, std::make_shared<unsigned int>(r2 + 2), false));
			// 在坐标已存在情况下，如果不允许替换，则再次取出的应该是旧值。
			BOOST_REQUIRE_EQUAL(r2 + 1, *o2.c->get(c2));

			const auto& ht0r0 = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0));
			const auto& ht1r0 = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1));
			const auto& ht2r0 = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2));
			// 维度 0 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r0->second.head, ht0r0->second.tail);
			// 维度 1 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r0->second.head, ht1r0->second.tail);
			// 维度 2 头尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht2r0->second.head, ht2r0->second.tail);
			// 维度 0 头指针和维度 1 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r0->second.head, ht1r0->second.head);
			// 维度 1 头指针和维度 2 头指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r0->second.head, ht2r0->second.head);
			// 维度 0 尾指针和维度 1 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0r0->second.tail, ht1r0->second.tail);
			// 维度 1 尾指针和维度 2 尾指针指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht1r0->second.tail, ht2r0->second.tail);
		}

		/**
		 * 测试二维正交链表坐标添加元素。
		 * 添加一次后，在另一个位置，按下列情况再添加：（设第一次添加的元素坐标为 c1）
		 * 1. c1 的坐标与 c2 的坐标完全不同；
		 * 2. c1 的维度 0 与 c3 的维度 0 相同，维度 1 与维度 2 不同；
		 * 3. c1 的维度 1 与 c4 的维度 1 相同，维度 0 与维度 2 不同；
		 * 4. c1 的维度 2 与 c5 的维度 2 相同，维度 0 与维度 1 不同；
		 * 5. c1 的维度 0 和维度 1 与 c6 的维度 0 和维度 1 相同，维度 2 不同；
		 * 6. c1 的维度 1 和维度 2 与 c7 的维度 1 和维度 2 相同，维度 0 不同；
		 * 7. c1 的维度 2 和维度 0 与 c8 的维度 2 和维度 0 相同，维度 1 不同。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DAddTwice)
		{
			const auto seed = time(0);
			srand(static_cast<unsigned int>(seed));
			LinkedCoordinate3DFixture o1;
			// 为了方便调试，此处使用固定坐标，而非随机坐标。
			const std::vector<unsigned int>& c1 = { 5, 7, 9 };
			// const std::vector<unsigned int>& c1 = { static_cast<unsigned int>(rand()), static_cast<unsigned int>(rand()), static_cast<unsigned int>(rand()) };
			// 维度 0 头尾指针组。因为此处测试的是二维坐标，故头尾指针组应该是一维数据。但为了普适处理，头尾指针组坐标依然与坐标保持相同维度，而当前维度全部置零，下同。
			const auto& ht0 = o1.c->__debug_head_and_tail_in_all_dimensions[0];
			// 维度 1 头尾指针组。
			const auto& ht1 = o1.c->__debug_head_and_tail_in_all_dimensions[1];
			// 维度 1 头尾指针组。
			const auto& ht2 = o1.c->__debug_head_and_tail_in_all_dimensions[2];
			unsigned int r1 = static_cast<unsigned int>(rand());

			// 向坐标中添加一个元素。添加过程中不能抛出异常。
			BOOST_REQUIRE_NO_THROW(o1.c->set(c1, std::make_shared<unsigned int>(r1)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 1);
			BOOST_REQUIRE_EQUAL(ht1.size(), 1);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);
			// 检查指针指向的坐标尺寸是否与当前维度匹配。
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head->size(), 3);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail->size(), 3);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head->size(), 3);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail->size(), 3);
			BOOST_REQUIRE_EQUAL(ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head->size(), 3);
			BOOST_REQUIRE_EQUAL(ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail->size(), 3);
			// 检查头尾指针组是否指向同一个元素。
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail);

			// 坐标1的维度0头指针
			auto c1_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head;
			// 坐标1的维度0尾指针
			auto c1_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail;
			// 坐标1的维度1头指针
			auto c1_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head;
			// 坐标1的维度1尾指针
			auto c1_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail;
			// 坐标1的维度2头指针
			auto c1_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head;
			// 坐标1的维度2尾指针
			auto c1_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail;

			// 头尾指针都应该指向 c1 坐标，并且值也相等。
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_head)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_tail)[2], c1[2]);

			const std::vector<unsigned int>& c2 = { c1[0] + 1, c1[1] + 1, c1[2] + 1 };
			unsigned int r2 = static_cast<unsigned int>(rand());
			BOOST_REQUIRE_NO_THROW(o1.c->set(c2, std::make_shared<unsigned int>(r2)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 2);
			BOOST_REQUIRE_EQUAL(ht2.size(), 2);
			// 两个坐标的两个维度值均不相等，因此他们的头尾指针也不会改变。
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail);
			
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head, ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.tail);
			BOOST_REQUIRE_EQUAL(ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.head, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2))->second.head, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2))->second.head);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.tail, ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.tail);
			BOOST_REQUIRE_EQUAL(ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.tail, ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2))->second.tail);

			const std::vector<unsigned int>& c3 = { c1[0], c1[1] + 1, c1[2] + 1 };
			unsigned int r3 = static_cast<unsigned int>(rand());
			BOOST_REQUIRE_NO_THROW(o1.c->set(c3, std::make_shared<unsigned int>(r3)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 2);
			BOOST_REQUIRE_EQUAL(ht1.size(), 3);
			BOOST_REQUIRE_EQUAL(ht2.size(), 3);
			// 坐标1的维度0头指针。此时应该指向（5，7, 9）
			c1_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head;
			// 坐标1的维度0尾指针。此时应该指向（5，7, 9）
			c1_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail;
			// 坐标2的维度0头指针。此时应该指向（5, 8, 10）
			auto c2_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.head;
			// 坐标2的维度0尾指针。此时应该指向（6, 8, 10）
			auto c2_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 0))->second.tail;

			// 坐标1的维度1头指针。此时应该指向（5，7, 9）
			c1_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head;
			// 坐标1的维度1尾指针。此时应该指向（5，7, 9）
			c1_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail;
			// 坐标2的维度1头指针。此时应该指向（6, 8, 10）
			auto c2_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.head;
			// 坐标2的维度1尾指针。此时应该指向（6，8, 10）
			auto c2_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 1))->second.tail;
			// 坐标3的维度1头指针。此时应该指向（5，8, 10）
			auto c3_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c3, 1))->second.head;
			// 坐标3的维度1尾指针。此时应该指向（5，8, 10）
			auto c3_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c3, 1))->second.tail;

			// 坐标1的维度1头指针。此时应该指向（5，7, 9）
			c1_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.head;
			// 坐标1的维度1尾指针。此时应该指向（5，7, 9）
			c1_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 2))->second.tail;
			// 坐标2的维度1头指针。此时应该指向（6, 8, 10）
			auto c2_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2))->second.head;
			// 坐标2的维度1尾指针。此时应该指向（6，8, 10）
			auto c2_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c2, 2))->second.tail;
			// 坐标3的维度1头指针。此时应该指向（5，8, 10）
			auto c3_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c3, 2))->second.head;
			// 坐标3的维度1尾指针。此时应该指向（5，8, 10）
			auto c3_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c3, 2))->second.tail;

			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_head)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht0r_tail)[2], c1[2]);
			
			BOOST_REQUIRE_EQUAL((*c2_ht0r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c2_ht0r_tail)[0], c1[0] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht0r_head)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht0r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht0r_head)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht0r_tail)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL(c1_ht0r_head, c1_ht0r_tail);
			BOOST_REQUIRE_NE(c2_ht0r_head, c2_ht0r_tail);

			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_head)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht1r_tail)[2], c1[2]);

			BOOST_REQUIRE_EQUAL((*c2_ht1r_head)[0], c1[0] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht1r_tail)[0], c1[0] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht1r_head)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht1r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht1r_head)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht1r_tail)[2], c1[2] + 1);

			BOOST_REQUIRE_EQUAL((*c3_ht1r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c3_ht1r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c3_ht1r_head)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c3_ht1r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c3_ht1r_head)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL((*c3_ht1r_tail)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL(c1_ht1r_head, c1_ht1r_tail);

			BOOST_REQUIRE_EQUAL((*c1_ht2r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_head)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_tail)[1], c1[1]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_head)[2], c1[2]);
			BOOST_REQUIRE_EQUAL((*c1_ht2r_tail)[2], c1[2]);

			BOOST_REQUIRE_EQUAL((*c2_ht2r_head)[0], c1[0] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht2r_tail)[0], c1[0] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht2r_head)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht2r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht2r_head)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL((*c2_ht2r_tail)[2], c1[2] + 1);

			BOOST_REQUIRE_EQUAL((*c3_ht2r_head)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c3_ht2r_tail)[0], c1[0]);
			BOOST_REQUIRE_EQUAL((*c3_ht2r_head)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c3_ht2r_tail)[1], c1[1] + 1);
			BOOST_REQUIRE_EQUAL((*c3_ht2r_head)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL((*c3_ht2r_tail)[2], c1[2] + 1);
			BOOST_REQUIRE_EQUAL(c1_ht2r_head, c1_ht2r_tail);
			
			const std::vector<unsigned int>& c4 = { c1[0] + 1, c1[1], c1[2] + 1 };
			unsigned int r4 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c4, std::make_shared<unsigned int>(r4)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 3);
			BOOST_REQUIRE_EQUAL(ht1.size(), 3);
			BOOST_REQUIRE_EQUAL(ht2.size(), 4);

			// 坐标1的维度0头指针。此时应该指向（5，7）
			c1_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.head;
			// 坐标1的维度0尾指针。此时应该指向（6，7）
			c1_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 0))->second.tail;
			// 坐标1的维度1头指针。此时应该指向（5，7）
			c1_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.head;
			// 坐标1的维度1尾指针。此时应该指向（5，8）
			c1_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c1, 1))->second.tail;

			const std::vector<unsigned int>& c5 = { c1[0] + 1, c1[1] + 1, c1[2] };
			unsigned int r5 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c5, std::make_shared<unsigned int>(r5)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 4);
			BOOST_REQUIRE_EQUAL(ht1.size(), 4);
			BOOST_REQUIRE_EQUAL(ht2.size(), 4);
			
			const std::vector<unsigned int>& c6 = { c1[0], c1[1], c1[2] + 1 };
			unsigned int r6 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c6, std::make_shared<unsigned int>(r6)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 4);
			BOOST_REQUIRE_EQUAL(ht1.size(), 4);
			BOOST_REQUIRE_EQUAL(ht2.size(), 4);
			
			const std::vector<unsigned int>& c7 = { c1[0] + 1, c1[1], c1[2] };
			unsigned int r7 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c7, std::make_shared<unsigned int>(r7)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 4);
			BOOST_REQUIRE_EQUAL(ht1.size(), 4);
			BOOST_REQUIRE_EQUAL(ht2.size(), 4);
			
			const std::vector<unsigned int>& c8 = { c1[0], c1[1] + 1, c1[2] };
			unsigned int r8 = (unsigned int)rand();
			BOOST_REQUIRE_NO_THROW(o1.c->set(c8, std::make_shared<unsigned int>(r8)));
			BOOST_REQUIRE_EQUAL(ht0.size(), 4);
			BOOST_REQUIRE_EQUAL(ht1.size(), 4);
			BOOST_REQUIRE_EQUAL(ht2.size(), 4);
		}

		/**
		 * 测试三维正交链接坐标批量添加元素。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DAddBatch)
		{

		}

		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DRemove)
		{
			
		}
		BOOST_AUTO_TEST_SUITE_END()

	}
}

