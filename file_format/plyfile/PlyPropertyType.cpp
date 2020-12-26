/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_PROPERTY_TYPE_H__
#include "PlyPropertyType.h"
#endif

#ifdef __PLY_PROPERTY_TYPE_H__
using namespace std;
const int vistart::point_cloud_base_presentation::PlyPropertyType::PropertyDataTypeSize[9] = { 0, 1, 1, 2, 2, 4, 4, 4, 8 };

vistart::point_cloud_base_presentation::PlyPropertyType::Endian vistart::point_cloud_base_presentation::PlyPropertyType::check_endian()
{
#ifdef IS_LITTLE_ENDIAN
	return Endian::LITTLE;
#else
	return Endian::BIG;
#endif
}

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::NOTYPE> {
	using type = double;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::INT8> {
	using type = char;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::UINT8> {
	using type = unsigned char;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::INT16> {
	using type = short;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::UINT16> {
	using type = unsigned short;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::INT32> {
	using type = int;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::UINT32> {
	using type = unsigned int;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::FLOAT32> {
	using type = float;
};

template <>
struct vistart::point_cloud_base_presentation::PlyPropertyType::TypeSelector<vistart::point_cloud_base_presentation::PlyPropertyType::FLOAT64> {
	using type = double;
};
#endif
