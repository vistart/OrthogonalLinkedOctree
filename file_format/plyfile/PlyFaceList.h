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

#ifndef __PLY_FACE_LIST_H__
#define __PLY_FACE_LIST_H__

#include "PlyFace.h"
#include "PlyFileEncoding.h"
#include <vector>

#include "../point_cloud_base_presentation/PointFaceList.h"

namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 @TODO: Implement it.
		 */
		class PlyFaceList : public PointFaceList<PlyFace, PlyFaceList>
		{
		public:
			PlyFaceList();
			~PlyFaceList() override;

			PlyFaceList& operator<<(std::string const&);
			PlyFaceList& operator<<(std::fstream&);
			PlyFaceList& operator<<(std::shared_ptr<PlyFace> const&);
			PlyFaceList& operator<<(PlyFileEncoding const& fe);
			bool read_element_face_names(std::fstream& file);
			PlyFace::FaceDescription face_description = {
				PlyFace::PROPERTY_LIST,
				PlyPropertyType::NOTYPE,
				PlyPropertyType::NOTYPE,
				PlyFace::PROPERTY_VERTEX_INDICES
			};

			/*
			 Set the count of face according to the value stored in ply file header.
			 Note: It is strongly recommended to set it only once before reading the
			 face properties.

			 @param count the target count.
			 */
			void SetCountInHeader(unsigned int count);

			/*
			 Get the count of face.

			 @return unsigned int const: the target count.
			 */
			[[nodiscard]] unsigned int GetCountInHeader() const;
			/*
			 Return the pointer pointing to all faces stored in this instance.

			 @return the shared pointer to all faces.
			 */
			[[nodiscard]] std::shared_ptr<std::vector<std::shared_ptr<PlyFace>>> GetFaces() const override;
		protected:
			unsigned int count_in_header = 0;
			PlyFileEncoding::FileEncoding file_encoding = { PlyFileEncoding::FILE_ENCODING_ASCII, 1.0 };
			//std::shared_ptr<std::vector<std::shared_ptr<PlyFace>>> faces;
		};
	}
}

#endif