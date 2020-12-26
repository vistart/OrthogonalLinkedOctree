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
#ifndef __POINT_EDGE__
#define __POINT_EDGE__
#include <iomanip>
#include <memory>
namespace vistart
{
	namespace point_cloud_base_presentation
	{
        class PointEdge
        {
        public:
            PointEdge() = default;
            virtual ~PointEdge() = default;
            int vertex1 = 0;
            int vertex2 = 0;
            struct RGB
            {
                double R;
                double G;
                double B;
            };
            [[nodiscard]] unsigned char R() const
            {
                return __R;
            }
            virtual PointEdge& R(unsigned char const R) {
                __R = R;
                return *this;
            }
            [[nodiscard]] unsigned char G() const
            {
                return __G;
            }
            virtual PointEdge& G(unsigned char const G) {
                __G = G;
                return *this;
            }
            [[nodiscard]] unsigned char B() const
            {
                return __B;
            }
            virtual PointEdge& B(unsigned char const B) {
                __B = B;
                return *this;
            }
            friend std::ostream& operator<<(std::ostream& stream, PointEdge const& edge)
            {
                stream << "(" << std::setprecision(10) << edge.vertex1 << "," << std::setprecision(10) << edge.vertex2 << ")";
                return stream;
            }
        protected:
            unsigned char __R = 0;
            unsigned char __G = 0;
            unsigned char __B = 0;
            void set_all_properties(int v1, int v2, unsigned char const R, unsigned char const G, unsigned char const B)
            {
                vertex1 = v1;
                vertex2 = v2;
                this->__R = R;
                this->__G = G;
                this->__B = B;
            }
        };
	}
}
#endif
