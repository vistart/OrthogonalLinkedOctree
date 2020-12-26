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

#ifndef __PLY_FACE_H__
#define __PLY_FACE_H__

#include "PlyFileEncoding.h"
#include <sstream>
#include <vector>

#include "../point_cloud_base_presentation/PointFace.h"

namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 @TODO: Implement it.
		 */
		class PlyFace : public PointFace
		{
		public:
			struct FaceDescription
			{
				int list_name;
				int list_type;
				int vertex_type;
				int vertex_name;
			};
			PlyFace() = default;
			PlyFace(FaceDescription const&, std::string const&);
			PlyFace(FaceDescription const&, std::fstream&, PlyFileEncoding::FileEncoding const&);
			PlyFace(std::initializer_list<unsigned int> const&);
			~PlyFace() override = default;
			enum PropertyNames {
				PROPERTY_NONE,
				PROPERTY_LIST,
				PROPERTY_VERTEX_INDICES
			};
			friend std::ostream& operator<<(std::ostream& stream, PlyFace const& face)
			{
				stream << "(";
				auto f = face.vertex_indices;
				while (!f->empty())
				{
					stream << f->top();
					f->pop();
					if (!f->empty()) stream << ", ";
				}
				stream << ")";
				return stream;
			}
		};
	}
}

#endif