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
             * Initialize OctreeNode with a point.
             * @param point the pointer to the initial point.
             */
            OctreeNode(std::shared_ptr<T> point)
            {
                if (!point)
                    return;
                *this << point;
            }
            /**
             * Initialize OctreeNode with coordinate and depth and a point.
             * You should ensure the point be fallen into the current node yourself.
             * @param X
             * @param Y
             * @param Z
             * @param depth
             * @param point
             */
            OctreeNode(unsigned int X, unsigned int Y, unsigned int Z, unsigned char depth, std::shared_ptr<T> point = nullptr)
            {
                NodeCoordinate c(X, Y, Z, depth);
                OctreeNode(c, point);
            }
            /**
             * Initialize OctreeNode with a set of points.
             * @param points
             */
            OctreeNode(std::unordered_set<std::shared_ptr<T>> const& points)
            {
                this->points = points;
            }
            virtual ~OctreeNode() = default;

            /**
             * Insert a point.
             * @param point
             * @return
             */
            OctreeNode<T>& operator<<(std::shared_ptr<T> point)
            {
                points.emplace(point);
                return *this;
            }

            /**
             * Output all the points contained in a OctreeNode.
             * @param stream
             * @param node
             * @return
             */
            friend std::ostream& operator<<(std::ostream& stream, OctreeNode const& node)
            {
                for (auto& p : node.GetPoints())
                {
                    stream << *p << std::endl;
                }
                return stream;
            }

            /**
             * Return all the points.
             * Note: If you want to get the size of this node, please access [[size()]] method instead.
             * @return points.
             */
            std::unordered_set<std::shared_ptr<T>>& GetPoints()
            {
                return points;
            }

            /**
             * Return the size of this node.
             * @return size.
             */
            auto size() const noexcept
            {
                return points.size();
            }
        protected:
            /**
             * the unordered set contained all the points.
             * You shouldn't access this property directly, unless you know the consequences of doing so.
             */
            std::unordered_set<std::shared_ptr<T>> points;
        };
	}
}
#endif
