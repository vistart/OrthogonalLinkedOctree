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

#ifndef __PLY_EDGE_H__
#define __PLY_EDGE_H__

#include <string>
#include <vector>


#include "PlyFileEncoding.h"
#include "../point_cloud_base_presentation/PointEdge.h"

namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 @TODO: Implement it.
		 */
		class PlyEdge : public PointEdge
		{
		public:
			enum PropertyNames {
				PROPERTY_NONE,
				PROPERTY_VERTEX1,
				PROPERTY_VERTEX2,
				PROPERTY_RED,
				PROPERTY_GREEN,
				PROPERTY_BLUE
			};
			struct EdgeName {
				int name;
				int type;
			};
			PlyEdge() = default;
			PlyEdge(std::vector<EdgeName> const&, std::string const&);
			PlyEdge(std::vector<EdgeName> const&, std::fstream&, PlyFileEncoding::FileEncoding const&);
			PlyEdge(int, int, unsigned char R = 0, unsigned char G = 0, unsigned char B = 0);
			~PlyEdge() = default;
			friend std::ostream& operator<<(std::ostream& stream, PlyEdge const& edge)
			{
				stream << "(" << ")";
				return stream;
			}
		};
	}
}

#endif