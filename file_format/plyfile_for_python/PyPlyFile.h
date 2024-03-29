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
#ifndef __PY_PLY_FILE_H__
#define __PY_PLY_FILE_H__

#include "../plyfile/PlyFile.h"

namespace vistart
{
    namespace point_cloud_base_presentation
    {
        class PyPlyFile : public vistart::point_cloud_base_presentation::PlyFile {
        public:
            explicit PyPlyFile(std::string const& filePath) : PlyFile(filePath){}
            [[nodiscard]] std::string get_file_format() { return PlyFile::get_file_format(); }
            bool GetIsValid() const { return PlyFile::GetIsValid(); }
        };
    }
}

#endif //__PY_PLY_FILE_H__
