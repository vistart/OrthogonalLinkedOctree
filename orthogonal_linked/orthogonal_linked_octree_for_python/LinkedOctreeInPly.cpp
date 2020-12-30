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
vistart::orthogonal_linked_octree_for_python::LinkedOctreeInPly::LinkedOctreeInPly(std::string const& file_path, unsigned int depth)
{
    plyfile = std::make_shared<vistart::point_cloud_base_presentation::PlyFile>(file_path);
    if (plyfile->GetIsValid()) {
        vistart::orthogonal_linked_octree::LinkedOctree<
                vistart::point_cloud_base_presentation::PlyVertexList,
                vistart::point_cloud_base_presentation::PlyVertex,
                vistart::point_cloud_base_presentation::PlyFile>
                (plyfile->GetPointList(), depth);
    } else
        std::cout << "Invalid file!" << std::endl;
}

bool vistart::orthogonal_linked_octree_for_python::LinkedOctreeInPly::insert_point(
        const vistart::orthogonal_linked_octree::LinkedOctree<vistart::point_cloud_base_presentation::PlyVertexList, vistart::point_cloud_base_presentation::PlyVertex, vistart::point_cloud_base_presentation::PlyFile>::NodeCoordinate &c,
        std::shared_ptr<vistart::point_cloud_base_presentation::PlyVertex> point) {
    return vistart::orthogonal_linked_octree::LinkedOctree<vistart::point_cloud_base_presentation::PlyVertexList, vistart::point_cloud_base_presentation::PlyVertex, vistart::point_cloud_base_presentation::PlyFile>::insert_point(c, point);
}

#endif //__LINKED_OCTREE_IN_PLY_H__
