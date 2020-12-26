/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_VERTEX_H__
#include "PlyVertex.h"
#endif

#ifdef __PLY_VERTEX_H__
using namespace std;
#define READ_BE PlyPropertyType::read_binary_be_property
#define READ_LE PlyPropertyType::read_binary_le_property

vistart::point_cloud_base_presentation::PlyVertex::PlyVertex(vector<VertexName> const& names, string const& vertex)
{
	double X = 0, Y = 0, Z = 0;
	/*
	 * If you treat `char` as a number, you cannot directly stream the content of
	 * a character or string to a `char` type variable. Instead, you need to output
	 * it to an integer or unsigned integer variable first, and then perform bit
	 * operations, otherwise it will be treated as a character.
	 * For example:
	 * If you would like to receive the number `7` and put it into a `char` variable,
	 * you'll find that the value of variable is `55`, the ASCII code of character `7`,
	 * not number `7`.
	 */
	unsigned int __R = 0, __G = 0, __B = 0;
	unsigned char R = 0, G = 0, B = 0;
	double NX = 0, NY = 0, NZ = 0, CONFIDENCE = 1, INTENSITY = 0.5;
	unsigned int __ALPHA = 255;
	unsigned char ALPHA = 255;
	stringstream stream(vertex);
	for (const auto& name : names)
	{
		switch (name.name) {
		case PROPERTY_X:
			stream >> X;
			break;
		case PROPERTY_Y:
			stream >> Y;
			break;
		case PROPERTY_Z:
			stream >> Z;
			break;
		case PROPERTY_R:
			stream >> __R;
			R = __R & 0xFF;
			break;
		case PROPERTY_G:
			stream >> __G;
			G = __G & 0xFF;
			break;
		case PROPERTY_B:
			stream >> __B;
			B = __B & 0xFF;
			break;
		case PROPERTY_NX:
			stream >> NX;
			break;
		case PROPERTY_NY:
			stream >> NY;
			break;
		case PROPERTY_NZ:
			stream >> NZ;
			break;
		case PROPERTY_ALPHA:
			stream >> __ALPHA;
			ALPHA = __ALPHA & 0xFF;
			break;
		case PROPERTY_CONFIDENCE:
			stream >> CONFIDENCE;
			break;
		case PROPERTY_INTENSITY:
			stream >> INTENSITY;
			break;
		default:
			string none;
			stream >> none;
		}
	}
	this->set_all_properties(X, Y, Z, R, G, B, NX, NY, NZ, ALPHA, CONFIDENCE, INTENSITY);
}

vistart::point_cloud_base_presentation::PlyVertex::PlyVertex(vector<VertexName> const& names, fstream& file, PlyFileEncoding::FileEncoding const& file_encoding)
{
	double X = 0, Y = 0, Z = 0;
	unsigned int __R = 0, __G = 0, __B = 0;
	unsigned char R = 0, G = 0, B = 0;
	double NX = 0, NY = 0, NZ = 0, CONFIDENCE = 1, INTENSITY = 0.5;
	unsigned int __ALPHA = 255;
	unsigned char ALPHA = 255;
	switch (file_encoding.type) {
	case PlyFileEncoding::FILE_ENCODING_ASCII:
		for (const auto& name : names)
		{
			switch (name.name) {
			case PROPERTY_X:
				file >> X;
				break;
			case PROPERTY_Y:
				file >> Y;
				break;
			case PROPERTY_Z:
				file >> Z;
				break;
			case PROPERTY_R:
				file >> __R;
				R = __R & 0xFF;
				break;
			case PROPERTY_G:
				file >> __G;
				G = __G & 0xFF;
				break;
			case PROPERTY_B:
				file >> __B;
				B = __B & 0xFF;
				break;
			case PROPERTY_NX:
				file >> NX;
				break;
			case PROPERTY_NY:
				file >> NY;
				break;
			case PROPERTY_NZ:
				file >> NZ;
				break;
			case PROPERTY_ALPHA:
				file >> __ALPHA;
				ALPHA = __ALPHA & 0xFF;
				break;
			case PROPERTY_CONFIDENCE:
				file >> CONFIDENCE;
				break;
			case PROPERTY_INTENSITY:
				file >> INTENSITY;
				break;
			default:
				string none;
				file >> none;
			}
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_BIG_ENDIAN:
		for (const auto& name : names)
		{
			switch (name.name) {
			case PROPERTY_X:
				switch (name.type) {
				case PlyPropertyType::INT8: X = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: X = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: X = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: X = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: X = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: X = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: X = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: X = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_Y:
				switch (name.type) {
				case PlyPropertyType::INT8: Y = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: Y = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: Y = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: Y = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: Y = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: Y = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Y = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: Y = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_Z:
				switch (name.type) {
				case PlyPropertyType::INT8: Z = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: Z = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: Z = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: Z = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: Z = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: Z = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Z = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: Z = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_R:
				R = READ_BE<unsigned char>(file);
				break;
			case PROPERTY_G:
				G = READ_BE<unsigned char>(file);
				break;
			case PROPERTY_B:
				B = READ_BE<unsigned char>(file);
				break;
			case PROPERTY_NX:
				switch (name.type) {
				case PlyPropertyType::INT8: NX = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: NX = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: NX = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: NX = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: NX = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: NX = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NX = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: NX = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_NY:
				switch (name.type) {
				case PlyPropertyType::INT8: NY = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: NY = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: NY = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: NY = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: NY = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: NY = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NY = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: NY = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_NZ:
				switch (name.type) {
				case PlyPropertyType::INT8: NZ = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: NZ = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: NZ = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: NZ = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: NZ = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: NZ = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NZ = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: NZ = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_ALPHA:
				ALPHA = READ_BE<unsigned char>(file);
				break;
			case PROPERTY_CONFIDENCE:
				switch (name.type) {
				case PlyPropertyType::INT8: CONFIDENCE = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: CONFIDENCE = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: CONFIDENCE = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: CONFIDENCE = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: CONFIDENCE = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: CONFIDENCE = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: CONFIDENCE = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: CONFIDENCE = READ_BE<double>(file); break;
				}
				break;
			case PROPERTY_INTENSITY:
				switch (name.type) {
				case PlyPropertyType::INT8: INTENSITY = READ_BE<char>(file); break;
				case PlyPropertyType::UINT8: INTENSITY = READ_BE<unsigned char>(file); break;
				case PlyPropertyType::INT16: INTENSITY = READ_BE<short>(file); break;
				case PlyPropertyType::UINT16: INTENSITY = READ_BE<unsigned short>(file); break;
				case PlyPropertyType::INT32: INTENSITY = READ_BE<int>(file); break;
				case PlyPropertyType::UINT32: INTENSITY = READ_BE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: INTENSITY = READ_BE<float>(file); break;
				case PlyPropertyType::FLOAT64: INTENSITY = READ_BE<double>(file); break;
				}
				break;
			default:
				string none;
				file >> none;
			}
		}
		break;
	case PlyFileEncoding::FILE_ENCODING_BINARY_LITTLE_ENDIAN:
		for (const auto& name : names)
		{
			switch (name.name) {
			case PROPERTY_X:
				switch (name.type) {
				case PlyPropertyType::INT8: X = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: X = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: X = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: X = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: X = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: X = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: X = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: X = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_Y:
				switch (name.type) {
				case PlyPropertyType::INT8: Y = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: Y = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: Y = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: Y = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: Y = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: Y = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Y = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: Y = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_Z:
				switch (name.type) {
				case PlyPropertyType::INT8: Z = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: Z = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: Z = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: Z = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: Z = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: Z = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: Z = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: Z = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_R:
				R = READ_LE<unsigned char>(file);
				break;
			case PROPERTY_G:
				G = READ_LE<unsigned char>(file);
				break;
			case PROPERTY_B:
				B = READ_LE<unsigned char>(file);
				break;
			case PROPERTY_NX:
				switch (name.type) {
				case PlyPropertyType::INT8: NX = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: NX = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: NX = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: NX = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: NX = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: NX = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NX = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: NX = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_NY:
				switch (name.type) {
				case PlyPropertyType::INT8: NY = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: NY = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: NY = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: NY = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: NY = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: NY = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NY = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: NY = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_NZ:
				switch (name.type) {
				case PlyPropertyType::INT8: NZ = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: NZ = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: NZ = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: NZ = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: NZ = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: NZ = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: NZ = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: NZ = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_ALPHA:
				ALPHA = READ_LE<unsigned char>(file);
				break;
			case PROPERTY_CONFIDENCE:
				switch (name.type) {
				case PlyPropertyType::INT8: CONFIDENCE = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: CONFIDENCE = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: CONFIDENCE = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: CONFIDENCE = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: CONFIDENCE = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: CONFIDENCE = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: CONFIDENCE = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: CONFIDENCE = READ_LE<double>(file); break;
				}
				break;
			case PROPERTY_INTENSITY:
				switch (name.type) {
				case PlyPropertyType::INT8: INTENSITY = READ_LE<char>(file); break;
				case PlyPropertyType::UINT8: INTENSITY = READ_LE<unsigned char>(file); break;
				case PlyPropertyType::INT16: INTENSITY = READ_LE<short>(file); break;
				case PlyPropertyType::UINT16: INTENSITY = READ_LE<unsigned short>(file); break;
				case PlyPropertyType::INT32: INTENSITY = READ_LE<int>(file); break;
				case PlyPropertyType::UINT32: INTENSITY = READ_LE<unsigned int>(file); break;
				case PlyPropertyType::FLOAT32: INTENSITY = READ_LE<float>(file); break;
				case PlyPropertyType::FLOAT64: INTENSITY = READ_LE<double>(file); break;
				}
				break;
			default:
				string none;
				file >> none;
			}
		}
		break;
	}
	this->set_all_properties(X, Y, Z, R, G, B, NX, NY, NZ, ALPHA, CONFIDENCE, INTENSITY);
}

vistart::point_cloud_base_presentation::PlyVertex::PlyVertex(double X, double Y, double Z, unsigned char R = 0, unsigned char G = 0, unsigned char B = 0)
{
	this->set_all_properties(X, Y, Z, R, G, B, 0, 0, 0, 255, 1, 0.5);
}
#endif