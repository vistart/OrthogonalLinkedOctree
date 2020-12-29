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
#include "../../file_format/plyfile/PlyFile.h"
#include "OctreeNodeInPly.h"
#include <pybind11/pybind11.h>
#include <vector>
#include <memory>
#include <string>

namespace py = pybind11;

namespace vistart
{
    namespace orthogonal_linked_octree_for_python
    {
        class LinkedOctreeInPly : vistart::orthogonal_linked_octree::LinkedOctree<
                vistart::point_cloud_base_presentation::PlyVertexList,
                vistart::point_cloud_base_presentation::PlyVertex,
                vistart::point_cloud_base_presentation::PlyFile
                >
        {
        public:
            LinkedOctreeInPly(std::string const&, unsigned int);

        protected:
            std::shared_ptr<vistart::point_cloud_base_presentation::PlyFile> plyfile;
            std::shared_ptr<
            vistart::orthogonal_linked_octree::LinkedOctree<
                    vistart::point_cloud_base_presentation::PlyVertexList,
                    vistart::point_cloud_base_presentation::PlyVertex,
                    vistart::point_cloud_base_presentation::PlyFile>> octree;
        };
    }
}

#endif //__LINKEDOCTREE_H__
