/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#include "PyPlyFile.cpp"
#include "PyPlyVertex.cpp"
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(plyfile_for_python, m)
{
    py::class_<
            vistart::point_cloud_base_presentation::PyPlyFile
    >(m, "PyPlyFile")
            .def(py::init<std::string const&>())
            .def("GetFileFormat", &vistart::point_cloud_base_presentation::PyPlyFile::get_file_format)
            .def("GetIsValid", &vistart::point_cloud_base_presentation::PyPlyFile::GetIsValid)
            ;
    ;
    py::class_<vistart::point_cloud_base_presentation::PyPlyVertex
    >(m, "PyPlyVertex")
            .def(py::init<>())
            .def(py::init<
                    std::vector<vistart::point_cloud_base_presentation::PlyVertex::VertexName> const&,
                    std::string const&
            >())
            ;
}
