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
#ifndef __OCTREE_NODE_H__
#define __OCTREE_NODE_H__

#include "../../file_format/point_cloud_base_presentation/Point.h"
#include "NodeCoordinate.h"
#include <memory>
#include <unordered_set>

namespace vistart
{
	namespace orthogonal_linked_octree
	{
        template<class T, typename = typename std::enable_if<std::is_base_of<vistart::point_cloud_base_presentation::Point, T>::value, T>::type>
		class OctreeNode
        {
        public:
            OctreeNode() = default;
            /**
             *
             * @param point
             */
            OctreeNode(std::shared_ptr<T> point)
            {
                if (!point)
                    return;
                *this << point;
            }
            OctreeNode(unsigned int X, unsigned int Y, unsigned int Z, unsigned char depth, std::shared_ptr<T> point = nullptr)
            {
                NodeCoordinate c(X, Y, Z, depth);
                OctreeNode(c, point);
            }
            virtual ~OctreeNode() = default;

            OctreeNode<T>& operator<<(std::shared_ptr<T> point)
            {
                points.emplace(point);
                return *this;
            }

            friend std::ostream& operator<<(std::ostream& stream, OctreeNode const& node)
            {
                for (auto& p : node.GetPoints())
                {
                    stream << *p << std::endl;
                }
                return stream;
            }

            std::unordered_set<std::shared_ptr<T>>& GetPoints()
            {
                return points;
            }
        protected:
            std::unordered_set<std::shared_ptr<T>> points;

        };
	}
}
#endif
