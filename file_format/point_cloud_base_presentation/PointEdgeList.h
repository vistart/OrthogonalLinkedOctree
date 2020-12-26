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

#ifndef __POINT_EDGE_LIST__
#define __POINT_EDGE_LIST__
#include "PointEdge.h"
#include <memory>
#include <type_traits>
#include <vector>
namespace vistart
{
	namespace point_cloud_base_presentation
	{
		template <typename T, typename = typename std::enable_if<std::is_base_of<PointEdge, T>::value, T>::type>
		class PointEdgeList
		{
		public:
			PointEdgeList()
			{
				this->edges = std::make_shared<std::vector<std::shared_ptr<T>>>();
			}
			PointEdgeList(const PointEdgeList&) = delete;
			PointEdgeList& operator=(const PointEdgeList&) = delete;
			PointEdgeList(PointEdgeList&&) = default;
			PointEdgeList& operator=(PointEdgeList&&) = default;
			virtual ~PointEdgeList()
			{
				this->edges = nullptr;
			};
			[[nodiscard]] virtual std::shared_ptr<std::vector<std::shared_ptr<T>>> GetEdges() const
			{
				return this->edges;
			}
		protected:
			std::shared_ptr<std::vector<std::shared_ptr<T>>> edges;
		};
	}
}
#endif
