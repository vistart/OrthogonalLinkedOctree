/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#ifndef __OCTREE_NODE_IN_PLY_H__
#define __OCTREE_NODE_IN_PLY_H__

#include "../orthogonal_linked_octree/OctreeNode.h"
#include "../../file_format/plyfile/PlyVertex.h"
#include <memory>
namespace vistart {
    namespace orthogonal_linked_octree_for_python
    {
        class OctreeNodeInPly : public
                vistart::orthogonal_linked_octree::OctreeNode<
                vistart::point_cloud_base_presentation::PlyVertex> {
        public:
            OctreeNodeInPly() = default;
            typedef vistart::point_cloud_base_presentation::PlyVertex plyvertex;
            OctreeNodeInPly(std::shared_ptr<plyvertex> point) : OctreeNode(point) {}
            OctreeNodeInPly(std::unordered_set<std::shared_ptr<plyvertex>> points) : OctreeNode(points) {}
            void insert_point(std::shared_ptr<plyvertex> point) {};
            virtual ~OctreeNodeInPly() = default;
        protected:

        };
    }
}


#endif //__OCTREE_NODE_IN_PLY_H__
