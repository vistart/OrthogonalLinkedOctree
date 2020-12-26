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

#ifndef __POINT_LIST_H__
#define __POINT_LIST_H__
#include "Point.h"
#include <memory>
#include <type_traits>
#include <vector>

/*
 This class is used to describe point list that holds all points.
 All points are saved to a vector container and there is a shared pointer to it.
 The class that describes a point can be the Point class or its inherited class,
 otherwise, the compilation fails.

 If you think that this class definition cannot meet your needs, you can inherit
 the current class and implement it yourself according to your needs.

 If you need to implement inherited classes, be sure to follow the following specifications:
 1. Define the vector container that holds all points and make shared pointer point to it.
 2. Initialize the shared pointer of above points property in Constructor.
 3. Make the points to nullptr in Destructor.
*/
namespace vistart
{
	namespace point_cloud_base_presentation
	{
        template <typename T, typename = typename std::enable_if<std::is_base_of<Point, T>::value, T>::type>
        class PointList
        {
        public:
            PointList() {
                points = std::make_shared<std::vector<std::shared_ptr<T>>>();
            }
            PointList(const PointList& other)
            {
                points = other.points;
            }
            PointList& operator=(const PointList& other)
            {
                if (this == &other) return *this;
                if (points != nullptr) points == nullptr;
                points = other.points;
                return *this;
            }
            PointList(PointList&& other) noexcept
            {
                points = other.points;
                other.points = nullptr;
            }
            PointList& operator=(PointList&& other) noexcept
            {
                if (this == &other) return *this;
                if (points != nullptr) points = nullptr;
                points = other.points;
                other.points = nullptr;
                return *this;
            }
            virtual ~PointList() {
                this->points = nullptr;
            }
            [[nodiscard]] virtual std::shared_ptr<std::vector<std::shared_ptr<T>>> GetPoints() const {
                return this->points;
            }
        protected:
            std::shared_ptr<std::vector<std::shared_ptr<T>>> points;
        };
	}
}
#endif
