/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/

#ifndef __ORTHOGONALLINKEDOCTREE_POINTLISTFIXTURE_H__
#define __ORTHOGONALLINKEDOCTREE_POINTLISTFIXTURE_H__

#include "PointList.h"
#include "PointFixture.h"

namespace vistart
{
    namespace orthogonal_linked_octree
    {
        class PointListFixture : public vistart::point_cloud_base_presentation::PointList<PointFixture> {
        public:
            PointListFixture(unsigned int count = 10, unsigned int depth = 5)
            {
                InsertRandomPoints(count, depth);
            }

            void InsertRandomPoints(unsigned int count = 10, unsigned int depth = 5)
            {
                for (int i = 0; i < count; i++)
                {
                    InsertRandomPoint(depth);
                }
            }

            void InsertRandomPoint(unsigned int depth = 5)
            {
                auto point = std::make_shared<PointFixture>(depth);
                this->points->emplace_back(point);
            }
        };
    }
}


#endif //__ORTHOGONALLINKEDOCTREE_POINTLISTFIXTURE_H__
