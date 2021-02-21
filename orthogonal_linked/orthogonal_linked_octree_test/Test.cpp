/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/

#define BOOST_TEST_MODULE TestLinkedOctree
#include <boost/test/included/unit_test.hpp>

#include "LinkedOctree.h"
#include "NodeCoordinate.h"
#include "OctreeNode.h"
#include "fixtures/PointFixture.h"
#include "fixtures/PointListFixture.h"

namespace vistart
{
    namespace orthogonal_linked_octree
    {
#pragma region 夹具
#pragma region Coordinate3D
        struct LinkedOctreeFixture1
        {
            std::shared_ptr<LinkedOctree<PointListFixture, PointFixture>> o;
            const std::shared_ptr<PointListFixture> p;
            LinkedOctreeFixture1()
            {
            }
            ~LinkedOctreeFixture1() = default;
        };
#pragma endregion
#pragma endregion
        BOOST_AUTO_TEST_SUITE(TestLinkedOctree)
        BOOST_AUTO_TEST_CASE(TestLinkedOctreeInit)
        {
            LinkedOctreeFixture1 f;
            BOOST_TEST(f.p == nullptr);
        }
        BOOST_AUTO_TEST_SUITE_END()
    }
}