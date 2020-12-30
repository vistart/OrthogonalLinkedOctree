/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#ifndef __LINKED_OCTREE_IN_PLY_H__
#define __LINKED_OCTREE_IN_PLY_H__

#include "../orthogonal_linked_octree/LinkedOctree.h"
#include "../orthogonal_linked_octree/OctreeNode.h"
#include "../../file_format/plyfile/PlyFile.h"
#include "../../file_format/plyfile/PlyVertex.h"
#include "../../file_format/plyfile/PlyVertexList.h"
#include "OctreeNodeInPly.h"
#include <vector>
#include <memory>
#include <string>

namespace vistart
{
    namespace orthogonal_linked_octree_for_python
    {
        class LinkedOctreeInPly : public vistart::orthogonal_linked_octree::LinkedOctree<
                vistart::point_cloud_base_presentation::PlyVertexList,
                vistart::point_cloud_base_presentation::PlyVertex,
                vistart::point_cloud_base_presentation::PlyFile
                >
        {
        public:
            LinkedOctreeInPly(std::string const&, unsigned int);
            virtual bool insert_point(NodeCoordinate const& c, std::shared_ptr<vistart::point_cloud_base_presentation::PlyVertex> point);
        protected:
            std::shared_ptr<vistart::point_cloud_base_presentation::PlyFile> plyfile;
        };
    }
}

#endif //__LINKEDOCTREE_H__
