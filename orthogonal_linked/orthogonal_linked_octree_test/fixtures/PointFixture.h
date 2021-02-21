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

namespace vistart
{
    namespace orthogonal_linked_octree
    {
        class PointFixture : public vistart::point_cloud_base_presentation::Point {
        public:
            PointFixture(unsigned int depth = 5)
            {
                unsigned seed = time(0);
                srand(seed);
                X(rand() % static_cast<unsigned int>(pow(2, depth)) + 1);
                Y(rand() % static_cast<unsigned int>(pow(2, depth)) + 1);
                Z(rand() % static_cast<unsigned int>(pow(2, depth)) + 1);
            }
        };
    }
}


#endif //__ORTHOGONALLINKEDOCTREE_POINTFIXTURE_H__
