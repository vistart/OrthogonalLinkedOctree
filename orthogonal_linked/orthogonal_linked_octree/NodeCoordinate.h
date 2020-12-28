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
#ifndef __NODE_COORDINATE_H__
#define __NODE_COORDINATE_H__

#include <ostream>

namespace vistart
{
    namespace orthogonal_linked_octree
    {
        class NodeCoordinate {
        public:
            NodeCoordinate(unsigned int X, unsigned int Y, unsigned int Z, unsigned char depth) : X(X), Y(Y), Z(Z), depth(depth)
            {
            }

            /**
             * Determine whether the two coordinates are equal.
             * Return true if XYZ and the depth must be completely equal.
             *
             * @param node_coordinate The coordinate to be compared.
             * @return true if XYZ and the depth completely equal.
             */
            virtual bool operator==(NodeCoordinate const& node_coordinate) const
            {
                return (X == node_coordinate.X && Y == node_coordinate.Y && Z == node_coordinate.Z && depth == node_coordinate.depth);
            }

            struct Hash
            {
                /**
                 * Calculate the hash value based on the coordinates and depth.
                 *
                 * The most four significant bits are temporarily not used.
                 *
                 * The remaining 60 bits are divided equally into three dimensions, each of which occupies 20 bits,
                 * that is, the value of each dimension ranges from 0 to 1048575.
                 * If the coordinate value exceeds this range, only the last 20 bits will be accepted,
                 * and the high bits will be discarded.
                 *
                 * For example:
                 * The NodeCoordinate instance is (X:16, Y:15, Z:14, depth:5)
                 *
                 * The calculated hash value is 0x0000 1000 00F0 000E.
                 * The corresponding binary is:
                 * 0000 0000 0000 0000
                 * 0001 0000 0000 0000
                 * 0000 0000 1111 0000
                 * 0000 0000 0000 1110
                 *
                 * @param i The node to be calculated.
                 * @return hash value.
                 */
                size_t operator()(NodeCoordinate const& i) const
                {
                    return
                        // static_cast<size_t>(i.depth) << 60 ^
                            static_cast<size_t>(i.X & 0xFFFFF) << 42 ^
                            static_cast<size_t>(i.Y & 0xFFFFF) << 21 ^
                            static_cast<size_t>(i.Z & 0xFFFFF);
                }
            };
            /*
            struct Equal
            {
                bool operator()(NodeCoordinate const& left, NodeCoordinate const& right) const
                {
                    return left == right;
                }
            };
            */

            /**
             * Node coordinate X.
             */
            unsigned int X = 0;
            /**
             * Node coordinate Y.
             */
            unsigned int Y = 0;
            /**
             * Node coordinate Z.
             */
            unsigned int Z = 0;
            /**
             * Node coordinate depth.
             */
            unsigned char depth = 1;

            friend std::ostream& operator<<(std::ostream& stream, NodeCoordinate const& node_coordinate)
            {
                stream << "(" << node_coordinate.X << ", " << node_coordinate.Y << ", " << node_coordinate.Z << " @ " << node_coordinate.depth << ")" << std::endl;
                return stream;
            }
        };
    }
}

#endif
