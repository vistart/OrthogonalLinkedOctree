/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#ifndef __LINKEDOCTREE_H__
#define __LINKEDOCTREE_H__

#include "../orthogonal_linked_octree/LinkedOctree.h"
#include "../../file_format/plyfile/PlyFile.h"
#include <pybind11/pybind11.h>
#include <memory>
#include <string>

namespace py = pybind11;

namespace vistart
{
    namespace orthogonal_linked_octree_for_python
    {
        class LinkedOctreeInPly
        {
        public:
            LinkedOctreeInPly() = default;
            LinkedOctreeInPly(std::string const& file_path, unsigned int depth)
            {
                plyfile = std::make_shared<vistart::point_cloud_base_presentation::PlyFile>(file_path);
                if (plyfile->GetIsValid())
                    octree = std::make_shared<vistart::orthogonal_linked_octree::LinkedOctree<
                            vistart::point_cloud_base_presentation::PlyVertexList,
                            vistart::point_cloud_base_presentation::PlyVertex,
                            vistart::point_cloud_base_presentation::PlyFile>>(plyfile->GetPointList(), depth);
                else
                    std::cout << "Invalid file!" << std::endl;
            }
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

PYBIND11_MODULE(orthogonal_linked_octree_for_python, m) {
    py::class_<
            vistart::orthogonal_linked_octree_for_python::LinkedOctreeInPly
            >(m, "LinkedOctreeInPly")
            .def(py::init<>())
            .def(py::init<std::string const&, unsigned int>())
            ;
}

#endif //__LINKEDOCTREE_H__
