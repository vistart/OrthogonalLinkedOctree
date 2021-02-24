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
#ifndef __LINKED_OCTREE_H__
#define __LINKED_OCTREE_H__
#include <type_traits>

#include "../../file_format/point_cloud_base_presentation/PointList.h"
#include "../orthogonal_linked_list/Coordinate.h"
#include "../orthogonal_linked_list/LinkedCoordinate.h"
#include "OctreeNode.h"
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <map>
#include <immintrin.h>
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif

namespace vistart
{
	namespace orthogonal_linked_octree
	{
		template<class TPointList,
				 class TPoint,
				 typename = typename std::enable_if<std::is_base_of<point_cloud_base_presentation::PointList<TPoint>, TPointList>::value, TPointList>::type>
		class LinkedOctree : public orthogonal_linked_list::LinkedCoordinate<3, OctreeNode<TPoint>>
		{
		public:
		    LinkedOctree() = default;
			explicit LinkedOctree(std::shared_ptr<TPointList> const& point_list, unsigned char depth = 12)
            {
                if (depth < 1 || depth > 127) {
#ifdef _MSC_VER
                    throw std::exception("The depth out of range. It should be an integer from 1 to 127.");
#endif
#ifdef __GNUC__
                    throw std::runtime_error("The depth out of range. It should be an integer from 1 to 127.");
#endif
                }
                // Specify the parameter `depth`. This parameter is recognized as the depth of octree.
                this->depth = depth;

                // Find the the boundaries throughout the three dimensions.

                std::cout << "The boundaries of three dimensions are following:" << std::endl;
                boundaries = find_boundary(point_list);
                std::cout << std::endl;

                // Find the middle point of each dimension.

                const auto middle_point = find_middle_point(boundaries);
                max_range = find_max_range(boundaries);

                leaf_width = max_range / ((base_depth << depth) - 1);
#pragma region Output Range
#ifdef _DEBUG
                std::cout << "Leaf node width: " << leaf_width << std::endl;
                std::cout << "Max extended range (= Max range + Leaf node width): " << std::setprecision(8) << max_range + leaf_width << std::endl;
                auto [x_mid, y_mid, z_mid] = middle_point;
                std::cout << "X-axis extended range: " << std::setprecision(8) << x_mid - (max_range + leaf_width) / 2 << " to " << std::setprecision(8) << x_mid + (max_range + leaf_width) / 2 << std::endl;
                std::cout << "Y-axis extended range: " << std::setprecision(8) << y_mid - (max_range + leaf_width) / 2 << " to " << std::setprecision(8) << y_mid + (max_range + leaf_width) / 2 << std::endl;
                std::cout << "Z-axis extended range: " << std::setprecision(8) << z_mid - (max_range + leaf_width) / 2 << " to " << std::setprecision(8) << z_mid + (max_range + leaf_width) / 2 << std::endl;
#endif
#pragma endregion

                auto points = point_list->GetPoints();
#pragma region Insert Point into Octree
                std::cout << "Inserting all points into Octree:" << std::endl;
                for (auto i = 0; i < points->size(); i++) {
                    auto& point = (*points)[i];
                    const auto& node_coordinate = find_node_coordinate(point, middle_point, max_range, depth, leaf_width);
                    auto result = this->insert_point(node_coordinate, point);
                    //auto result = insert_point(node_coordinate, point);
                    if (!result)
                    {
                        std::cout << "(" << node_coordinate[0] << ", " << node_coordinate[1] << ", " << node_coordinate[2]  << ")" << ":" << std::endl;
                    }
                    if (i % 10000 == 9999)
                    {
                        std::cout << i + 1 << " points are inserted." << std::endl;
                    }
                }
                std::cout << "All(" << points->size() << ") points are inserted." << std::endl;
#pragma endregion
#ifdef _DEBUG

                print_nodes_stats();

                auto& first_point = (*points)[0];
                std::cout << *first_point << std::endl;
                first_point->offset(leaf_width / 3, 0, 0);
                std::cout << *first_point << std::endl;
#endif
            }
            ~LinkedOctree() = default;
            /*
             * Point coordinate.
             * Each point coordinate contains X, Y and Z.
             */
            typedef std::tuple<double, double, double> PointCoordinate;
            typedef std::vector<unsigned int> NodeCoordinate;

            virtual bool insert_point(NodeCoordinate const& c, std::shared_ptr<TPoint> point)
            {
                if (!orthogonal_linked_list::Coordinate<3, OctreeNode<TPoint>>::exists(c))
                {
                    this->set(c, std::make_shared<OctreeNode<TPoint>>());
                }
                const auto& node = this->get(c);
                *node << point;
                return true;
            }
            virtual size_t GetAllSizes()
            {
                size_t result = 0;
#ifdef __AVX2__
                __m256i a = _mm256_set1_epi32(0);
                auto it = this->pointers.begin();
            	for (auto i = 0; i < this->pointers.size() - 8; i+=8)
            	{
                    const auto s0 = (it++)->second->size();
                    const auto s1 = (it++)->second->size();
                    const auto s2 = (it++)->second->size();
                    const auto s3 = (it++)->second->size();
                    const auto s4 = (it++)->second->size();
                    const auto s5 = (it++)->second->size();
                    const auto s6 = (it++)->second->size();
                    const auto s7 = (it++)->second->size();
                    __m256i b = _mm256_set_epi32(s7, s6, s5, s4, s3, s2, s1, s0);
                    a = _mm256_add_epi32(a, b);
            	}
                int acc[8];
            	_mm256_store_si256((__m256i*)acc, a);
                result = acc[0] + acc[1] + acc[2] + acc[3] + acc[4] + acc[5] + acc[6] + acc[7];
                for (auto i = this->pointers.size() - 8; i < this->pointers.size(); i++) result += (it++)->second->size();
#endif
                return result;
            }
        protected:
            unsigned char depth = 12; // The depth range is limited to between 1 and 127.
            /**
             * x:[lower, higher]
             * y:[lower, higher]
             * z:[lower, higher]
             */
            std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> boundaries;
            double max_range = 1;
            /**
             * Define the base of leaf node width.
             *
             * The calculation method of the depth base is 2 to the power of `depth`.
             * For example:
             *
             * When the depth is 12, base_depth is 2 to the 12th power, which is 4096.
             */
            unsigned long long const base_depth = 1;
            double leaf_width = 1;
            void print_nodes_stats()
            {
                std::cout << "Octree Stats:" << std::endl;
                size_t count = 0;
                std::map<size_t, unsigned int> count_per_node;
                for (auto &p : this->pointers)
                {
                    auto size = p.second->GetPoints().size();
                    count += size;
                    auto [iterator, success] = count_per_node.try_emplace(p.second->GetPoints().size(), 1);
                    if (!success) {
                        ++iterator->second;
                    }
                }
                std::cout << "Nodes: " << this->pointers.size() << ", Depth: " << (int)depth << ", Average Density: " << (float)count / this->pointers.size() << std::endl;

                std::cout << "Number of nodes containing # point(s):" << std::endl;
                for (auto& c : count_per_node)
                {
                    std::cout << "Count (" << c.first << "): " << c.second << std::endl;
                }
                std::cout << std::endl;
            }

            /**
             * Find the boundary of the point cloud.
             *
             * @param point_list The list that contains all the points.
             * @return The min & max coordinate of three dimensions.
             */
            static std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> find_boundary(std::shared_ptr<TPointList> const& point_list)
            {
                /**
                 * The return value of `GetPoints()` method is a shared pointer pointed to a point.
                 * That is, if you want to use the built-in methods that return pointers such as
                 * `min_element`/`max_element`, you should add a dereference symbol `*`
                 * when accessing a specific point.
                 *
                 * The following lines are examples.
                 */
                const auto comp_x = [](std::shared_ptr<TPoint> const& a, std::shared_ptr<TPoint> const& b) {return a->is_less_than(*b, TPoint::Coordination::X); };
                const auto comp_y = [](std::shared_ptr<TPoint> const& a, std::shared_ptr<TPoint> const& b) {return a->is_less_than(*b, TPoint::Coordination::Y); };
                const auto comp_z = [](std::shared_ptr<TPoint> const& a, std::shared_ptr<TPoint> const& b) {return a->is_less_than(*b, TPoint::Coordination::Z); };
                const auto begin = point_list->GetPoints()->begin();
                const auto end = point_list->GetPoints()->end();
                const auto x_min = min_element(begin, end, comp_x);
                const auto x_max = max_element(begin, end, comp_x);
                const auto y_min = min_element(begin, end, comp_y);
                const auto y_max = max_element(begin, end, comp_y);
                const auto z_min = min_element(begin, end, comp_z);
                const auto z_max = max_element(begin, end, comp_z);
#ifdef _DEBUG
                std::cout << std::fixed;
                std::cout << "X-axis:" << "[" << std::setw(8) << std::setprecision(8) << std::distance(begin, x_min) << "]" << std::setw(11) << (**x_min).X() << " to "
                          << std::setw(0) << "[" << std::setw(8) << std::distance(begin, x_max) << "]" << std::setw(11) << (**x_max).X() << std::endl;
                std::cout << "Y-axis:" << "[" << std::setw(8) << std::setprecision(8) << std::distance(begin, y_min) << "]" << std::setw(11) << (**y_min).Y() << " to "
                          << std::setw(0) << "[" << std::setw(8) << std::distance(begin, y_max) << "]" << std::setw(11) << (**y_max).Y() << std::endl;
                std::cout << "Z-axis:" << "[" << std::setw(8) << std::setprecision(8) << std::distance(begin, z_min) << "]" << std::setw(11) << (**z_min).Z() << " to "
                          << std::setw(0) << "[" << std::setw(8) << std::distance(begin, z_max) << "]" << std::setw(11) << (**z_max).Z() << std::endl;
#endif
#ifdef _DEBUG
                const auto x_range = (**x_max).X() - (**x_min).X();
                const auto y_range = (**y_max).Y() - (**y_min).Y();
                const auto z_range = (**z_max).Z() - (**z_min).Z();
                const auto x_mid = ((**x_max).X() + (**x_min).X()) / 2;
                const auto y_mid = ((**y_max).Y() + (**y_min).Y()) / 2;
                const auto z_mid = ((**z_max).Z() + (**z_min).Z()) / 2;
                std::cout << "X-axis range: " << std::setprecision(8) << x_range << " middle point: " << x_mid << std::endl;
                std::cout << "Y-axis range: " << std::setprecision(8) << y_range << " middle point: " << y_mid << std::endl;
                std::cout << "Z-axis range: " << std::setprecision(8) << z_range << " middle point: " << z_mid << std::endl;
#endif
#ifdef _DEBUG
                const auto max_range = std::max(x_range, std::max(y_range, z_range));
                std::cout << "Max range: " << std::setprecision(8) << max_range << std::endl;
#endif
                return std::make_tuple(std::make_tuple((**x_min).X(), (**x_max).X()), std::make_tuple((**y_min).Y(), (**y_max).Y()), std::make_tuple((**z_min).Z(), (**z_max).Z()));
            }

            /**
             * Find the value of the largest spanned dimension.
             *
             * @param b which contains three candidate dimensions.
             * @return double The upper and lower limits of the largest dimension of the range.
             */
            [[nodiscard]] double find_max_range(std::tuple<std::tuple<double, double>, std::tuple<double, double>, std::tuple<double, double>> const& b) const
            {
                const auto& [x_range, y_range, z_range] = b;
                const auto [x_range_min, x_range_max] = x_range;
                const auto [y_range_min, y_range_max] = y_range;
                const auto [z_range_min, z_range_max] = z_range;
                return std::max(x_range_max - x_range_min, std::max(y_range_max - y_range_min, z_range_max - z_range_min));
            }

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
            static NodeCoordinate const find_node_coordinate(std::shared_ptr<TPoint> const& point, PointCoordinate const& middle_point, double const& max_range, unsigned char const& depth, double const& leaf_width)
            {
                const auto& [x_mid, y_mid, z_mid] = middle_point;
                const auto half_leaf_width_with_max_range = (max_range + leaf_width) / 2;
                const auto& [offset_of_x, offset_of_y, offset_of_z] = point->offset_of(x_mid - half_leaf_width_with_max_range, y_mid - half_leaf_width_with_max_range, z_mid - half_leaf_width_with_max_range);
                const auto x_th = static_cast<unsigned int>(offset_of_x / leaf_width);
                const auto y_th = static_cast<unsigned int>(offset_of_y / leaf_width);
                const auto z_th = static_cast<unsigned int>(offset_of_z / leaf_width);
                return {x_th, y_th, z_th};
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
                return find_middle_point(x_range_min, x_range_max, y_range_min, y_range_max, z_range_min, z_range_max);
            }
		};
	}
}
#endif
