/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#ifndef __PY_PLY_FILE_H__
#include "PyPlyFile.h"
#include <pybind11/pybind11.h>
#endif

#ifdef __PY_PLY_FILE_H__

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
}
#endif // __PY_PLY_FILE_H__
