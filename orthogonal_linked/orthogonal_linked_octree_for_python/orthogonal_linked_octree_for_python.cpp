/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#include "LinkedOctreeInPly.h"
#include "OctreeNodeInPly.h"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace vp = vistart::point_cloud_base_presentation;
namespace vo = vistart::orthogonal_linked_octree;
namespace vop = vistart::orthogonal_linked_octree_for_python;

PYBIND11_MODULE(orthogonal_linked_octree_for_python, m) {
    py::class_<
            vop::LinkedOctreeInPly, std::shared_ptr<vop::LinkedOctreeInPly>
    >(m, "LinkedOctreeInPly")
            .def(py::init<std::string const&, unsigned int>())
            .def("InsertPoint", &vop::LinkedOctreeInPly::insert_point)
            .def("Get", &vo::LinkedOctree<
                vp::PlyVertexList,
                vp::PlyVertex,
                vp::PlyFile>::get)
            ;

    py::class_<
            vop::OctreeNodeInPly, std::shared_ptr<vop::OctreeNodeInPly>
    >(m, "OctreeNodeInPly")
            .def(py::init<>())
            .def(py::init<std::shared_ptr<vp::PlyVertex>>())
            .def(py::init<std::unordered_set<std::shared_ptr<vp::PlyVertex>>>())
            .def("InsertPoint", &vop::OctreeNodeInPly::insert_point)
    ;
}
