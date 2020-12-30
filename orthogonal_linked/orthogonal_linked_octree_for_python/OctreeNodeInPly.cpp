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
#include "OctreeNodeInPly.h"
#endif

#ifdef __OCTREE_NODE_IN_PLY_H__
void vistart::orthogonal_linked_octree_for_python::OctreeNodeInPly::insert_point(std::shared_ptr<plyvertex> point) {
    
}
PYBIND11_MODULE(orthogonal_linked_octree_for_python, m)
{
    py::class<
            vistart::orthogonal_linked_octree_for_python::OctreeNodeInPly
            >(m, "OctreeNodeInPly")
            .def(py::init);
}
#endif
