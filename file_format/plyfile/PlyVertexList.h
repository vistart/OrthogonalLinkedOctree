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

#ifndef __PLY_VERTEX_LIST_H__
#define __PLY_VERTEX_LIST_H__

#include "PlyVertex.h"
#include "PlyFileEncoding.h"
#include <vector>

#include "../point_cloud_base_presentation/PointList.h"

namespace  vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 This class is used to describe the list containing all the vertices.
		 */
		class PlyVertexList : public PointList<PlyVertex, PlyVertexList>
		{
		public:
			/*
			 Initialize the vertex list.
			 */
			PlyVertexList();

			/*
			 Destroy the vertex list.
			 */
			~PlyVertexList() override;

			/*
			 Add a vertex to this list.

			 @param str_vertex the string describing the vertex.
			 @return self.
			 */
			PlyVertexList& operator<<(std::string const& str_vertex);

			/*
			 Add a vertex to this list.

			 @param file the file stream containing the vertex.
			 @return PlyVertexList&: self.
			 */
			PlyVertexList& operator<<(std::fstream& file);

			/*
			 Add a vertex to this list.

			 @param vertex the vertex to be added.
			 @return self.
			 */
			PlyVertexList& operator<<(std::shared_ptr<PlyVertex> const& vertex);

			/*
			 Specify the current file encoding.

			 Note: The property encoding of the PLY file is unified, so you need to specify the file
			 encoding once before reading the property value, and it is strongly not recommended to change thereafter.
			 If you need to specify this parameter twice, you need to know the consequences of doing so.

			 @param PlyFileEncoding const&: the target file encoding.
			 @return PlyVertexList&: self.
			 */
			PlyVertexList& operator<<(PlyFileEncoding const& fe);

			/*
			 Read property names and corresponding types.

			 @param file the target file.
			 @return true if no exceptions occurred.
			 */
			bool read_element_vertex_names(std::fstream& file);

			/*
			 Set the count of vertex according to the value stored in ply file header.
			 Note: It is strongly recommended to set it only once before reading the
			 vertex properties.

			 @param count the target count.
			 */
			void SetCountInHeader(unsigned int count);

			/*
			 Get the count of vertex.

			 @return unsigned int const: the target count.
			 */
			[[nodiscard]] unsigned int GetCountInHeader() const;

			/*
			 Names of all properties.
			 Note: Please arrange their order in the vector according to the order of the property names
			 listed in the file header. The property names of the PLY file are unified, so you need to
			 specify the property names once before reading the property value, and it is strongly not
			 recommended to change thereafter.
			 */
			std::vector<PlyVertex::VertexName> names;

			/*
			 Return the pointer pointing to all vertices stored in this instance.

			 @return the shared pointer to all vertices.
			 */
			[[nodiscard]] std::shared_ptr<std::vector<std::shared_ptr<PlyVertex>>> GetPoints() const override;
		protected:
			unsigned int count_in_header = 0;
			PlyFileEncoding::FileEncoding file_encoding = { PlyFileEncoding::FILE_ENCODING_ASCII, 1.0 };
			//std::shared_ptr<std::vector<std::shared_ptr<PlyVertex>>> points;
		};
	}
}

#endif