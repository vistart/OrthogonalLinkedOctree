/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_FILE_ENCODING_H__
#include "PlyFileEncoding.h"
#endif

#ifdef __PLY_FILE_ENCODING_H__
using namespace std;
string vistart::point_cloud_base_presentation::PlyFileEncoding::Encoding() const
{
	if (this->file_encoding.type == FILE_ENCODING_ASCII)
		return PLY_FILE_ENCODING_ASCII;
	if (this->file_encoding.type == FILE_ENCODING_BINARY_BIG_ENDIAN)
		return PLY_FILE_BINARY_BIG_ENDIAN;
	if (this->file_encoding.type == FILE_ENCODING_BINARY_LITTLE_ENDIAN)
		return PLY_FILE_BINARY_LITTLE_ENDIAN;
	return "";
}

vistart::point_cloud_base_presentation::PlyFileEncoding& vistart::point_cloud_base_presentation::PlyFileEncoding::Encoding(string const& encoding)
{
	*this << encoding;
	return *this;
}

float vistart::point_cloud_base_presentation::PlyFileEncoding::Version() const
{
	return this->file_encoding.version;
}

vistart::point_cloud_base_presentation::PlyFileEncoding& vistart::point_cloud_base_presentation::PlyFileEncoding::Version(float version)
{
	*this << version;
	return *this;
}

vistart::point_cloud_base_presentation::PlyFileEncoding::FileEncoding vistart::point_cloud_base_presentation::PlyFileEncoding::GetDefinition() const&
{
	return this->file_encoding;
}

vistart::point_cloud_base_presentation::PlyFileEncoding& vistart::point_cloud_base_presentation::PlyFileEncoding::operator<<(fstream& file)
{
	string encoding;
	float version;
	file >> encoding >> version;
	*this << encoding << version;
	return *this;
}

vistart::point_cloud_base_presentation::PlyFileEncoding& vistart::point_cloud_base_presentation::PlyFileEncoding::operator<<(FileEncoding const& file_encoding)
{
	this->file_encoding = file_encoding;
	return *this;
}

vistart::point_cloud_base_presentation::PlyFileEncoding& vistart::point_cloud_base_presentation::PlyFileEncoding::operator<<(string const& format)
{
	if (format == PLY_FILE_ENCODING_ASCII)
	{
		this->file_encoding.type = FILE_ENCODING_ASCII;
	}
	else if (format == PLY_FILE_BINARY_BIG_ENDIAN) {
		this->file_encoding.type = FILE_ENCODING_BINARY_BIG_ENDIAN;
	}
	else if (format == PLY_FILE_BINARY_LITTLE_ENDIAN) {
		this->file_encoding.type = FILE_ENCODING_BINARY_LITTLE_ENDIAN;
	}
	return *this;
}

vistart::point_cloud_base_presentation::PlyFileEncoding& vistart::point_cloud_base_presentation::PlyFileEncoding::operator<<(float version)
{
	this->file_encoding.version = version;
	return *this;
}

bool vistart::point_cloud_base_presentation::PlyFileEncoding::operator==(PlyFileEncoding const& object) const
{
	return this->file_encoding.type == object.file_encoding.type && this->file_encoding.version == object.file_encoding.version;
}

bool vistart::point_cloud_base_presentation::PlyFileEncoding::operator!=(vistart::point_cloud_base_presentation::PlyFileEncoding const& object) const
{
	return !(*this == object);
}

bool vistart::point_cloud_base_presentation::PlyFileEncoding::operator==(PlyFileEncoding::FileEncoding const& object) const
{
	return this->file_encoding.type == object.type && this->file_encoding.version == object.version;
}

bool vistart::point_cloud_base_presentation::PlyFileEncoding::operator!=(PlyFileEncoding::FileEncoding const& object) const
{
	return !(*this == object);
}

vistart::point_cloud_base_presentation::PlyFileEncoding::PlyFileEncoding()
{
	this->endian = PlyPropertyType::check_endian();
	this->file_encoding = { FILE_ENCODING_ASCII, 1.0 };
}
#endif