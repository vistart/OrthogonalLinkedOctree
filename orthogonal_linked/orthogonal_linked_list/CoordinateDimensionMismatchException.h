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
#ifndef __COORDINATE_DIMENSION_MISMATCH_EXCEPTION__
#define __COORDINATE_DIMENSION_MISMATCH_EXCEPTION__
#include <stdexcept>
#include <pybind11/pybind11.h>

/**
 * 坐标维度不匹配异常。当参数维度与目标维度不匹配时应当抛出此异常。
 */
namespace vistart
{
	namespace orthogonal_linked_list
	{
		class CoordinateDimensionMismatchException : public std::length_error
		{
		public:
			/**
			 *
			 *
			 * @param Dc
			 * @param Dt
			 */
			CoordinateDimensionMismatchException(unsigned char Dc, unsigned char Dt) : length_error("The coordinate dimension does not match the target dimension.")
			{
				this->dc = Dc;
				this->dt = Dt;
			}

			/**
			 * @return get Dimension of Coordinate passed-in.
			 */
			unsigned char getDc() const
			{
				return this->dc;
			}

			/**
			 * @return get Dimension of target.
			 */
			unsigned char getDt() const
			{
				return this->dt;
			}
		protected:
			unsigned char dc;
			unsigned char dt;
		};
	}
}
#endif
