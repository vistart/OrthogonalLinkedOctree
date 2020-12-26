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

#ifndef __PLY_EDGE_LIST_H__
#define __PLY_EDGE_LIST_H__

#include "PlyEdge.h"
#include "PlyFileEncoding.h"
#include <vector>

#include "../point_cloud_base_presentation/PointEdgeList.h"
namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 @TODO: Implement it.
		 */
		class PlyEdgeList : public PointEdgeList<PlyEdge, PlyEdgeList>
		{
		public:
			/*
			 No action is required by default.
			 */
			PlyEdgeList();
			~PlyEdgeList() override;
			PlyEdgeList& operator<<(std::string const&);
			PlyEdgeList& operator<<(std::fstream&);
			PlyEdgeList& operator<<(std::shared_ptr<PlyEdge> const&);
			PlyEdgeList& operator<<(PlyFileEncoding const&);
			bool read_element_edge_names(std::fstream& file);
			/*
			 Set the count of edge according to the value stored in ply file header.
			 Note: It is strongly recommended to set it only once before reading the
			 edge properties.

			 @param count the target count.
			 */
			void SetCountInHeader(unsigned int count);

			/*
			 Get the count of edge.

			 @return unsigned int const: the target count.
			 */
			[[nodiscard]] unsigned int GetCountInHeader() const;
			/*
			 Return the pointer pointing to all edges stored in this instance.

			 @return the shared pointer to all edges.
			 */
			[[nodiscard]] std::shared_ptr<std::vector<std::shared_ptr<PlyEdge>>> GetEdges() const override;

			std::vector<PlyEdge::EdgeName> names;
		protected:
			unsigned int count_in_header = 0;
			PlyFileEncoding::FileEncoding file_encoding = { PlyFileEncoding::FILE_ENCODING_ASCII, 1.0 };
			//std::shared_ptr<std::vector<std::shared_ptr<PlyEdge>>> edges;
		};
	}
}

#endif