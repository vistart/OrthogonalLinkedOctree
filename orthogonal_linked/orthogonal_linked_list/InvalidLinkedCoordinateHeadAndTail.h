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
#ifndef __INVALID_LINKED_COORDINATE_HEAD_AND_TAIL__
#define __INVALID_LINKED_COORDINATE_HEAD_AND_TAIL__
#include <stdexcept>
#include <pybind11/pybind11.h>

#include "Coordinate.h"

namespace vistart
{
	namespace orthogonal_linked_list
	{
		/**
		 * 头尾指针不匹配异常。
		 * 头尾指针要么不存在，要么同为 nullptr 或同不为 nullptr。否则为异常状态。
		 */
		class InvalidLinkedCoordinateHeadAndTail : public std::range_error
		{
		public:
			/**
			 *
			 */
			InvalidLinkedCoordinateHeadAndTail() : range_error("The head pointer and tail pointer do not match.") {}
		};
	}
}
#endif
