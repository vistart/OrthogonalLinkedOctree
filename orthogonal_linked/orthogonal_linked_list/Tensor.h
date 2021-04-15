/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __ORTHOGONAL_LINKED_LIST_TENSOR_H__
#define __ORTHOGONAL_LINKED_LIST_TENSOR_H__
#include <memory>
#include "Coordinate.h"
#include "CoordinateDimensionMismatchException.h"

namespace vistart
{
    namespace orthogonal_linked_list
    {
        template<unsigned char D, typename T>
        class Tensor {
        public:
            Tensor() = delete;
            Tensor(typename Coordinate<D, T>::coordinates_type const& lower, typename Coordinate<D, T>::coordinates_type const& upper, std::shared_ptr<T> null_position_value = nullptr)
            {
                this->lower = lower;
                this->upper = upper;
                if (!check_lower_upper_bound(lower, upper))
                {
                    throw CoordinateDimensionMismatchException(
                            static_cast<unsigned char>(lower.size()),
                            static_cast<unsigned char>(upper.size())
                            );
                }
                this->null_position_value = null_position_value;
            }
            virtual ~Tensor() = default;
        protected:
            typename Coordinate<D, T>::coordinates_type const lower;
            typename Coordinate<D, T>::coordinates_type const upper;
            std::shared_ptr<T> null_position_value = nullptr;
        private:
            static bool check_lower_upper_bound(typename Coordinate<D, T>::coordinates_type const& lower, typename Coordinate<D, T>::coordinates_type const& upper)
            {
                if (!Coordinate<D, T>::check_coordinates_dimension_size(lower) || !Coordinate<D, T>::check_coordinates_dimension_size(upper))
                    return false;
                for (int i = 0; i < lower.size(); i++)
                    if (lower[i] > upper[i])
                        return false;
                return true;
            }
        };
    }
}

#endif //__ORTHOGONAL_LINKED_LIST_TENSOR_H__
