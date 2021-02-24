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
#include "LinkedOctreeInPly.h"
#endif

#ifdef __LINKED_OCTREE_IN_PLY_H__
namespace vp = vistart::point_cloud_base_presentation;
namespace vo = vistart::orthogonal_linked_octree;
namespace vop = vistart::orthogonal_linked_octree_for_python;
vop::LinkedOctreeInPly::LinkedOctreeInPly(std::string const& file_path, unsigned int depth)
{
    plyfile = std::make_shared<vp::PlyFile>(file_path);
    if (plyfile->GetIsValid()) {
        vo::LinkedOctree<
                vp::PlyVertexList,
                vp::PlyVertex,
                vp::PlyFile>
                (plyfile->GetPointList(), depth);
    } else
    std::cout << "Invalid file!" << std::endl;
}

bool vop::LinkedOctreeInPly::insert_point(
        const NodeCoordinate &c,
        std::shared_ptr<vp::PlyVertex> point) {
    return LinkedOctree<vp::PlyVertexList, vp::PlyVertex, vp::PlyFile>::insert_point(c, point);
}

#endif //__LINKED_OCTREE_IN_PLY_H__
