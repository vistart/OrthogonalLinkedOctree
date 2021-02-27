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
#include <immintrin.h>
#include <cstdlib>
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
            virtual size_t GetAllSizes()
            {
                size_t result = 0;
                auto it = this->pointers.begin();
                // 此处手动编写了使用 AVX 指令集的代码。
                // 在较新的编译器，如GCC 9.3.0，开启 -O3 级别优化时，会自动将简单累加计算改为使用 AVX 指令，因此使用 AVX 指令与直接累加耗时差异不大。
#ifdef __AVX512F__
                __m512i a = _mm512_set1_epi32(0);
            	for (auto i = 0; i < this->pointers.size() - 16; i += 16)
            	{
                    const auto s0 = (it++)->second->size();
                    const auto s1 = (it++)->second->size();
                    const auto s2 = (it++)->second->size();
                    const auto s3 = (it++)->second->size();
                    const auto s4 = (it++)->second->size();
                    const auto s5 = (it++)->second->size();
                    const auto s6 = (it++)->second->size();
                    const auto s7 = (it++)->second->size();
                    const auto s8 = (it++)->second->size();
                    const auto s9 = (it++)->second->size();
                    const auto s10 = (it++)->second->size();
                    const auto s11 = (it++)->second->size();
                    const auto s12 = (it++)->second->size();
                    const auto s13 = (it++)->second->size();
                    const auto s14 = (it++)->second->size();
                    const auto s15 = (it++)->second->size();
                    __m512i b = _mm512_set_epi32(s15, s14, s13, s12, s11, s10, s9, s8, s7, s6, s5, s4, s3, s2, s1, s0);
                    a = _mm512_add_epi32(a, b);
            	}
            	// 不能在 Debug 模式下直接使用 int[16]，因为此时变量并非“64-字节”内存对齐。
                int *acc = static_cast<int*>(std::aligned_alloc(sizeof(int) * 16, sizeof(int) * 16));
                _mm512_store_epi32(acc, a);
                for (int i = 0; i < 16; i++) result += acc[i];
                free(acc);
                while (it != this->pointers.end()) result += (it++)->second->size();
#elif __AVX2__
                __m256i a = _mm256_set1_epi32(0);
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
                __m256i mask = _mm256_set1_epi32(0xffffffff);
                _mm256_maskstore_epi32(acc, mask, a);
                result = acc[0] + acc[1] + acc[2] + acc[3] + acc[4] + acc[5] + acc[6] + acc[7];
                while (it != this->pointers.end()) result += (it++)->second->size();
#else
                while (it != this->pointers.end()) result += (it++)->second->size();
#endif
                return result;
            }
            virtual size_t GetSizeOf(typename orthogonal_linked_list::LinkedCoordinate<3, orthogonal_linked_octree::OctreeNode<TPoint>>::base_coord_col const& c) {
                if (!orthogonal_linked_list::LinkedCoordinate<3, orthogonal_linked_octree::OctreeNode<TPoint>>::exists(c)) return 0;
                return this->get(c)->size();
            }
            virtual double GetReciprocalOfSize(typename orthogonal_linked_list::LinkedCoordinate<3, orthogonal_linked_octree::OctreeNode<TPoint>>::base_coord_col const& c) {
                const auto r = this->GetSizeOf(c);
                if (r == 0) return NAN;
                return 1 / static_cast<double>(r);
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
