/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#define BOOST_TEST_MODULE TestCoordinate
#include <boost/test/included/unit_test.hpp>

#include "Coordinate.h"
#include "LinkedCoordinate.h"
#include <torch/torch.h>

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
		struct Coordinate3DwithCoordinate3DFixture
        {
		    std::shared_ptr<Coordinate<3, std::vector<double>>> c;
            Coordinate3DwithCoordinate3DFixture()
            {
		        c = std::make_shared<Coordinate<3, std::vector<double>>>();
            }
            ~Coordinate3DwithCoordinate3DFixture() = default;
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
		struct LinkedCoordinate3DwithLinkedCoordinate3DFixture
        {
            std::shared_ptr<LinkedCoordinate<3,std::vector<double>>>c;
            LinkedCoordinate3DwithLinkedCoordinate3DFixture()
            {
                c = std::make_shared<LinkedCoordinate<3,std::vector<double>>>();
            }
            ~LinkedCoordinate3DwithLinkedCoordinate3DFixture() = default;
        };
		/*
		 * 以6,7,9为中心，向六个方向间隔1分别添加1个元素。一共7个元素。
		 */
		struct LinkedCoordinate3DwithSevenElementsFixture1
		{
			std::shared_ptr<LinkedCoordinate<3, unsigned int>> c;
			const unsigned int c_x = 6;
			const unsigned int c_y = 7;
			const unsigned int c_z = 9;
			std::vector<unsigned int> const c11 = { 5,7,9 }; const unsigned int r11 = 17;
			std::vector<unsigned int> const c_center = { 6,7,9 }; const unsigned int r_center = 18;
			std::vector<unsigned int> const c13 = { 7,7,9 }; const unsigned int r13 = 19;
			std::vector<unsigned int> const c21 = { 6,6,9 }; const unsigned int r21 = 27;
			std::vector<unsigned int> const c23 = { 6,8,9 }; const unsigned int r23 = 37;
			std::vector<unsigned int> const c31 = { 6,7,8 }; const unsigned int r31 = 47;
			std::vector<unsigned int> const c33 = { 6,7,10 }; const unsigned int r33 = 57;
			
			LinkedCoordinate3DwithSevenElementsFixture1()
			{
				c = std::make_shared<LinkedCoordinate<3, unsigned int>>();
				c->set(c11, std::make_shared<unsigned int>(r11));
				c->set(c_center, std::make_shared<unsigned int>(r_center));
				c->set(c13, std::make_shared<unsigned int>(r13));
				c->set(c21, std::make_shared<unsigned int>(r21));
				c->set(c23, std::make_shared<unsigned int>(r23));
				c->set(c31, std::make_shared<unsigned int>(r31));
				c->set(c33, std::make_shared<unsigned int>(r33));
			}
			~LinkedCoordinate3DwithSevenElementsFixture1() = default;
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
#pragma region 随机坐标组
        struct RandomCoordinates256
        {
            const at::Tensor coords = at::rand({256, 3});
        };
        struct RandomCoordinates65536
        {
            const at::Tensor coords = at::rand({65536, 3});
        };
        struct RandomCoordinates262144
        {
            const at::Tensor coords = at::rand({262144, 3});
        };
        struct RandomCoordinates16777216
        {
            const at::Tensor coords = at::rand({16777216, 3});
        };
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

		BOOST_AUTO_TEST_CASE(TestCoordinate2DOperatorBracket)
		{
			const auto type_length = sizeof(size_t) * 8;
			const auto dimension_length = type_length / 2;
			const Coordinate<2, unsigned int>::coordinates_type& c = { 1, 2 };

			size_t result = (static_cast<size_t>(c[1]) << dimension_length) + static_cast<size_t>(c[0]);
			Coordinate<2, unsigned int>::Hash h;
			BOOST_REQUIRE_EQUAL(h.operator()(c), result);
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
			BOOST_TEST(*r3 != *(o2.c->get(c2)), "在坐标已存在情况下，应该允许设置新值。");
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

		BOOST_AUTO_TEST_CASE(TestCoordinate3DOperatorBracket)
		{
			const auto type_length = sizeof(size_t) * 8;
			const auto dimension_length = type_length / 3;
			const Coordinate<3, unsigned int>::coordinates_type& c = { 1, 2, 3 };

			size_t result = (static_cast<size_t>(c[2]) << 2 * dimension_length) + (static_cast<size_t>(c[1]) << dimension_length) + static_cast<size_t>(c[0]);
			Coordinate<3, unsigned int>::Hash h;
			BOOST_REQUIRE_EQUAL(h.operator()(c), result);
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
			// 维度 2 头尾指针组。
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

		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DIsFirstOrLastInDimension)
		{
			LinkedCoordinate3DFixture o1;
			
			const unsigned int c_x = 5;
			const unsigned int c_y = 7;
			const unsigned int c_z = 9;
			unsigned int size = 10;
			std::vector<unsigned int> c0 = { c_x, c_y, c_z };
			std::vector<unsigned int> c1 = { c_x, c_y, c_z + 1 };
			std::vector<unsigned int> c2 = { c_x, c_y, c_z + 2 };

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 0), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 0), false);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 1), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 1), false);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 2), false);

			BOOST_REQUIRE_NO_THROW(o1.c->set(c0, std::make_shared<unsigned int>(17)));

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 0), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 0), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 1), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 1), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 2), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 2), true);

			BOOST_REQUIRE_NO_THROW(o1.c->set(c1, std::make_shared<unsigned int>(18)));

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 0), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 0), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 1), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 1), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 2), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c1, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c1, 2), true);

			BOOST_REQUIRE_NO_THROW(o1.c->set(c2, std::make_shared<unsigned int>(19)));

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 0), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 0), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 1), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 1), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 2), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c1, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c1, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c2, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c2, 2), true);

			BOOST_REQUIRE_EQUAL(o1.c->erase(c1), 1);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 0), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 0), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 1), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 1), true);

			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c0, 2), true);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c0, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c1, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c1, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_first_in_dimension(c2, 2), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_is_last_in_dimension(c2, 2), true);
		}

		/**
		 * 测试三维正交链接坐标在单维度方向上批量添加元素。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DAddBatchInSingleDimension)
		{
			LinkedCoordinate3DFixture o1;
			// 在没有添加内容前，应该找不到。

			// 声明一个坐标组，有10个坐标，前两个维度固定，第三个维度间隔1。
			std::vector<std::vector<unsigned int>> c;

			// y-z 面头尾指针组。因为此处测试的是二维坐标，故头尾指针组应该是一维数据。但为了普适处理，头尾指针组坐标依然与坐标保持相同维度，而当前维度全部置零，下同。
			const auto& ht0 = o1.c->__debug_head_and_tail_in_all_dimensions[0];
			// x-z 面头尾指针组。
			const auto& ht1 = o1.c->__debug_head_and_tail_in_all_dimensions[1];
			// x-y 面头尾指针组。
			const auto& ht2 = o1.c->__debug_head_and_tail_in_all_dimensions[2];

			const unsigned int c_x = 5;
			const unsigned int c_y = 7;
			const unsigned int c_z = 9;
			
			for (unsigned int i = 0; i < 10; i++)
			{
				std::vector<unsigned int> c0 = { c_x, c_y, i + c_z };
				c.push_back(c0);
				// 添加的过程不能抛出异常
				// 添加的元素内容是当前序号 i。
				BOOST_REQUIRE_EQUAL(o1.c->get(c0), nullptr);
				BOOST_REQUIRE_NO_THROW(o1.c->set(c0, std::make_shared<unsigned int>(i)));
				const auto rt = o1.c->get(c0);
				// 添加后应该找得到。
				BOOST_REQUIRE_NE(rt, nullptr);
				// 取出的值应该与原值相等。
				BOOST_REQUIRE_EQUAL(*rt, i);

				unsigned int size = i + 1;
				BOOST_REQUIRE_EQUAL(ht0.size(), size);
				BOOST_REQUIRE_EQUAL(ht1.size(), size);
				BOOST_REQUIRE_EQUAL(ht2.size(), 1);
				
				// 当前坐标的y-z面头指针
				auto c0_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 0))->second.head;
				// 当前坐标的y-z面尾指针
				auto c0_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 0))->second.tail;
				// 当前坐标的x-z面头指针
				auto c0_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 1))->second.head;
				// 当前坐标的x-z面尾指针
				auto c0_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 1))->second.tail;
				// 当前坐标的x-y面头指针
				auto c0_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 2))->second.head;
				// 当前坐标的x-y面尾指针
				auto c0_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 2))->second.tail;

				// 每添加一个新元素判断每个头尾指针是否指向正确的元素坐标。
				// 每添加一个元素判断y-z面头尾指针是否指向当前元素坐标
				BOOST_REQUIRE_EQUAL((*c0_ht0r_head)[0], c0[0]);
				BOOST_REQUIRE_EQUAL((*c0_ht0r_tail)[0], c0[0]);
				BOOST_REQUIRE_EQUAL((*c0_ht0r_head)[1], c0[1]);
				BOOST_REQUIRE_EQUAL((*c0_ht0r_tail)[1], c0[1]);
				BOOST_REQUIRE_EQUAL((*c0_ht0r_head)[2], c0[2]);
				BOOST_REQUIRE_EQUAL((*c0_ht0r_tail)[2], c0[2]);
				// 每添加一个元素判断x-z面头尾指针是否指向当前元素坐标
				BOOST_REQUIRE_EQUAL((*c0_ht1r_head)[0], c0[0]);
				BOOST_REQUIRE_EQUAL((*c0_ht1r_tail)[0], c0[0]);
				BOOST_REQUIRE_EQUAL((*c0_ht1r_head)[1], c0[1]);
				BOOST_REQUIRE_EQUAL((*c0_ht1r_tail)[1], c0[1]);
				BOOST_REQUIRE_EQUAL((*c0_ht1r_head)[2], c0[2]);
				BOOST_REQUIRE_EQUAL((*c0_ht1r_tail)[2], c0[2]);
				// 每添加一个元素判断x-y面头指针指向第一个元素，尾指针指向最后一个元素
				BOOST_REQUIRE_EQUAL((*c0_ht2r_head)[0], c_x);
				BOOST_REQUIRE_EQUAL((*c0_ht2r_tail)[0], c0[0]);
				BOOST_REQUIRE_EQUAL((*c0_ht2r_head)[1], c_y);
				BOOST_REQUIRE_EQUAL((*c0_ht2r_tail)[1], c0[1]);
				BOOST_REQUIRE_EQUAL((*c0_ht2r_head)[2], c_z);
				BOOST_REQUIRE_EQUAL((*c0_ht2r_tail)[2], c0[2]);
			}

			// 测试维度 2 前后关系。
			// 测试第 1 个元素。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z }), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z }), true);
			const auto o1c0adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z });
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[2].prev, nullptr);
			const auto o1c0d2next = (*o1c0adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c0d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c0d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c0d2next)[2], c_z + 1);

			// 测试第 2 到第 9 个元素。
			for(int i=1;i<9;i++)
			{
				BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z+i }), nullptr);
				BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z +i}), true);
				const auto o1ciadj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z+i });
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[0].prev, nullptr);
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[0].next, nullptr);
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[1].prev, nullptr);
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[1].next, nullptr);
				const auto o1cid2prev = (*o1ciadj_ptr)[2].prev;
				BOOST_REQUIRE_EQUAL((*o1cid2prev)[0], c_x);
				BOOST_REQUIRE_EQUAL((*o1cid2prev)[1], c_y);
				BOOST_REQUIRE_EQUAL((*o1cid2prev)[2], c_z +i-1);
				const auto o1cid2next = (*o1ciadj_ptr)[2].next;
				BOOST_REQUIRE_EQUAL((*o1cid2next)[0], c_x);
				BOOST_REQUIRE_EQUAL((*o1cid2next)[1], c_y);
				BOOST_REQUIRE_EQUAL((*o1cid2next)[2], c_z + i+1);
			}
			
			// 测试第 10 个元素。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z +9}), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z +9}), true);
			const auto o1c9adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z +9});
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[2].next, nullptr);
			const auto o1c9d2prev = (*o1c9adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c9d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c9d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c9d2prev)[2], c_z + 8);
		}

		/**
		 * 测试三维正交链接坐标在单维度方向上批量删除元素。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DRemoveInSingleDimension)
		{
			LinkedCoordinate3DFixture o1;
			std::vector<std::vector<unsigned int>> c;
			// y-z 面头尾指针组。因为此处测试的是二维坐标，故头尾指针组应该是一维数据。但为了普适处理，头尾指针组坐标依然与坐标保持相同维度，而当前维度全部置零，下同。
			const auto& ht0 = o1.c->__debug_head_and_tail_in_all_dimensions[0];
			// x-z 面头尾指针组。
			const auto& ht1 = o1.c->__debug_head_and_tail_in_all_dimensions[1];
			// x-y 面头尾指针组。
			const auto& ht2 = o1.c->__debug_head_and_tail_in_all_dimensions[2];

			const unsigned int c_x = 5;
			const unsigned int c_y = 7;
			const unsigned int c_z = 9;
			unsigned int size = 10;
			std::vector<unsigned int> c0 = { c_x, c_y, c_z };
			std::vector<unsigned int> c9 = { c_x, c_y, c_z + size - 1 };
			std::vector<unsigned int> c5 = { c_x, c_y, c_z + 5 };
			for(unsigned int i = 0; i < size; i++)
			{
				std::vector<unsigned int> ci = { c_x, c_y, i + c_z };
				// 添加的过程不能抛出异常
				// 添加的元素内容是当前序号 i。
				BOOST_REQUIRE_EQUAL(o1.c->get(ci), nullptr);
				BOOST_REQUIRE_NO_THROW(o1.c->set(ci, std::make_shared<unsigned int>(i)));
			}
			// 删第 1 个。
			BOOST_REQUIRE_NE(o1.c->get(c0), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c0), true);
			const auto o1c0adj_ptr = o1.c->__debug_get_adjacents(c0);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c0adj_ptr)[2].prev, nullptr);
			const auto o1c0d2next = (*o1c0adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c0d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c0d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c0d2next)[2], c_z + 1);

			BOOST_REQUIRE_EQUAL(o1.c->erase(c0), 1);

			BOOST_REQUIRE_EQUAL(o1.c->get(c0), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c0), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_get_adjacents(c0), nullptr);

			BOOST_REQUIRE_EQUAL(ht0.size(), size);
			BOOST_REQUIRE_EQUAL(ht1.size(), size);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);
			
			BOOST_REQUIRE_EQUAL(o1.c->erase(c0), 0);

			BOOST_REQUIRE_EQUAL(o1.c->get(c0), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c0), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_get_adjacents(c0), nullptr);

			BOOST_REQUIRE_EQUAL(ht0.size(), size);
			BOOST_REQUIRE_EQUAL(ht1.size(), size);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);
			
			// 当前坐标的y-z面头指针
			auto c0_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 0))->second.head;
			// 当前坐标的y-z面尾指针
			auto c0_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 0))->second.tail;
			// 当前坐标的x-z面头指针
			auto c0_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 1))->second.head;
			// 当前坐标的x-z面尾指针
			auto c0_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 1))->second.tail;
			// 当前坐标的x-y面头指针
			auto c0_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 2))->second.head;
			// 当前坐标的x-y面尾指针
			auto c0_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c0, 2))->second.tail;

			BOOST_REQUIRE_EQUAL(c0_ht0r_head, nullptr);
			BOOST_REQUIRE_EQUAL(c0_ht0r_tail, nullptr);
			BOOST_REQUIRE_EQUAL(c0_ht1r_head, nullptr);
			BOOST_REQUIRE_EQUAL(c0_ht1r_tail, nullptr);
			BOOST_REQUIRE_NE(c0_ht2r_head, nullptr);
			BOOST_REQUIRE_NE(c0_ht2r_tail, nullptr);

			// 每添加一个元素判断x-y面头指针指向第一个元素，尾指针指向最后一个元素
			BOOST_REQUIRE_EQUAL((*c0_ht2r_head)[0], c_x);
			BOOST_REQUIRE_EQUAL((*c0_ht2r_tail)[0], c0[0]);
			BOOST_REQUIRE_EQUAL((*c0_ht2r_head)[1], c_y);
			BOOST_REQUIRE_EQUAL((*c0_ht2r_tail)[1], c0[1]);
			BOOST_REQUIRE_EQUAL((*c0_ht2r_head)[2], c_z + 1);
			BOOST_REQUIRE_EQUAL((*c0_ht2r_tail)[2], c_z + size - 1);

			// 删最后一个。
			BOOST_REQUIRE_NE(o1.c->get(c9), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c9), true);
			const auto o1c9adj_ptr = o1.c->__debug_get_adjacents(c9);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c9adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_NE((*o1c9adj_ptr)[2].prev, nullptr);
			const auto o1c9d2prev = (*o1c9adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c9d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c9d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c9d2prev)[2], c_z +size-2);

			BOOST_REQUIRE_EQUAL(o1.c->erase(c9), 1);

			BOOST_REQUIRE_EQUAL(o1.c->get(c9), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c9), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_get_adjacents(c9), nullptr);

			BOOST_REQUIRE_EQUAL(ht0.size(), size);
			BOOST_REQUIRE_EQUAL(ht1.size(), size);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);

			BOOST_REQUIRE_EQUAL(o1.c->erase(c9), 0);

			BOOST_REQUIRE_EQUAL(o1.c->get(c9), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c9), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_get_adjacents(c9), nullptr);

			BOOST_REQUIRE_EQUAL(ht0.size(), size);
			BOOST_REQUIRE_EQUAL(ht1.size(), size);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);

			// 当前坐标的y-z面头指针
			auto c9_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 0))->second.head;
			// 当前坐标的y-z面尾指针
			auto c9_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 0))->second.tail;
			// 当前坐标的x-z面头指针
			auto c9_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 1))->second.head;
			// 当前坐标的x-z面尾指针
			auto c9_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 1))->second.tail;
			// 当前坐标的x-y面头指针
			auto c9_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 2))->second.head;
			// 当前坐标的x-y面尾指针
			auto c9_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 2))->second.tail;

			BOOST_REQUIRE_EQUAL(c9_ht0r_head, nullptr);
			BOOST_REQUIRE_EQUAL(c9_ht0r_tail, nullptr);
			BOOST_REQUIRE_EQUAL(c9_ht1r_head, nullptr);
			BOOST_REQUIRE_EQUAL(c9_ht1r_tail, nullptr);
			BOOST_REQUIRE_NE(c9_ht2r_head, nullptr);
			BOOST_REQUIRE_NE(c9_ht2r_tail, nullptr);

			// 每添加一个元素判断x-y面头指针指向第一个元素，尾指针指向最后一个元素
			BOOST_REQUIRE_EQUAL((*c9_ht2r_head)[0], c_x);
			BOOST_REQUIRE_EQUAL((*c9_ht2r_tail)[0], c9[0]);
			BOOST_REQUIRE_EQUAL((*c9_ht2r_head)[1], c_y);
			BOOST_REQUIRE_EQUAL((*c9_ht2r_tail)[1], c9[1]);
			BOOST_REQUIRE_EQUAL((*c9_ht2r_head)[2], c_z +1);
			BOOST_REQUIRE_EQUAL((*c9_ht2r_tail)[2], c_z + size - 2);

			// 删中间一个。
			BOOST_REQUIRE_NE(o1.c->get(c5), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c5), true);
			const auto o1c5adj_ptr = o1.c->__debug_get_adjacents(c5);
			BOOST_REQUIRE_EQUAL((*o1c5adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c5adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c5adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c5adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_NE((*o1c5adj_ptr)[2].prev, nullptr);
			const auto o1c5d2prev = (*o1c5adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c5d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c5d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c5d2prev)[2], c_z + 4);
			const auto o1c5d2next = (*o1c5adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c5d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c5d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c5d2next)[2], c_z + 6);

			BOOST_REQUIRE_EQUAL(o1.c->erase(c5), 1);

			BOOST_REQUIRE_EQUAL(o1.c->get(c5), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c5), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_get_adjacents(c5), nullptr);

			BOOST_REQUIRE_EQUAL(ht0.size(), size);
			BOOST_REQUIRE_EQUAL(ht1.size(), size);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);

			BOOST_REQUIRE_EQUAL(o1.c->erase(c5), 0);

			BOOST_REQUIRE_EQUAL(o1.c->get(c5), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c5), false);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_get_adjacents(c5), nullptr);

			BOOST_REQUIRE_EQUAL(ht0.size(), size);
			BOOST_REQUIRE_EQUAL(ht1.size(), size);
			BOOST_REQUIRE_EQUAL(ht2.size(), 1);

			// 当前坐标的y-z面头指针
			auto c5_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 0))->second.head;
			// 当前坐标的y-z面尾指针
			auto c5_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 0))->second.tail;
			// 当前坐标的x-z面头指针
			auto c5_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 1))->second.head;
			// 当前坐标的x-z面尾指针
			auto c5_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 1))->second.tail;
			// 当前坐标的x-y面头指针
			auto c5_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 2))->second.head;
			// 当前坐标的x-y面尾指针
			auto c5_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c9, 2))->second.tail;

			BOOST_REQUIRE_EQUAL(c5_ht0r_head, nullptr);
			BOOST_REQUIRE_EQUAL(c5_ht0r_tail, nullptr);
			BOOST_REQUIRE_EQUAL(c5_ht1r_head, nullptr);
			BOOST_REQUIRE_EQUAL(c5_ht1r_tail, nullptr);
			BOOST_REQUIRE_NE(c5_ht2r_head, nullptr);
			BOOST_REQUIRE_NE(c5_ht2r_tail, nullptr);

			// 每添加一个元素判断x-y面头指针指向第一个元素，尾指针指向最后一个元素
			BOOST_REQUIRE_EQUAL((*c5_ht2r_head)[0], c_x);
			BOOST_REQUIRE_EQUAL((*c5_ht2r_tail)[0], c5[0]);
			BOOST_REQUIRE_EQUAL((*c5_ht2r_head)[1], c_y);
			BOOST_REQUIRE_EQUAL((*c5_ht2r_tail)[1], c5[1]);
			BOOST_REQUIRE_EQUAL((*c5_ht2r_head)[2], c_z + 1);
			BOOST_REQUIRE_EQUAL((*c5_ht2r_tail)[2], c_z + size - 2);

			// 测试连续性
			// 测试第 1 个元素：5,7,10。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z +1}), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z +1}), true);
			const auto o1c00adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z+1 });
			BOOST_REQUIRE_EQUAL((*o1c00adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c00adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c00adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c00adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c00adj_ptr)[2].prev, nullptr);
			const auto o1c00d2next = (*o1c00adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c00d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c00d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c00d2next)[2], c_z + 2);

			// 测试第 2 到第 3 个元素：5,7,11;5,7,12。
			for (int i = 1; i < 3; i++)
			{
				BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z +1+ i }), nullptr);
				BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z +1+ i }), true);
				const auto o1ciadj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z+1 + i });
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[0].prev, nullptr);
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[0].next, nullptr);
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[1].prev, nullptr);
				BOOST_REQUIRE_EQUAL((*o1ciadj_ptr)[1].next, nullptr);
				const auto o1cid2prev = (*o1ciadj_ptr)[2].prev;
				BOOST_REQUIRE_EQUAL((*o1cid2prev)[0], c_x);
				BOOST_REQUIRE_EQUAL((*o1cid2prev)[1], c_y);
				BOOST_REQUIRE_EQUAL((*o1cid2prev)[2], c_z + i );
				const auto o1cid2next = (*o1ciadj_ptr)[2].next;
				BOOST_REQUIRE_EQUAL((*o1cid2next)[0], c_x);
				BOOST_REQUIRE_EQUAL((*o1cid2next)[1], c_y);
				BOOST_REQUIRE_EQUAL((*o1cid2next)[2], c_z + i + 2);
			}

			// 测试第 4 个元素：5,7,13。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z + 4 }), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z + 4 }), true);
			const auto o1c3adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z + 4 });
			BOOST_REQUIRE_EQUAL((*o1c3adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c3adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c3adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c3adj_ptr)[1].next, nullptr);
			const auto o1c3d2prev = (*o1c3adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c3d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c3d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c3d2prev)[2], c_z + 3);
			const auto o1c3d2next = (*o1c3adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c3d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c3d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c3d2next)[2], c_z + 6);
			
			// 测试第 5 个元素：5,7,15。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z + 6 }), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z + 6}), true);
			const auto o1c4adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z + 6 });
			BOOST_REQUIRE_EQUAL((*o1c4adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c4adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c4adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c4adj_ptr)[1].next, nullptr);
			const auto o1c4d2prev = (*o1c4adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c4d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c4d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c4d2prev)[2], c_z + 4);
			const auto o1c4d2next = (*o1c4adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c4d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c4d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c4d2next)[2], c_z + 7);

			// 测试第 6 个元素：5,7,16。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z + 7 }), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z + 7 }), true);
			const auto o1c55adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z + 7 });
			BOOST_REQUIRE_EQUAL((*o1c55adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c55adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c55adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c55adj_ptr)[1].next, nullptr);
			const auto o1c55d2prev = (*o1c55adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c55d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c55d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c55d2prev)[2], c_z + 6);
			const auto o1c55d2next = (*o1c55adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c55d2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c55d2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c55d2next)[2], c_z + 8);

			// 测试第 7 个元素：5,7,17。
			BOOST_REQUIRE_NE(o1.c->get({ c_x, c_y, c_z + 8 }), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists({ c_x, c_y, c_z + 8 }), true);
			const auto o1c6adj_ptr = o1.c->__debug_get_adjacents({ c_x, c_y, c_z + 8 });
			BOOST_REQUIRE_EQUAL((*o1c6adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c6adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c6adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c6adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c6adj_ptr)[2].next, nullptr);
			const auto o1c6d2prev = (*o1c6adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c6d2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c6d2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c6d2prev)[2], c_z + 7);
		}

		/**
		 * 测试三维正交链接坐标在多维度方向上批量添加元素。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DAddBatchInMultipleDimensions)
		{
			LinkedCoordinate3DwithSevenElementsFixture1 o1;
			const auto c11 = o1.c11;
			const auto c13 = o1.c13;
			const auto c21 = o1.c21;
			const auto c23 = o1.c23;
			const auto c31 = o1.c31;
			const auto c33 = o1.c33;
			const auto c_center = o1.c_center;
			const auto c_x = o1.c_x;
			const auto c_y = o1.c_y;
			const auto c_z = o1.c_z;

			// y-z 面头尾指针组。因为此处测试的是二维坐标，故头尾指针组应该是一维数据。但为了普适处理，头尾指针组坐标依然与坐标保持相同维度，而当前维度全部置零，下同。
			const auto& ht0 = o1.c->__debug_head_and_tail_in_all_dimensions[0];
			// x-z 面头尾指针组。
			const auto& ht1 = o1.c->__debug_head_and_tail_in_all_dimensions[1];
			// x-y 面头尾指针组。
			const auto& ht2 = o1.c->__debug_head_and_tail_in_all_dimensions[2];

#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail
			// 测试头尾节点
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c11
			//     测试 c11(5, 7, 9) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto c11_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c11, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto c11_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c11, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto c11_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c11, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto c11_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c11, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto c11_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c11, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto c11_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c11, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c11_ht0r_head)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c11_ht0r_head)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c11_ht0r_head)[2], c11[2]);
			BOOST_CHECK_EQUAL((*c11_ht0r_tail)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c11_ht0r_tail)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c11_ht0r_tail)[2], c13[2]);

			BOOST_CHECK_EQUAL((*c11_ht1r_head)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c11_ht1r_head)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c11_ht1r_head)[2], c11[2]);
			BOOST_CHECK_EQUAL((*c11_ht1r_tail)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c11_ht1r_tail)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c11_ht1r_tail)[2], c11[2]);

			BOOST_CHECK_EQUAL((*c11_ht2r_head)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c11_ht2r_head)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c11_ht2r_head)[2], c11[2]);
			BOOST_CHECK_EQUAL((*c11_ht2r_tail)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c11_ht2r_tail)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c11_ht2r_tail)[2], c11[2]);
#pragma endregion
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c_center
			//     测试 c_center=(6, 7, 9) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto  c_center_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c_center, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto  c_center_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c_center, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto  c_center_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c_center, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto  c_center_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c_center, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto  c_center_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c_center, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto  c_center_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c_center, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c_center_ht0r_head)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c_center_ht0r_head)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c_center_ht0r_head)[2], c11[2]);
			BOOST_CHECK_EQUAL((*c_center_ht0r_tail)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c_center_ht0r_tail)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c_center_ht0r_tail)[2], c13[2]);

			BOOST_CHECK_EQUAL((*c_center_ht1r_head)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c_center_ht1r_head)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c_center_ht1r_head)[2], c21[2]);
			BOOST_CHECK_EQUAL((*c_center_ht1r_tail)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c_center_ht1r_tail)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c_center_ht1r_tail)[2], c23[2]);

			BOOST_CHECK_EQUAL((*c_center_ht2r_head)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c_center_ht2r_head)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c_center_ht2r_head)[2], c31[2]);
			BOOST_CHECK_EQUAL((*c_center_ht2r_tail)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c_center_ht2r_tail)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c_center_ht2r_tail)[2], c33[2]);
#pragma endregion
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c11
			//     测试 c13=(7, 7, 9) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto  c13_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c13, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto  c13_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c13, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto  c13_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c13, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto  c13_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c13, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto  c13_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c13, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto  c13_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c13, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c13_ht0r_head)[0], c11[0]);
			BOOST_CHECK_EQUAL((*c13_ht0r_head)[1], c11[1]);
			BOOST_CHECK_EQUAL((*c13_ht0r_head)[2], c11[2]);
			BOOST_CHECK_EQUAL((*c13_ht0r_tail)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c13_ht0r_tail)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c13_ht0r_tail)[2], c13[2]);

			BOOST_CHECK_EQUAL((*c13_ht1r_head)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c13_ht1r_head)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c13_ht1r_head)[2], c13[2]);
			BOOST_CHECK_EQUAL((*c13_ht1r_tail)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c13_ht1r_tail)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c13_ht1r_tail)[2], c13[2]);

			BOOST_CHECK_EQUAL((*c13_ht2r_head)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c13_ht2r_head)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c13_ht2r_head)[2], c13[2]);
			BOOST_CHECK_EQUAL((*c13_ht2r_tail)[0], c13[0]);
			BOOST_CHECK_EQUAL((*c13_ht2r_tail)[1], c13[1]);
			BOOST_CHECK_EQUAL((*c13_ht2r_tail)[2], c13[2]);
#pragma endregion
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c21
			//     测试 c21=(6, 6, 9) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto  c21_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c21, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto  c21_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c21, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto  c21_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c21, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto  c21_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c21, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto  c21_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c21, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto  c21_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c21, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c21_ht0r_head)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c21_ht0r_head)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c21_ht0r_head)[2], c21[2]);
			BOOST_CHECK_EQUAL((*c21_ht0r_tail)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c21_ht0r_tail)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c21_ht0r_tail)[2], c21[2]);

			BOOST_CHECK_EQUAL((*c21_ht1r_head)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c21_ht1r_head)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c21_ht1r_head)[2], c21[2]);
			BOOST_CHECK_EQUAL((*c21_ht1r_tail)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c21_ht1r_tail)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c21_ht1r_tail)[2], c23[2]);

			BOOST_CHECK_EQUAL((*c21_ht2r_head)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c21_ht2r_head)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c21_ht2r_head)[2], c21[2]);
			BOOST_CHECK_EQUAL((*c21_ht2r_tail)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c21_ht2r_tail)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c21_ht2r_tail)[2], c21[2]);
#pragma endregion
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c23
			//     测试 c23=(6, 8, 9) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto  c23_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c23, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto  c23_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c23, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto  c23_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c23, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto  c23_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c23, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto  c23_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c23, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto  c23_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c23, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c23_ht0r_head)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c23_ht0r_head)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c23_ht0r_head)[2], c23[2]);
			BOOST_CHECK_EQUAL((*c23_ht0r_tail)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c23_ht0r_tail)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c23_ht0r_tail)[2], c23[2]);

			BOOST_CHECK_EQUAL((*c23_ht1r_head)[0], c21[0]);
			BOOST_CHECK_EQUAL((*c23_ht1r_head)[1], c21[1]);
			BOOST_CHECK_EQUAL((*c23_ht1r_head)[2], c21[2]);
			BOOST_CHECK_EQUAL((*c23_ht1r_tail)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c23_ht1r_tail)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c23_ht1r_tail)[2], c23[2]);

			BOOST_CHECK_EQUAL((*c23_ht2r_head)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c23_ht2r_head)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c23_ht2r_head)[2], c23[2]);
			BOOST_CHECK_EQUAL((*c23_ht2r_tail)[0], c23[0]);
			BOOST_CHECK_EQUAL((*c23_ht2r_tail)[1], c23[1]);
			BOOST_CHECK_EQUAL((*c23_ht2r_tail)[2], c23[2]);
#pragma endregion
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c31
			//     测试 c31=(6, 7, 8) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto  c31_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c31, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto  c31_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c31, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto  c31_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c31, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto  c31_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c31, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto  c31_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c31, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto  c31_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c31, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c31_ht0r_head)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c31_ht0r_head)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c31_ht0r_head)[2], c31[2]);
			BOOST_CHECK_EQUAL((*c31_ht0r_tail)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c31_ht0r_tail)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c31_ht0r_tail)[2], c31[2]);

			BOOST_CHECK_EQUAL((*c31_ht1r_head)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c31_ht1r_head)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c31_ht1r_head)[2], c31[2]);
			BOOST_CHECK_EQUAL((*c31_ht1r_tail)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c31_ht1r_tail)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c31_ht1r_tail)[2], c31[2]);

			BOOST_CHECK_EQUAL((*c31_ht2r_head)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c31_ht2r_head)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c31_ht2r_head)[2], c31[2]);
			BOOST_CHECK_EQUAL((*c31_ht2r_tail)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c31_ht2r_tail)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c31_ht2r_tail)[2], c33[2]);
#pragma endregion
#pragma region 测试_LinkedCoordinate_3D_Add_Batch_In_Double_Dimensions__Head_and_Tail_c33
			//     测试 c33=(6, 7, 10) 的相关头尾节点。

			//         当前坐标的y-z面头指针
			auto  c33_ht0r_head = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c33, 0))->second.head;
			//         当前坐标的y-z面尾指针
			auto  c33_ht0r_tail = ht0.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c33, 0))->second.tail;
			//         当前坐标的x-z面头指针
			auto  c33_ht1r_head = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c33, 1))->second.head;
			//         当前坐标的x-z面尾指针
			auto  c33_ht1r_tail = ht1.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c33, 1))->second.tail;
			//         当前坐标的x-y面头指针
			auto  c33_ht2r_head = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c33, 2))->second.head;
			//         当前坐标的x-y面尾指针
			auto  c33_ht2r_tail = ht2.find(Coordinate<3, unsigned int>::coordinates_beyond_dimension(c33, 2))->second.tail;

			BOOST_CHECK_EQUAL((*c33_ht0r_head)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c33_ht0r_head)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c33_ht0r_head)[2], c33[2]);
			BOOST_CHECK_EQUAL((*c33_ht0r_tail)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c33_ht0r_tail)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c33_ht0r_tail)[2], c33[2]);

			BOOST_CHECK_EQUAL((*c33_ht1r_head)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c33_ht1r_head)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c33_ht1r_head)[2], c33[2]);
			BOOST_CHECK_EQUAL((*c33_ht1r_tail)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c33_ht1r_tail)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c33_ht1r_tail)[2], c33[2]);

			BOOST_CHECK_EQUAL((*c33_ht2r_head)[0], c31[0]);
			BOOST_CHECK_EQUAL((*c33_ht2r_head)[1], c31[1]);
			BOOST_CHECK_EQUAL((*c33_ht2r_head)[2], c31[2]);
			BOOST_CHECK_EQUAL((*c33_ht2r_tail)[0], c33[0]);
			BOOST_CHECK_EQUAL((*c33_ht2r_tail)[1], c33[1]);
			BOOST_CHECK_EQUAL((*c33_ht2r_tail)[2], c33[2]);
#pragma endregion
#pragma endregion

			// 测试连续性

			// c11 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c11), true);
			const auto o1c11adj_ptr = o1.c->__debug_get_adjacents(c11);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_NE((*o1c11adj_ptr)[0].next, nullptr);
			const auto o1c11d0next = (*o1c11adj_ptr)[0].next;
			BOOST_REQUIRE_EQUAL((*o1c11d0next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c11d0next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c11d0next)[2], c_z);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[2].next, nullptr);

			// c_center 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c_center), true);
			const auto o1c_centeradj_ptr = o1.c->__debug_get_adjacents(c_center);
			BOOST_REQUIRE_NE((*o1c_centeradj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_NE((*o1c_centeradj_ptr)[0].next, nullptr);
			const auto o1c_centerd0prev = (*o1c_centeradj_ptr)[0].prev;
			BOOST_REQUIRE_EQUAL((*o1c_centerd0prev)[0], c_x-1);
			BOOST_REQUIRE_EQUAL((*o1c_centerd0prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c_centerd0prev)[2], c_z);
			const auto o1c_centerd0next = (*o1c_centeradj_ptr)[0].next;
			BOOST_REQUIRE_EQUAL((*o1c_centerd0next)[0], c_x+1);
			BOOST_REQUIRE_EQUAL((*o1c_centerd0next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c_centerd0next)[2], c_z);
			BOOST_REQUIRE_NE((*o1c_centeradj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_NE((*o1c_centeradj_ptr)[1].next, nullptr);
			const auto o1c_centerd1prev = (*o1c_centeradj_ptr)[1].prev;
			BOOST_REQUIRE_EQUAL((*o1c_centerd1prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c_centerd1prev)[1], c_y-1);
			BOOST_REQUIRE_EQUAL((*o1c_centerd1prev)[2], c_z);
			const auto o1c_centerd1next = (*o1c_centeradj_ptr)[1].next;
			BOOST_REQUIRE_EQUAL((*o1c_centerd1next)[0], c_x );
			BOOST_REQUIRE_EQUAL((*o1c_centerd1next)[1], c_y+1);
			BOOST_REQUIRE_EQUAL((*o1c_centerd1next)[2], c_z);
			BOOST_REQUIRE_NE((*o1c_centeradj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_NE((*o1c_centeradj_ptr)[2].next, nullptr);
			const auto o1c_centerd2prev = (*o1c_centeradj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c_centerd2prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c_centerd2prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c_centerd2prev)[2], c_z-1);
			const auto o1c_centerd2next = (*o1c_centeradj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c_centerd2next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c_centerd2next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c_centerd2next)[2], c_z+1);

			// c13 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c13), true);
			const auto o1c13adj_ptr = o1.c->__debug_get_adjacents(c13);
			BOOST_REQUIRE_NE((*o1c13adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[0].next, nullptr);
			const auto o1c13d0prev = (*o1c13adj_ptr)[0].prev;
			BOOST_REQUIRE_EQUAL((*o1c13d0prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c13d0prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c13d0prev)[2], c_z);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[2].next, nullptr);

			// c21 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c21), true);
			const auto o1c21adj_ptr = o1.c->__debug_get_adjacents(c21);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_NE((*o1c21adj_ptr)[1].next, nullptr);
			const auto o1c21d1next = (*o1c21adj_ptr)[1].next;
			BOOST_REQUIRE_EQUAL((*o1c21d1next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c21d1next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c21d1next)[2], c_z);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[2].next, nullptr);

			// c23 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c23), true);
			const auto o1c23adj_ptr = o1.c->__debug_get_adjacents(c23);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_NE((*o1c23adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[1].next, nullptr);
			const auto o1c23d1prev = (*o1c23adj_ptr)[1].prev;
			BOOST_REQUIRE_EQUAL((*o1c23d1prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c23d1prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c23d1prev)[2], c_z);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[2].next, nullptr);

			// c31 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c31), true);
			const auto o1c31adj_ptr = o1.c->__debug_get_adjacents(c31);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_NE((*o1c31adj_ptr)[2].next, nullptr);
			const auto o1c31d1next = (*o1c31adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c31d1next)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c31d1next)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c31d1next)[2], c_z);

			// c33 连续性
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c33), true);
			const auto o1c33adj_ptr = o1.c->__debug_get_adjacents(c33);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_NE((*o1c33adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[2].next, nullptr);
			const auto o1c33d1prev = (*o1c33adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c33d1prev)[0], c_x);
			BOOST_REQUIRE_EQUAL((*o1c33d1prev)[1], c_y);
			BOOST_REQUIRE_EQUAL((*o1c33d1prev)[2], c_z);
		}

		/**
		 * 测试三维正交链接坐标在多维度方向上批量删除元素。
		 */
		BOOST_AUTO_TEST_CASE(TestLinkedCoordinate3DRemoveInMultipleDimensions)
		{
			LinkedCoordinate3DwithSevenElementsFixture1 o1;
			const auto c11 = o1.c11;
			const auto c13 = o1.c13;
			const auto c21 = o1.c21;
			const auto c23 = o1.c23;
			const auto c31 = o1.c31;
			const auto c33 = o1.c33;
			const auto c_center = o1.c_center;
			const auto c_x = o1.c_x;
			const auto c_y = o1.c_y;
			const auto c_z = o1.c_z;

			BOOST_REQUIRE_EQUAL(o1.c->erase(c_center), 1);
		    // 验证 c11 在维度 0 的前驱为空，后继为 c13，其它维度的前驱后继均为空。
			BOOST_REQUIRE_NE(o1.c->get(c11), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c11), true);
			const auto o1c11adj_ptr = o1.c->__debug_get_adjacents(c11);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[0].prev, nullptr);
			const auto o1c11d0next = (*o1c11adj_ptr)[0].next;
			BOOST_REQUIRE_EQUAL((*o1c11d0next)[0], c13[0]);
			BOOST_REQUIRE_EQUAL((*o1c11d0next)[1], c13[1]);
			BOOST_REQUIRE_EQUAL((*o1c11d0next)[2], c13[2]);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c11adj_ptr)[2].next, nullptr);
			// 验证 c13 在维度 0 的前驱为c11，后继为空，其它维度的前驱后继均为空。
			BOOST_REQUIRE_NE(o1.c->get(c13), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c13), true);
			const auto o1c13adj_ptr = o1.c->__debug_get_adjacents(c13);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[0].next, nullptr);
			const auto o1c13d0prev = (*o1c13adj_ptr)[0].prev;
			BOOST_REQUIRE_EQUAL((*o1c13d0prev)[0], c11[0]);
			BOOST_REQUIRE_EQUAL((*o1c13d0prev)[1], c11[1]);
			BOOST_REQUIRE_EQUAL((*o1c13d0prev)[2], c11[2]);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c13adj_ptr)[2].next, nullptr);
			// 验证 c21 在维度 1 的前驱为空，后继为c23，其它维度的前驱后继均为空。
			BOOST_REQUIRE_NE(o1.c->get(c21), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c21), true);
			const auto o1c21adj_ptr = o1.c->__debug_get_adjacents(c21);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[1].prev, nullptr);
			const auto o1c21d1next = (*o1c21adj_ptr)[1].next;
			BOOST_REQUIRE_EQUAL((*o1c21d1next)[0], c23[0]);
			BOOST_REQUIRE_EQUAL((*o1c21d1next)[1], c23[1]);
			BOOST_REQUIRE_EQUAL((*o1c21d1next)[2], c23[2]);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c21adj_ptr)[2].next, nullptr);
			// 验证 c23在维度 1 的前驱为c21，后继为空，其它维度的前驱后继均为空。
			BOOST_REQUIRE_NE(o1.c->get(c23), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c23), true);
			const auto o1c23adj_ptr = o1.c->__debug_get_adjacents(c23);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[1].next, nullptr);
			const auto o1c23d1prev = (*o1c23adj_ptr)[1].prev;
			BOOST_REQUIRE_EQUAL((*o1c23d1prev)[0], c21[0]);
			BOOST_REQUIRE_EQUAL((*o1c23d1prev)[1], c21[1]);
			BOOST_REQUIRE_EQUAL((*o1c23d1prev)[2], c21[2]);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[2].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c23adj_ptr)[2].next, nullptr);
			// 验证 c31在维度 2 的前驱为空，后继为c33，其它维度的前驱后继均为空。
			BOOST_REQUIRE_NE(o1.c->get(c31), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c31), true);
			const auto o1c31adj_ptr = o1.c->__debug_get_adjacents(c31);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c31adj_ptr)[2].prev, nullptr);
			const auto o1c31d1next = (*o1c31adj_ptr)[2].next;
			BOOST_REQUIRE_EQUAL((*o1c31d1next)[0], c33[0]);
			BOOST_REQUIRE_EQUAL((*o1c31d1next)[1], c33[1]);
			BOOST_REQUIRE_EQUAL((*o1c31d1next)[2], c33[2]);
			// 验证 c33在维度 2 的前驱为c31，后继为空，其它维度的前驱后继均为空。
			BOOST_REQUIRE_NE(o1.c->get(c33), nullptr);
			BOOST_REQUIRE_EQUAL(o1.c->__debug_adjacent_exists(c33), true);
			const auto o1c33adj_ptr = o1.c->__debug_get_adjacents(c33);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[0].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[0].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[1].next, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[1].prev, nullptr);
			BOOST_REQUIRE_EQUAL((*o1c33adj_ptr)[2].next, nullptr);
			const auto o1c33d1prev = (*o1c33adj_ptr)[2].prev;
			BOOST_REQUIRE_EQUAL((*o1c33d1prev)[0], c31[0]);
			BOOST_REQUIRE_EQUAL((*o1c33d1prev)[1], c31[1]);
			BOOST_REQUIRE_EQUAL((*o1c33d1prev)[2], c31[2]);
		}
        BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE(BenchmarkCoordinate3D)
		//深度为4
		BOOST_AUTO_TEST_CASE(TestBenckmarkCoordinate3DAddBatchInDepth4)
        {
            torch::manual_seed(1);
            RandomCoordinates256 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 4)), 0, pow(2, 4));
            Coordinate3DwithCoordinate3DFixture space;
            unsigned int count = 0;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                const auto& c2 = {
                        static_cast<unsigned int>(c1[i][0].item().toInt()),
                        static_cast<unsigned int>(c1[i][1].item().toInt()),
                        static_cast<unsigned int>(c1[i][2].item().toInt())
                };
                if (!space.c->exists(c2)) count++;
                space.c->set(c2,std::make_shared<std::vector<double>>(t));
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), count);
            const auto& v = *(space.c->get(
                {static_cast<unsigned int>(c1[0][0].item().toInt()),
                static_cast<unsigned int>(c1[0][1].item().toInt()),
                static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            // std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkCoordinate3DRemoveBatchInDepth4)
        {
            torch::manual_seed(1);
            RandomCoordinates256 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 4)), 0, pow(2, 4));
            Coordinate3DwithCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                   coords.coords[i][0].item().toDouble(),
                   coords.coords[i][1].item().toDouble(),
                   coords.coords[i][2].item().toDouble()
                };
                space.c->set(
                {  static_cast<unsigned int>(c1[i][0].item().toInt()),
                   static_cast<unsigned int>(c1[i][1].item().toInt()),
                   static_cast<unsigned int>(c1[i][2].item().toInt())},
                   std::make_shared<std::vector<double>>(t));
            }

            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
               space.c->erase(
                {static_cast<unsigned int>(c1[i][0].item().toInt()),
                 static_cast<unsigned int>(c1[i][1].item().toInt()),
                 static_cast<unsigned int>(c1[i][2].item().toInt())}
                 );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
		BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DAddBatchInDepth4)
        {
            torch::manual_seed(1);
            RandomCoordinates256 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 4)), 0, pow(2, 4));
            LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
            unsigned int count = 0;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                const auto& c2 = {
                        static_cast<unsigned int>(c1[i][0].item().toInt()),
                        static_cast<unsigned int>(c1[i][1].item().toInt()),
                        static_cast<unsigned int>(c1[i][2].item().toInt())};
                if (!space.c->exists(c2)) count++;
                space.c->set(c2,std::make_shared<std::vector<double>>(t));
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), count);
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DRemoveBatchInDepth4)
        {
            torch::manual_seed(1);
            RandomCoordinates256 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 4)), 0, pow(2, 4));
            LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                   coords.coords[i][0].item().toDouble(),
                   coords.coords[i][1].item().toDouble(),
                   coords.coords[i][2].item().toDouble()
                };
                space.c->set({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t)
                );
            }
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                space.c->erase({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())}
                );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
        //深度为8
        BOOST_AUTO_TEST_CASE(TestBenckmarkCoordinate3DAddBatchInDepth8)
        {
            torch::manual_seed(1);
            RandomCoordinates65536 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 8)), 0, pow(2, 8));
            Coordinate3DwithCoordinate3DFixture space;
            unsigned int count = 0;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                const auto& c2 = {
                        static_cast<unsigned int>(c1[i][0].item().toInt()),
                        static_cast<unsigned int>(c1[i][1].item().toInt()),
                        static_cast<unsigned int>(c1[i][2].item().toInt())};
                if (!space.c->exists(c2)) count++;
                space.c->set(c2, std::make_shared<std::vector<double>>(t)
                );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), count);
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
           // std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkCoordinate3DRemoveBatchInDepth8)
        {
		    torch::manual_seed(1);
		    RandomCoordinates65536 coords;
		    const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 8)), 0, pow(2, 8));
		    Coordinate3DwithCoordinate3DFixture space;
		    for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                space.c->set({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t)
                );
            }

            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                 space.c->erase(
                 {static_cast<unsigned int>(c1[i][0].item().toInt()),
                  static_cast<unsigned int>(c1[i][1].item().toInt()),
                  static_cast<unsigned int>(c1[i][2].item().toInt())}
                  );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DAddBatchInDepth8)
        {
            torch::manual_seed(1);
            RandomCoordinates65536 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 8)), 0, pow(2, 8));
            LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
            unsigned int count = 0;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                const auto& c2 = {
                        static_cast<unsigned int>(c1[i][0].item().toInt()),
                        static_cast<unsigned int>(c1[i][1].item().toInt()),
                        static_cast<unsigned int>(c1[i][2].item().toInt())};
                if (!space.c->exists(c2)) count++;
                space.c->set(c2, std::make_shared<std::vector<double>>(t));
            }
            BOOST_REQUIRE_LE(space.c->size(), count);
            const auto& v = *(space.c->get({
                static_cast<unsigned int>(c1[0][0].item().toInt()),
                static_cast<unsigned int>(c1[0][1].item().toInt()),
                static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
           //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DRemoveBatchInDepth8)
        {
		    torch::manual_seed(1);
		    RandomCoordinates65536 coords;
		    const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 8)), 0, pow(2, 8));
		    LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
		    for (int i = 0; i < coords.coords.size(0); i++)
		    {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                space.c->set({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t));
		    }
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                space.c->erase(
                       {static_cast<unsigned int>(c1[i][0].item().toInt()),
                        static_cast<unsigned int>(c1[i][1].item().toInt()),
                        static_cast<unsigned int>(c1[i][2].item().toInt())}
                        );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
           //std::cout << coords.coords[0] << std::endl;
        }
        //深度为12
        BOOST_AUTO_TEST_CASE(TestBenckmarkCoordinate3DAddBatchInDepth12)
        {
            torch::manual_seed(1);
            RandomCoordinates262144 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 12)), 0, pow(2, 12));
            Coordinate3DwithCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                   coords.coords[i][0].item().toDouble(),
                   coords.coords[i][1].item().toDouble(),
                   coords.coords[i][2].item().toDouble()
                };
                space.c->set(
                         {static_cast<unsigned int>(c1[i][0].item().toInt()),
                          static_cast<unsigned int>(c1[i][1].item().toInt()),
                          static_cast<unsigned int>(c1[i][2].item().toInt())},
                          std::make_shared<std::vector<double>>(t)
                          );
            }
            BOOST_REQUIRE_LE(space.c->size(), 262144);
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            // std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkCoordinate3DRemoveBatchInDepth12)
        {
		    torch::manual_seed(1);
		    RandomCoordinates262144 coords;
		    const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 12)), 0, pow(2, 12));
		    Coordinate3DwithCoordinate3DFixture space;
		    for (int i = 0; i < coords.coords.size(0); i++)
		    {
		        std::vector<double> t {
                          coords.coords[i][0].item().toDouble(),
                          coords.coords[i][1].item().toDouble(),
                          coords.coords[i][2].item().toDouble()
		        };
                space.c->set({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t));
		    }

            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
               space.c->erase(
               {static_cast<unsigned int>(c1[i][0].item().toInt()),
                static_cast<unsigned int>(c1[i][1].item().toInt()),
                static_cast<unsigned int>(c1[i][2].item().toInt())}
                );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DAddBatchInDepth12)
        {
		    torch::manual_seed(1);
		    RandomCoordinates262144 coords;
		    const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 12)), 0, pow(2, 12));
		    LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
		    for (int i = 0; i < coords.coords.size(0); i++)
		    {
		        std::vector<double> t {
		            coords.coords[i][0].item().toDouble(),
		            coords.coords[i][1].item().toDouble(),
		            coords.coords[i][2].item().toDouble()
		        };
		        space.c->set({
		            static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t));
		    }
            BOOST_REQUIRE_LE(space.c->size(), 262144);
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
		    //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DRemoveBatchInDepth12)
        {
		    torch::manual_seed(1);
            RandomCoordinates262144 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 12)), 0, pow(2, 12));
            LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                    coords.coords[i][0].item().toDouble(),
                    coords.coords[i][1].item().toDouble(),
                    coords.coords[i][2].item().toDouble()
                };
                space.c->set({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                             std::make_shared<std::vector<double>>(t)
                             );
            }
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                space.c->erase({
                    static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())}
                    );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
        //深度为12
        BOOST_AUTO_TEST_CASE(TestBenckmarkCoordinate3DAddBatchInDepth16)
        {
            torch::manual_seed(1);
            RandomCoordinates16777216 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 16)), 0, pow(2, 16));
            Coordinate3DwithCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                        coords.coords[i][0].item().toDouble(),
                        coords.coords[i][1].item().toDouble(),
                        coords.coords[i][2].item().toDouble()
                };
                space.c->set(
                {static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t)
                );
            }
            BOOST_REQUIRE_LE(space.c->size(), 16777216);
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            // std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkCoordinate3DRemoveBatchInDepth16)
        {
            torch::manual_seed(1);
            RandomCoordinates16777216 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 16)), 0, pow(2, 16));
            Coordinate3DwithCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                        coords.coords[i][0].item().toDouble(),
                        coords.coords[i][1].item().toDouble(),
                        coords.coords[i][2].item().toDouble()
                };
                space.c->set(
                {  static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t)
                );
            }

            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                space.c->erase(
                {static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())}
                );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DAddBatchInDepth16)
        {
            torch::manual_seed(1);
            RandomCoordinates16777216 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 16)), 0, pow(2, 16));
            LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                        coords.coords[i][0].item().toDouble(),
                        coords.coords[i][1].item().toDouble(),
                        coords.coords[i][2].item().toDouble()
                };
                space.c->set(
                {static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t)
                );
            }

            BOOST_REQUIRE_LE(space.c->size(), 16777216);
            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            //std::cout << coords.coords[0] << std::endl;
        }
        BOOST_AUTO_TEST_CASE(TestBenchmarkLinkedCoordinate3DRemoveBatchInDepth16)
        {
            torch::manual_seed(1);
            RandomCoordinates16777216 coords;
            const auto& c1 = torch::clamp(torch::round(coords.coords * pow(2, 16)), 0, pow(2, 16));
            LinkedCoordinate3DwithLinkedCoordinate3DFixture space;
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                std::vector<double> t {
                        coords.coords[i][0].item().toDouble(),
                        coords.coords[i][1].item().toDouble(),
                        coords.coords[i][2].item().toDouble()
                };
                space.c->set(
                 {static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())},
                    std::make_shared<std::vector<double>>(t)
                );
            }

            const auto& v = *(space.c->get(
                    {static_cast<unsigned int>(c1[0][0].item().toInt()),
                     static_cast<unsigned int>(c1[0][1].item().toInt()),
                     static_cast<unsigned int>(c1[0][2].item().toInt())}
            ));
            BOOST_REQUIRE_EQUAL(coords.coords[0][0].item().toDouble(), v[0]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][1].item().toDouble(), v[1]);
            BOOST_REQUIRE_EQUAL(coords.coords[0][2].item().toDouble(), v[2]);
            for (int i = 0; i < coords.coords.size(0); i++)
            {
                space.c->erase(
                {static_cast<unsigned int>(c1[i][0].item().toInt()),
                    static_cast<unsigned int>(c1[i][1].item().toInt()),
                    static_cast<unsigned int>(c1[i][2].item().toInt())}
                );
            }
            BOOST_REQUIRE_EQUAL(space.c->size(), 0);
            //std::cout << coords.coords[0] << std::endl;
        }
		BOOST_AUTO_TEST_SUITE_END()

	}
}

