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
#ifndef __POINT_H__
#define __POINT_H__

#include <iomanip>
#include <assert.h>
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif

constexpr auto coord_no_out_of_range_message = "The coordination system code is out of range.";

/*
 This class is used to describe a point (or a vertex in discrete mathematics).
 The currently supported attributes are:
 - 3D Coordinates (X, Y, Z) (Required, double for each)
 - Color (R, G, B) (Optional, unsigned char for each)
 - Normal Vector (NX, NY, NZ) (Optional, double for each)
 - Transparency (ALPHA) (Optional, unsigned char)
 - Confidence (CONFIDENCE) (Optional, positive double-precision number or zero)
 - Intensity (INTENSITY) (Optional, positive double-precision number or zero)

 If you think that this class definition cannot meet your needs, you can inherit
 the current class and implement it yourself according to your needs.

 TODO:
 - Enable to allocate memory for coordinates, colors, normal vector, transparency,
   confidence, and intensity as needed, that is, if not needed, it is not allocated.
*/
namespace vistart
{
	namespace point_cloud_base_presentation
	{
        class Point
        {
        public:
            Point() = default;
            Point(const Point&) = default;
            Point(std::initializer_list<double> const& c)
            {
                assert(c.size() == 3);
                auto p = c.begin();
                __X = *p++;
                __Y = *p++;
                __Z = *p;
            }
            Point(std::initializer_list<double> const& c, std::initializer_list<unsigned char> const& c1)
            {
                assert(c.size() == 3);
                assert(c1.size() == 3);
                auto p = c.begin();
                __X = *p++;
                __Y = *p++;
                __Z = *p;
                auto p1 = c1.begin();
                __R = *p1++;
                __G = *p1++;
                __B = *p1;
                has_RGB = true;
            }
            Point(double X, double Y, double Z) : __X(X), __Y(Y), __Z(Z){}
            Point(double X, double Y, double Z, unsigned char R, unsigned char G, unsigned char B) : __X(X), __Y(Y), __Z(Z), __R(R), __G(G), __B(B), has_RGB(true) {}
            Point& operator=(const Point&) = default;
            Point(Point&&) = default;
            Point& operator=(Point&&) = default;
            virtual ~Point() = default;
            struct XYZ
            {
                double X;
                double Y;
                double Z;
            };
            struct RGB
            {
                double R;
                double G;
                double B;
            };
            struct NXYZ
            {
                double NX;
                double NY;
                double NZ;
            };
            [[nodiscard]] double X() const noexcept
            {
                return __X;
            }
            virtual Point& X(double const X) noexcept {
                __X = X;
                return *this;
            }
            [[nodiscard]] double Y() const noexcept
            {
                return __Y;
            }
            virtual Point& Y(double const Y) noexcept {
                __Y = Y;
                return *this;
            }
            [[nodiscard]] double Z() const noexcept
            {
                return __Z;
            }
            virtual Point& Z(double const Z) noexcept {
                __Z = Z;
                return *this;
            }
            [[nodiscard]] unsigned char R() const
            {
                return __R;
            }
            virtual Point& R(unsigned char const R) {
                __R = R;
                return *this;
            }
            [[nodiscard]] unsigned char G() const
            {
                return __G;
            }
            virtual Point& G(unsigned char const G) {
                __G = G;
                return *this;
            }
            [[nodiscard]] unsigned char B() const
            {
                return __B;
            }
            virtual Point& B(unsigned char const B) {
                __B = B;
                return *this;
            }
            [[nodiscard]] double NX() const
            {
                return __NX;
            }
            virtual Point& NX(double const NX) {
                __NX = NX;
                return *this;
            }
            [[nodiscard]] double NY() const
            {
                return __NY;
            }
            virtual Point& NY(double const NY) {
                __NY = NY;
                return *this;
            }
            [[nodiscard]] double NZ() const
            {
                return __NZ;
            }
            virtual Point& NZ(double const NZ) {
                __NZ = NZ;
                return *this;
            }
            [[nodiscard]] unsigned char ALPHA() const
            {
                return __ALPHA;
            }
            virtual Point& ALPHA(unsigned char const ALPHA) {
                __ALPHA = ALPHA;
                return *this;
            }
            [[nodiscard]] double CONFIDENCE() const
            {
                return __CONFIDENCE;
            }
            virtual Point& CONFIDENCE(double const CONFIDENCE) {
                __CONFIDENCE = CONFIDENCE;
                return *this;
            }
            [[nodiscard]] double INTENSITY() const
            {
                return __INTENSITY;
            }
            virtual Point& INTENSITY(double const INTENSITY) {
                __INTENSITY = INTENSITY;
                return *this;
            }
            virtual bool operator==(Point const& vertex) const
            {
                bool result = (__X == vertex.X() && __Y == vertex.Y() && __Z == vertex.Z());
                /*
                if (has_RGB)
                {
                    result = (result && __R == vertex.R() && __G == vertex.G() && __B == vertex.B());
                }
                if (has_normal)
                {
                    result = (result && __NX == vertex.NX() && __NY == vertex.NY() && __NZ == vertex.NZ());
                }
                if (has_alpha)
                {
                    result = (result && __ALPHA == vertex.ALPHA());
                }
                if (has_confidence)
                {
                    result = (result && __CONFIDENCE == vertex.CONFIDENCE());
                }
                if (has_intensity)
                {
                    result = (result && __INTENSITY == vertex.INTENSITY());
                }
                */
                return result;
            }
            virtual bool operator!=(Point const& vertex) const
            {
                return !(*this == vertex);
            }
            virtual bool operator<(Point const& vertex) const
            {
                return __X < vertex.X() && __Y < vertex.Y() && __Z < vertex.Z();
            }
            virtual bool operator>(Point const& vertex) const
            {
                return __X > vertex.X() && __Y > vertex.Y() && __Z > vertex.Z();
            }
            enum class Coordination { X, Y, Z };

            /**
             * Determine whether a certain dimension coordinate is less than the target.
             *
             * For example:
             * ```
             * a.X = 1;
             * b.X = 2;
             * auto result = a.is_less_than(b, Coordination.X);
             * ```
             *
             * The result will be true.
             *
             * @param object the target to be compared.
             * @param coordination the specified dimension to be compared.
             * @return whether the current point is less than the target in specified dimension.
             * @exception thrown if Coordination is not in X, Y or Z.
             */
            [[nodiscard]] virtual bool is_less_than(Point const& object, Coordination const& coordination) const
            {
                switch (coordination) {
                case Coordination::X:
                    return this->__X < object.X();

                case Coordination::Y:
                    return this->__Y < object.Y();

                case Coordination::Z:
                    return this->__Z < object.Z();
                }
#ifdef _MSC_VER
                throw std::exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
                throw std::runtime_error(coord_no_out_of_range_message);
#endif
            }

            /**
             * Determine whether a certain dimension coordinate is equal to the target.
             *
             * For example:
             * ```
             * a.X = 1;
             * b.X = 1;
             * auto result = a.is_equal_to(b, Coordination.X);
             * ```
             *
             * The result will be true.
             *
             * @param object the target to be compared.
             * @param coordination the specified dimension to be compared.
             * @return whether the current point is equal to the target in specified dimension.
             * @exception thrown if Coordination is not in X, Y or Z.
             * @exception
             */
            [[nodiscard]] virtual bool is_equal_to(Point const& object, Coordination const& coordination) const
            {
                switch (coordination) {
                case Coordination::X:
                    return this->__X == object.X();

                case Coordination::Y:
                    return this->__Y == object.Y();

                case Coordination::Z:
                    return this->__Z == object.Z();
                }
#ifdef _MSC_VER
                throw std::exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
                throw std::runtime_error(coord_no_out_of_range_message);
#endif
            }

            /**
             * Determine whether a certain dimension coordinate is greater than the target.
             *
             * For example:
             * ```
             * a.X = 2;
             * b.X = 1;
             * auto result = a.is_greater_to(b, Coordination.X);
             * ```
             *
             * The result will be true.
             *
             * @param object the target to be compared.
             * @param coordination the specified dimension to be compared.
             * @return whether the current point is greater than the target in specified dimension.
             * @exception thrown if Coordination is not in X, Y or Z.
             */
            [[nodiscard]] virtual bool is_greater_than(Point const& object, Coordination const& coordination) const
            {
                switch (coordination) {
                case Coordination::X:
                    return this->__X > object.X();

                case Coordination::Y:
                    return this->__Y > object.Y();

                case Coordination::Z:
                    return this->__Z > object.Z();
                }
#ifdef _MSC_VER
                throw std::exception(coord_no_out_of_range_message);
#endif
#ifdef __GNUC__
                throw std::runtime_error(coord_no_out_of_range_message);
#endif
            }

            /**
             * Determine whether a certain dimension coordinate is equal to or less than the target.
             *
             * For example:
             * ```
             * a.X = 1;
             * b.X = 2;
             * auto result = a.is_equal_or_less_than(b, Coordination.X);
             * ```
             *
             * The result will be true.
             *
             * @param object the target to be compared.
             * @param coordination the specified dimension to be compared.
             * @return whether the current point is equal to or less than the target in specified dimension.
             * @exception thrown if Coordination is not in X, Y or Z.
             */
            [[nodiscard]] virtual bool is_equal_or_less_than(Point const& object, Coordination const& coordination) const
            {
                return this->is_less_than(object, coordination) || this->is_equal_to(object, coordination);
            }

            /**
             * Determine whether a certain dimension coordinate is equal to or greater than the target.
             *
             * For example:
             * ```
             * a.X = 2;
             * b.X = 1;
             * auto result = a.is_equal_or_greater_than(b, Coordination.X);
             * ```
             *
             * The result will be true.
             *
             * @param object the target to be compared.
             * @param coordination the specified dimension to be compared.
             * @return bool is equal to or greater than the target in specified dimension.
             * @exception thrown if Coordination is not in X, Y or Z.
             */
            [[nodiscard]] virtual bool is_equal_or_greater_than(Point const& object, Coordination const& coordination) const
            {
                return this->is_greater_than(object, coordination) || this->is_equal_to(object, coordination);
            }

            /* Determines whether the current point contains the RGB properties. */
            bool has_RGB = false;
            /* Determines whether the current point contains the normal properties. */
            bool has_normal = false;
            /* Determines whether the current point contains the alpha properties. */
            bool has_alpha = false;
            /* Determines whether the current point contains the confidence properties. */
            bool has_confidence = false;
            /* Determines whether the current point contains the intensity properties. */
            bool has_intensity = false;

            /**
             * Offset the current point by three values.
             *
             * @param offset_x offset value in X coordinate. It can be negative.
             * @param offset_y offset value in Y coordinate. It can be negative.
             * @param offset_z offset value in Z coordinate. It can be negative.
             */
            void offset(double offset_x, double offset_y, double offset_z);

            /**
             * Offset the current point by a three-dimensional value.
             *
             * @param target offset value in X,Y and Z.
             */
            void offset(XYZ const& target);

            /**
             * Offset the current point by another point.
             *
             * @param target offset value in X,Y and Z.
             */
            void offset(Point const& target);

            Point* operator+(Point const& target);
            Point* operator+(XYZ const& target);

            /**
             * Calculate the offset under a certain coordinate.
             *
             * @param offset target.
             * @param coordination specified dimension.
             * @return the offset between the current and the target in specified dimension.
             */
            [[nodiscard]] double offset_of(double offset, Coordination const& coordination) const;

            /**
             * Calculate the offset under a certain coordinate.
             *
             * @param offset target.
             * @return the offset between the current and the target in specified dimension.
             */
            [[nodiscard]] std::tuple<double, double, double> offset_of(std::tuple<double, double, double> const& offset) const;

            /**
             * Calculate the offset under a certain coordinate.
             *
             * @param x
             * @param y
             * @param z
             * @return the offset between the current and the target in specified dimension.
             */
            [[nodiscard]] std::tuple<double, double, double> offset_of(double const& x, double const& y, double const& z) const;

            /**
             * Output the location of the current point.
             *
             * @param stream the target stream to output to.
             * @param point the point to be output.
             *
             * @return the received stream.
             */
            friend std::ostream& operator<<(std::ostream& stream, Point const& point)
            {
                stream << "(" << std::setprecision(10) << point.__X << "," << std::setprecision(10) << point.__Y << "," << std::setprecision(10) << point.__Z << ")";
                return stream;
            }
        protected:
            unsigned char __R = 0;
            unsigned char __G = 0;
            unsigned char __B = 0;
            unsigned char __ALPHA = 255;
            double __X = 0;
            double __Y = 0;
            double __Z = 0;
            double __NX = 0;
            double __NY = 0;
            double __NZ = 0;
            double __CONFIDENCE = 1;
            double __INTENSITY = 0.5;
            void set_all_properties(double const X, double const Y, double const Z,
                unsigned char const R, unsigned char const G, unsigned char const B,
                double const NX, double const NY, double const NZ,
                unsigned char const ALPHA, double const CONFIDENCE, double const INTENSITY)
            {
                this->__X = X;
                this->__Y = Y;
                this->__Z = Z;
                this->__R = R;
                this->__G = G;
                this->__B = B;
                this->__NX = NX;
                this->__NY = NY;
                this->__NZ = NZ;
                this->__ALPHA = ALPHA;
                this->__CONFIDENCE = CONFIDENCE;
                this->__INTENSITY = INTENSITY;
            }
        };
	}
}

#endif
