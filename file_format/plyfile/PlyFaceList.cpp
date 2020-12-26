/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_FACE_LIST_H__
#include "PlyFaceList.h"
#endif

#ifdef __PLY_FACE_LIST_H__
using namespace std;
#include <memory>
vistart::point_cloud_base_presentation::PlyFaceList::PlyFaceList()
{
	this->faces = make_shared<vector<shared_ptr<PlyFace>>>();
}
vistart::point_cloud_base_presentation::PlyFaceList::~PlyFaceList()
{
	this->faces = nullptr;
}

vistart::point_cloud_base_presentation::PlyFaceList& vistart::point_cloud_base_presentation::PlyFaceList::operator<<(string const& str_vertex)
{
	auto vertex = make_shared<PlyFace>(face_description, str_vertex);
	this->faces->emplace_back(vertex);
	return *this;
}

vistart::point_cloud_base_presentation::PlyFaceList& vistart::point_cloud_base_presentation::PlyFaceList::operator<<(fstream& file)
{
	auto face = make_shared<PlyFace>(face_description, file, this->file_encoding);
	this->faces->emplace_back(face);
	return *this;
}

vistart::point_cloud_base_presentation::PlyFaceList& vistart::point_cloud_base_presentation::PlyFaceList::operator<<(shared_ptr<PlyFace> const& vertex)
{
	this->faces->emplace_back(vertex);
	return *this;
}

vistart::point_cloud_base_presentation::PlyFaceList& vistart::point_cloud_base_presentation::PlyFaceList::operator<<(PlyFileEncoding const& fe)
{
	this->file_encoding = fe.GetDefinition();
	return *this;
}

bool vistart::point_cloud_base_presentation::PlyFaceList::read_element_face_names(fstream& file)
{
	string list_name;
	string list_type;
	string vertex_type;
	string vertex_name;
	file >> list_name >> list_type >> vertex_type >> vertex_name;
	if (list_type == "int8" || list_type == "char") {
		face_description.list_type = PlyPropertyType::INT8;
	}
	else if (list_type == "uint8" || list_type == "uchar") {
		face_description.list_type = PlyPropertyType::UINT8;
	}
	else if (list_type == "int16" || list_type == "short") {
		face_description.list_type = PlyPropertyType::INT16;
	}
	else if (list_type == "uint16" || list_type == "ushort") {
		face_description.list_type = PlyPropertyType::UINT16;
	}
	else if (list_type == "int32" || list_type == "int") {
		face_description.list_type = PlyPropertyType::INT32;
	}
	else if (list_type == "uint32" || list_type == "uint") {
		face_description.list_type = PlyPropertyType::UINT32;
	}
	else if (list_type == "float32" || list_type == "float") {
		face_description.list_type = PlyPropertyType::FLOAT32;
	}
	else if (list_type == "float64" || list_type == "double") {
		face_description.list_type = PlyPropertyType::FLOAT64;
	}
	
	if (vertex_type == "int8" || vertex_type == "char") {
		face_description.vertex_type = PlyPropertyType::INT8;
	}
	else if (vertex_type == "uint8" || vertex_type == "uchar") {
		face_description.vertex_type = PlyPropertyType::UINT8;
	}
	else if (vertex_type == "int16" || vertex_type == "short") {
		face_description.vertex_type = PlyPropertyType::INT16;
	}
	else if (vertex_type == "uint16" || vertex_type == "ushort") {
		face_description.vertex_type = PlyPropertyType::UINT16;
	}
	else if (vertex_type == "int32" || vertex_type == "int") {
		face_description.vertex_type = PlyPropertyType::INT32;
	}
	else if (vertex_type == "uint32" || vertex_type == "uint") {
		face_description.vertex_type = PlyPropertyType::UINT32;
	}
	else if (vertex_type == "float32" || vertex_type == "float") {
		face_description.vertex_type = PlyPropertyType::FLOAT32;
	}
	else if (vertex_type == "float64" || vertex_type == "double") {
		face_description.vertex_type = PlyPropertyType::FLOAT64;
	}
	return true;
}

void vistart::point_cloud_base_presentation::PlyFaceList::SetCountInHeader(unsigned int count)
{
	this->count_in_header = count;
}

unsigned vistart::point_cloud_base_presentation::PlyFaceList::GetCountInHeader() const
{
	return this->count_in_header;
}

std::shared_ptr<std::vector<std::shared_ptr<vistart::point_cloud_base_presentation::PlyFace>>> vistart::point_cloud_base_presentation::PlyFaceList::GetFaces() const
{
	return this->faces;
}
#endif
