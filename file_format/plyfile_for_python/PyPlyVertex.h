/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __PY_PLY_VERTEX_H__
#define __PY_PLY_VERTEX_H__
#include "../plyfile/PlyVertex.h"

namespace vistart
{
    namespace point_cloud_base_presentation
    {
        class PyPlyVertex : public vistart::point_cloud_base_presentation::PlyVertex {
        public:
            PyPlyVertex() = default;
            PyPlyVertex(std::vector<VertexName> const& v, std::string const& a) : PlyVertex(v, a) {}
        };
    }
}


#endif //__PY_PLY_VERTEX_H__
