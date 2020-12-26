/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_VERTEX_LIST_H__
#include "PlyVertexList.h"
#endif

#ifdef __PLY_VERTEX_LIST_H__
using namespace std;
#include <memory>

vistart::point_cloud_base_presentation::PlyVertexList::PlyVertexList()
{
	this->points = make_shared<vector<shared_ptr<PlyVertex>>>();
}

vistart::point_cloud_base_presentation::PlyVertexList::~PlyVertexList()
{
	this->points = nullptr;
}

vistart::point_cloud_base_presentation::PlyVertexList& vistart::point_cloud_base_presentation::PlyVertexList::operator<<(string const& str_vertex)
{
	auto vertex = make_shared<PlyVertex>(names, str_vertex);
	this->points->emplace_back(vertex);
	return *this;
}

vistart::point_cloud_base_presentation::PlyVertexList& vistart::point_cloud_base_presentation::PlyVertexList::operator<<(fstream& file)
{
	auto vertex = make_shared<PlyVertex>(names, file, this->file_encoding);
	this->points->emplace_back(vertex);
	return *this;
}

vistart::point_cloud_base_presentation::PlyVertexList& vistart::point_cloud_base_presentation::PlyVertexList::operator<<(shared_ptr<PlyVertex> const& vertex)
{
	this->points->emplace_back(vertex);
	return *this;
}

vistart::point_cloud_base_presentation::PlyVertexList& vistart::point_cloud_base_presentation::PlyVertexList::operator<<(PlyFileEncoding const& fe)
{
	this->file_encoding = fe.GetDefinition();
	return *this;
}

bool vistart::point_cloud_base_presentation::PlyVertexList::read_element_vertex_names(fstream& file)
{
	string type;
	string name;
	file >> type >> name;
	PlyVertex::VertexName vertex_name = { PlyVertex::PROPERTY_NONE, PlyPropertyType::NOTYPE };

	if (name == "x") {
		vertex_name.name = PlyVertex::PROPERTY_X;
	}
	else if (name == "y") {
		vertex_name.name = PlyVertex::PROPERTY_Y;
	}
	else if (name == "z") {
		vertex_name.name = PlyVertex::PROPERTY_Z;
	}
	else if (name == "red" || name == "r") {
		vertex_name.name = PlyVertex::PROPERTY_R;
	}
	else if (name == "green" || name == "g") {
		vertex_name.name = PlyVertex::PROPERTY_G;
	}
	else if (name == "blue" || name == "b") {
		vertex_name.name = PlyVertex::PROPERTY_B;
	}
	else if (name == "nx") {
		vertex_name.name = PlyVertex::PROPERTY_NX;
	}
	else if (name == "ny") {
		vertex_name.name = PlyVertex::PROPERTY_NY;
	}
	else if (name == "nz") {
		vertex_name.name = PlyVertex::PROPERTY_NZ;
	}
	else if (name == "alpha") {
		vertex_name.name = PlyVertex::PROPERTY_ALPHA;
	}
	else if (name == "confidence") {
		vertex_name.name = PlyVertex::PROPERTY_CONFIDENCE;
	}
	else if (name == "intensity") {
		vertex_name.name = PlyVertex::PROPERTY_INTENSITY;
	}

	if (type == "int8" || type == "char") {
		vertex_name.type = PlyPropertyType::INT8;
	}
	else if (type == "uint8" || type == "uchar") {
		vertex_name.type = PlyPropertyType::UINT8;
	}
	else if (type == "int16" || type == "short") {
		vertex_name.type = PlyPropertyType::INT16;
	}
	else if (type == "uint16" || type == "ushort") {
		vertex_name.type = PlyPropertyType::UINT16;
	}
	else if (type == "int32" || type == "int") {
		vertex_name.type = PlyPropertyType::INT32;
	}
	else if (type == "uint32" || type == "uint") {
		vertex_name.type = PlyPropertyType::UINT32;
	}
	else if (type == "float32" || type == "float") {
		vertex_name.type = PlyPropertyType::FLOAT32;
	}
	else if (type == "float64" || type == "double") {
		vertex_name.type = PlyPropertyType::FLOAT64;
	}

	this->names.emplace_back(vertex_name);
	return true;
}

void vistart::point_cloud_base_presentation::PlyVertexList::SetCountInHeader(unsigned int const count)
{
	this->count_in_header = count;
}

unsigned int vistart::point_cloud_base_presentation::PlyVertexList::GetCountInHeader() const
{
	return this->count_in_header;
}
std::shared_ptr<std::vector<std::shared_ptr<vistart::point_cloud_base_presentation::PlyVertex>>> vistart::point_cloud_base_presentation::PlyVertexList::GetPoints() const
{
	return this->points;
}
#endif
