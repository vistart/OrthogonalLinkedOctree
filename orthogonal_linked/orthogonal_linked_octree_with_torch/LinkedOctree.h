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

#include "../orthogonal_linked_list/Coordinate.h"
#include "../orthogonal_linked_list/LinkedCoordinate.h"
#include "../orthogonal_linked_octree/OctreeNode.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
#include <torch/torch.h>
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif

namespace vistart
{
	namespace orthogonal_linked_octree_with_torch
	{
		template<class TPoint,
				 typename = typename std::enable_if<std::is_base_of<point_cloud_base_presentation::Point, TPoint>::value, TPoint>::type>
		class LinkedOctree : public orthogonal_linked_list::LinkedCoordinate<3, orthogonal_linked_octree::OctreeNode<TPoint>>
		{
		public:
		    LinkedOctree() = default;
			explicit LinkedOctree(at::Tensor const& coords, unsigned char depth = 12)
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
                //123456std::cout << coords << std::endl;
                //std::cout << (coords + 1) / 2 << std::endl;
                const auto& coords_clamped = torch::clamp((coords + 1) * pow(2, depth - 1), 0, pow(2, depth) - 1);
                const auto& coords_rounded = torch::round(coords_clamped);
                //std::cout << (coords + 1) * pow(2, depth - 1) << std::endl;
                //std::cout << coords_rounded << std::endl;
                for (int i = 0; i < coords.size(0); i++)
                {
                    insert_point(coords_rounded[i], coords[i]);
                    //std::cout << coords_rounded[i] << std::endl << coords[i] << std::endl;
                    const auto& t = this->get({
                        static_cast<unsigned int>(coords_rounded[i][0].item().toInt()),
                    	static_cast<unsigned int>(coords_rounded[i][1].item().toInt()),
                    	static_cast<unsigned int>(coords_rounded[i][2].item().toInt())});
                    const std::unordered_set<std::shared_ptr<TPoint>>& p0 = t->GetPoints();
                    //const auto pointer = p0.begin();
                    //std::cout << **pointer << std::endl;
                }
            }
            virtual ~LinkedOctree() = default;
            /*
             * Point coordinate.
             * Each point coordinate contains X, Y and Z.
             */
            typedef std::tuple<double, double, double> PointCoordinate;
            typedef std::vector<unsigned int> NodeCoordinate;
            virtual bool insert_point(at::Tensor const& c, at::Tensor const& p)
            {
                assert(c.size(0) == 3);
                assert(p.size(0) == 3);
                return insert_point({
                    static_cast<unsigned int>(c[0].item().toShort()),
                    static_cast<unsigned int>(c[1].item().toShort()),
                    static_cast<unsigned int>(c[2].item().toShort()),
                    }, {
                        static_cast<double>(p[0].item().toDouble()),
                        static_cast<double>(p[1].item().toDouble()),
                        static_cast<double>(p[2].item().toDouble()),
                });
            }
            virtual bool insert_point(std::initializer_list<unsigned int> c, std::initializer_list<double> p)
            {
                assert(c.size() == 3);
                assert(p.size() == 3);
                NodeCoordinate const& c1(c);
                const auto& p1 = std::make_shared<TPoint>(p);
                return insert_point(c1, p1);
            }
            virtual bool insert_point(NodeCoordinate const& c, std::shared_ptr<TPoint> point)
            {
                if (!orthogonal_linked_list::Coordinate<3, orthogonal_linked_octree::OctreeNode<TPoint>>::exists(c))
                {
                    this->set(c, std::make_shared<orthogonal_linked_octree::OctreeNode<TPoint>>());
                }
                const auto& node = this->get(c);
                *node << point;
                return true;
            }
        protected:
            unsigned char depth = 12; // The depth range is limited to between 1 and 127.
            void print_nodes_stats()
            {
            }
		};
	}
}
#endif
