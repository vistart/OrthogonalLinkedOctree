/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_FACE_H__
#include "PlyFace.h"
#endif

#ifdef __PLY_FACE_H__
using namespace std;
#define READ_BE PlyPropertyType::read_binary_be_property
#define READ_LE PlyPropertyType::read_binary_le_property

vistart::point_cloud_base_presentation::PlyFace::PlyFace(FaceDescription const& fd, std::string const& str_face)
{
	stringstream stream(str_face);
	unsigned int size;
	stream >> size;
	for (unsigned int i = 0; i < size; i++)
	{
		unsigned int index;
		stream >> index;
		this->vertex_indices->push(index);
	}
}

vistart::point_cloud_base_presentation::PlyFace::PlyFace(FaceDescription const& fd, std::fstream& file, PlyFileEncoding::FileEncoding const& file_encoding)
{
	unsigned int size = 0;
	switch (file_encoding.type)
	{
	case PlyFileEncoding::FILE_ENCODING_ASCII:
		file >> size;
		for (unsigned int i = 0; i < size; i++)
		{
			unsigned int index;
			file >> index;
			this->vertex_indices->push(index);
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_BIG_ENDIAN:
		switch (fd.list_type)
		{
		case PlyPropertyType::INT8: size = READ_BE<char>(file); break;
		case PlyPropertyType::UINT8: size = READ_BE<unsigned char>(file); break;
		case PlyPropertyType::INT16: size = READ_BE<short>(file); break;
		case PlyPropertyType::UINT16: size = READ_BE<unsigned short>(file); break;
		case PlyPropertyType::INT32: size = READ_BE<int>(file); break;
		case PlyPropertyType::UINT32: size = READ_BE<unsigned int>(file); break;
		// case PlyPropertyType::FLOAT32: size = READ_BE<float>(file); break;
		// case PlyPropertyType::FLOAT64: size = READ_BE<double>(file); break;
		default: size = 0;
		}
		for (unsigned int i = 0; i < size; i++)
		{
			unsigned int index;
			switch (fd.vertex_type)
			{
			case PlyPropertyType::INT8: index = READ_BE<char>(file); break;
			case PlyPropertyType::UINT8: index = READ_BE<unsigned char>(file); break;
			case PlyPropertyType::INT16: index = READ_BE<short>(file); break;
			case PlyPropertyType::UINT16: index = READ_BE<unsigned short>(file); break;
			case PlyPropertyType::INT32: index = READ_BE<int>(file); break;
			case PlyPropertyType::UINT32: index = READ_BE<unsigned int>(file); break;
			// case PlyPropertyType::FLOAT32: index = READ_BE<float>(file); break;
			// case PlyPropertyType::FLOAT64: index = READ_BE<double>(file); break;
			default: index = 0;
			}
			this->vertex_indices->push(index);
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_LITTLE_ENDIAN:
		switch(fd.list_type)
		{
		case PlyPropertyType::INT8: size = READ_LE<char>(file); break;
		case PlyPropertyType::UINT8: size = READ_LE<unsigned char>(file); break;
		case PlyPropertyType::INT16: size = READ_LE<short>(file); break;
		case PlyPropertyType::UINT16: size = READ_LE<unsigned short>(file); break;
		case PlyPropertyType::INT32: size = READ_LE<int>(file); break;
		case PlyPropertyType::UINT32: size = READ_LE<unsigned int>(file); break;
		// case PlyPropertyType::FLOAT32: size = READ_LE<float>(file); break;
		// case PlyPropertyType::FLOAT64: size = READ_LE<double>(file); break;
		default: size = 0;
		}
		for (unsigned int i = 0; i < size; i++)
		{
			unsigned int index;
			switch (fd.vertex_type)
			{
			case PlyPropertyType::INT8: index = READ_LE<char>(file); break;
			case PlyPropertyType::UINT8: index = READ_LE<unsigned char>(file); break;
			case PlyPropertyType::INT16: index = READ_LE<short>(file); break;
			case PlyPropertyType::UINT16: index = READ_LE<unsigned short>(file); break;
			case PlyPropertyType::INT32: index = READ_LE<int>(file); break;
			case PlyPropertyType::UINT32: index = READ_LE<unsigned int>(file); break;
			// case PlyPropertyType::FLOAT32: index = READ_LE<float>(file); break;
			// case PlyPropertyType::FLOAT64: index = READ_LE<double>(file); break;
			default: index = 0;
			}
			this->vertex_indices->push(index);
		}
		break;
	}
}

vistart::point_cloud_base_presentation::PlyFace::PlyFace(std::initializer_list<unsigned> const& faces)
{
	for (const auto& p : faces) this->vertex_indices->push(p);
}

#endif
