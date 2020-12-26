/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_EDGE_H__
#include "PlyEdge.h"
#endif

#ifdef __PLY_EDGE_H__
#include <sstream>
#define READ_BE PlyPropertyType::read_binary_be_property
#define READ_LE PlyPropertyType::read_binary_le_property
vistart::point_cloud_base_presentation::PlyEdge::PlyEdge(std::vector<EdgeName> const& names, std::string const& edge)
{
	int vertex1 = 0, vertex2 = 0;
	unsigned int __R = 0, __G = 0, __B = 0;
	unsigned char R = 0, G = 0, B = 0;
	std::stringstream stream(edge);
	for (const auto& name:names)
	{
		switch (name.name)
		{
		case PROPERTY_VERTEX1:
			stream >> vertex1;
			break;
		case PROPERTY_VERTEX2:
			stream >> vertex2;
			break;
		case PROPERTY_RED:
			stream >> __R;
			R = __R & 0xFF;
			break;
		case PROPERTY_GREEN:
			stream >> __G;
			G = __G & 0xFF;
			break;
		case PROPERTY_BLUE:
			stream >> __B;
			B = __B & 0xFF;
			break;
		default:
			std::string none;
			stream >> none;
		}
	}
	this->set_all_properties(vertex1, vertex2, R, G, B);
}

vistart::point_cloud_base_presentation::PlyEdge::PlyEdge(std::vector<EdgeName> const& names, std::fstream& f, PlyFileEncoding::FileEncoding const& fe)
{
	int vertex1 = 0, vertex2 = 0;
	unsigned int __R = 0, __G = 0, __B = 0;
	unsigned char R = 0, G = 0, B = 0;
	switch (fe.type)
	{
	case PlyFileEncoding::FILE_ENCODING_ASCII:
		for (const auto& name : names)
		{
			switch (name.name)
			{
			case PROPERTY_VERTEX1:
				f >> vertex1;
				break;
			case PROPERTY_VERTEX2:
				f >> vertex2;
				break;
			case PROPERTY_RED:
				f >> __R;
				R = __R & 0xFF;
				break;
			case PROPERTY_GREEN:
				f >> __G;
				G = __G & 0xFF;
				break;
			case PROPERTY_BLUE:
				f >> __B;
				B = __B & 0xFF;
				break;
			default:
				std::string none;
				f >> none;
			}
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_BIG_ENDIAN:
		for (const auto& name : names)
		{
			switch (name.name)
			{
			case PROPERTY_VERTEX1:
				switch (name.type)
				{
				case PlyPropertyType::INT8: vertex1 = READ_BE<char>(f); break;
				case PlyPropertyType::UINT8: vertex1 = READ_BE<unsigned char>(f); break;
				case PlyPropertyType::INT16: vertex1 = READ_BE<short>(f); break;
				case PlyPropertyType::UINT16: vertex1 = READ_BE<unsigned short>(f); break;
				case PlyPropertyType::INT32: vertex1 = READ_BE<int>(f); break;
				case PlyPropertyType::UINT32: vertex1 = READ_BE<unsigned int>(f); break;
				}
				break;
			case PROPERTY_VERTEX2:
				switch (name.type)
				{
				case PlyPropertyType::INT8: vertex2 = READ_BE<char>(f); break;
				case PlyPropertyType::UINT8: vertex2 = READ_BE<unsigned char>(f); break;
				case PlyPropertyType::INT16: vertex2 = READ_BE<short>(f); break;
				case PlyPropertyType::UINT16: vertex2 = READ_BE<unsigned short>(f); break;
				case PlyPropertyType::INT32: vertex2 = READ_BE<int>(f); break;
				case PlyPropertyType::UINT32: vertex2 = READ_BE<unsigned int>(f); break;
				}
				break;
			case PROPERTY_RED:
				R = READ_BE<unsigned char>(f);
				break;
			case PROPERTY_GREEN:
				G = READ_BE<unsigned char>(f);
				break;
			case PROPERTY_BLUE:
				B = READ_BE<unsigned char>(f);
				break;
			default:
				std::string none;
				f >> none;
			}
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_LITTLE_ENDIAN:
		for (const auto& name : names)
		{
			switch (name.name)
			{
			case PROPERTY_VERTEX1:
				switch (name.type)
				{
				case PlyPropertyType::INT8: vertex1 = READ_LE<char>(f); break;
				case PlyPropertyType::UINT8: vertex1 = READ_LE<unsigned char>(f); break;
				case PlyPropertyType::INT16: vertex1 = READ_LE<short>(f); break;
				case PlyPropertyType::UINT16: vertex1 = READ_LE<unsigned short>(f); break;
				case PlyPropertyType::INT32: vertex1 = READ_LE<int>(f); break;
				case PlyPropertyType::UINT32: vertex1 = READ_LE<unsigned int>(f); break;
				}
				break;
			case PROPERTY_VERTEX2:
				switch (name.type)
				{
				case PlyPropertyType::INT8: vertex2 = READ_LE<char>(f); break;
				case PlyPropertyType::UINT8: vertex2 = READ_LE<unsigned char>(f); break;
				case PlyPropertyType::INT16: vertex2 = READ_LE<short>(f); break;
				case PlyPropertyType::UINT16: vertex2 = READ_LE<unsigned short>(f); break;
				case PlyPropertyType::INT32: vertex2 = READ_LE<int>(f); break;
				case PlyPropertyType::UINT32: vertex2 = READ_LE<unsigned int>(f); break;
				}
				break;
			case PROPERTY_RED:
				R = READ_BE<unsigned char>(f);
				break;
			case PROPERTY_GREEN:
				G = READ_BE<unsigned char>(f);
				break;
			case PROPERTY_BLUE:
				B = READ_BE<unsigned char>(f);
				break;
			default:
				std::string none;
				f >> none;
			}
		}
		break;
	}
	this->set_all_properties(vertex1, vertex2, R, G, B);
}

vistart::point_cloud_base_presentation::PlyEdge::PlyEdge(int v1, int v2, unsigned char R, unsigned char G, unsigned char B)
{
	this->set_all_properties(v1, v2, R, G, B);
}

#endif
