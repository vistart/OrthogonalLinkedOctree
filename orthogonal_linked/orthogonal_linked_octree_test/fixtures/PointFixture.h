/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/

#ifndef __ORTHOGONALLINKEDOCTREE_POINTFIXTURE_H__
#define __ORTHOGONALLINKEDOCTREE_POINTFIXTURE_H__

#include "Point.h"
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> // Header file needed to use time
#include <torch/torch.h>
#include <assert.h>

namespace vistart
{
    namespace orthogonal_linked_octree
    {
        class PointFixture : public vistart::point_cloud_base_presentation::Point {
        public:
            PointFixture(at::Tensor coord, unsigned int depth = 5)
            {
                assert(coord.size(0) == 3);
                Point(coord[0].item().toDouble(), coord[1].item().toDouble(), coord[2].item().toDouble());
            }
        };
    }
}


#endif //__ORTHOGONALLINKEDOCTREE_POINTFIXTURE_H__
