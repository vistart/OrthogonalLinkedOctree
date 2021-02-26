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
#include <torch/torch.h>

namespace vistart
{
    namespace orthogonal_linked_octree
    {
        class PointListFixture : public vistart::point_cloud_base_presentation::PointList<PointFixture> {
        public:
            PointListFixture(unsigned int count = 0x10000, unsigned int depth = 8)
            {
                InsertRandomPoints(count, depth);
            }

            void InsertRandomPoints(unsigned int count = 0x10000, unsigned int depth = 8)
            {
                const auto& rp = at::rand({count, 3}) * pow(2, depth);
                for (int i = 0; i < count; i++)
                {
                    InsertRandomPoint(rp[i], depth);
                }
            }

            void InsertRandomPoint(const at::Tensor point, unsigned int depth = 8)
            {
                auto p = std::make_shared<PointFixture>(point, depth);
                this->points->emplace_back(p);
            }
        };
    }
}


#endif //__ORTHOGONALLINKEDOCTREE_POINTLISTFIXTURE_H__
