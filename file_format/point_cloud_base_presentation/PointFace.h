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
#ifndef __POINT_FACE__
#define __POINT_FACE__

#include <memory>
#include <vector>
#include <queue>
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif
namespace vistart
{
	namespace point_cloud_base_presentation
	{
		class PointFace
		{
		public:
			PointFace();
			PointFace(const PointFace&) = default;
			PointFace& operator=(const PointFace&) = default;
			PointFace(PointFace&&) = default;
			PointFace& operator=(PointFace&&) = default;
			virtual ~PointFace();
			virtual bool operator==(PointFace const& face) const;
			virtual bool operator!=(PointFace const& face) const;
		protected:
			std::shared_ptr<std::priority_queue<unsigned int, std::vector<unsigned int>, std::greater<>>> vertex_indices;
		};
	}
}
#endif
