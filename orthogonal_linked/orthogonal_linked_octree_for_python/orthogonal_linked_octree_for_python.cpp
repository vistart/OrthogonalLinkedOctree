/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#include "LinkedOctreeInPly.cpp"
#include "OctreeNodeInPly.cpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(orthogonal_linked_octree_for_python, m) {
    py::class_<
            vistart::orthogonal_linked_octree_for_python::LinkedOctreeInPly, std::shared_ptr<vistart::orthogonal_linked_octree_for_python::LinkedOctreeInPly>
    >(m, "LinkedOctreeInPly")
            .def(py::init<std::string const&, unsigned int>())
            .def("InsertPoint", &vistart::orthogonal_linked_octree_for_python::LinkedOctreeInPly::insert_point)
            .def("Get", &vistart::orthogonal_linked_octree::LinkedOctree<
                    vistart::point_cloud_base_presentation::PlyVertexList,
                    vistart::point_cloud_base_presentation::PlyVertex,
                    vistart::point_cloud_base_presentation::PlyFile>::get)
            ;

    py::class_<
            vistart::orthogonal_linked_octree_for_python::OctreeNodeInPly, std::shared_ptr<vistart::orthogonal_linked_octree_for_python::OctreeNodeInPly>
    >(m, "OctreeNodeInPly")
            .def(py::init<>())
            .def(py::init<std::shared_ptr<vistart::point_cloud_base_presentation::PlyVertex>>())
            .def(py::init<std::unordered_set<std::shared_ptr<vistart::point_cloud_base_presentation::PlyVertex>>>())
            .def("InsertPoint", &vistart::orthogonal_linked_octree_for_python::OctreeNodeInPly::insert_point)
    ;
}
