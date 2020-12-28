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
            /*
             * Point coordinate.
             * Each point coordinate contains X, Y and Z.
             */
            typedef std::tuple<double, double, double> PointCoordinate;
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
            ~OctreeNode() = default;

            /**
             * Calculate the coordinates of the node where a certain point is located.
             *
             * This method uses the point in space and the common maximum range of the three dimensions to determine the spatial range.
             * Before using this method, you can use `find_middle_point()` to calculate the midpoint of the space, and then pass it in as a parameter.
             *
             * Then, you need to specify the depth of the node in the octree. This parameter determines the node coordinate value.
             *
             * @param point The target point.
             * @param middle_point The midpoint of the space.
             * @param max_range Common maximum range of the three dimensions.
             * @param depth The depth of the node in the octree. The default depth is 8.
             * @param leaf_width
             *
             * @return The coordinates of the node where the current point is located.
             */
            static NodeCoordinate find_node_coordinate(std::shared_ptr<T> const& point, PointCoordinate const& middle_point, double const& max_range, unsigned char const& depth, double const& leaf_width)
            {
                const auto& [x_mid, y_mid, z_mid] = middle_point;
                const auto half_leaf_width_with_max_range = (max_range + leaf_width) / 2;
                const auto& [offset_of_x, offset_of_y, offset_of_z] = point->offset_of(x_mid - half_leaf_width_with_max_range, y_mid - half_leaf_width_with_max_range, z_mid - half_leaf_width_with_max_range);
                //const auto offset_of_x = point->offset_of(x_mid - (max_range + leaf_width) / 2, Point::Coordination::X);
                //const auto offset_of_y = point->offset_of(y_mid - (max_range + leaf_width) / 2, Point::Coordination::Y);
                //const auto offset_of_z = point->offset_of(z_mid - (max_range + leaf_width) / 2, Point::Coordination::Z);
                const auto x_th = static_cast<unsigned int>(offset_of_x / leaf_width);
                const auto y_th = static_cast<unsigned int>(offset_of_y / leaf_width);
                const auto z_th = static_cast<unsigned int>(offset_of_z / leaf_width);
                return NodeCoordinate (x_th, y_th, z_th, depth);
            }

            /**
             * Calculate the coordinates of the midpoint in the specified space.
             *
             * @param x_range_min
             * @param x_range_max
             * @param y_range_min
             * @param y_range_max
             * @param z_range_min
             * @param z_range_max
             * @return the point coordinate of midpoint.
             */
            static PointCoordinate find_middle_point(double x_range_min, double x_range_max, double y_range_min, double y_range_max, double z_range_min, double z_range_max)
            {
                return std::make_tuple((x_range_max + x_range_min) / 2, (y_range_max + y_range_min) / 2, (z_range_max + z_range_min) / 2);
            }
            /**
             * Calculate the coordinates of the midpoint in the specified space.
             *
             * @param boundaries The boundary of the space to be calculated.
             * @return the point coordinate of midpoint.
             */
            static PointCoordinate find_middle_point(std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> const& boundaries)
            {
                const auto& [x_range, y_range, z_range] = boundaries;
                auto [x_range_min, x_range_max] = x_range;
                auto [y_range_min, y_range_max] = y_range;
                auto [z_range_min, z_range_max] = z_range;
                return OctreeNode::find_middle_point(x_range_min, x_range_max, y_range_min, y_range_max, z_range_min, z_range_max);
            }

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
