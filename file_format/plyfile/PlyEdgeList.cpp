/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_EDGE_LIST_H__
#include "PlyEdgeList.h"
#endif

#ifdef __PLY_EDGE_LIST_H__
using namespace std;
vistart::point_cloud_base_presentation::PlyEdgeList::PlyEdgeList()
{
	this->edges = make_shared<vector<shared_ptr<PlyEdge>>>();
}
vistart::point_cloud_base_presentation::PlyEdgeList::~PlyEdgeList()
{
	this->edges = nullptr;
}

vistart::point_cloud_base_presentation::PlyEdgeList& vistart::point_cloud_base_presentation::PlyEdgeList::operator<<(std::string const& str_edge)
{
	auto edge = std::make_shared<PlyEdge>(names, str_edge);
	this->edges->emplace_back(edge);
	return *this;
}

vistart::point_cloud_base_presentation::PlyEdgeList& vistart::point_cloud_base_presentation::PlyEdgeList::operator<<(std::fstream& file)
{
	auto edge = std::make_shared<PlyEdge>(names, file, file_encoding);
	this->edges->emplace_back(edge);
	return *this;
}

vistart::point_cloud_base_presentation::PlyEdgeList& vistart::point_cloud_base_presentation::PlyEdgeList::operator<<(std::shared_ptr<PlyEdge> const& edge)
{
	this->edges->emplace_back(edge);
	return *this;
}

vistart::point_cloud_base_presentation::PlyEdgeList& vistart::point_cloud_base_presentation::PlyEdgeList::operator<<(PlyFileEncoding const& fe)
{
	this->file_encoding = fe.GetDefinition();
	return *this;
}
bool vistart::point_cloud_base_presentation::PlyEdgeList::read_element_edge_names(std::fstream& f)
{
	string type;
	string name;
	f >> type >> name;
	PlyEdge::EdgeName edge_name = { PlyEdge::PROPERTY_NONE, PlyPropertyType::NOTYPE };

	if (name == "vertex1")
	{
		edge_name.name = PlyEdge::PROPERTY_VERTEX1;
	} else if (name == "vertex2")
	{
		edge_name.name = PlyEdge::PROPERTY_VERTEX2;
	} else if (name == "red" || name == "r")
	{
		edge_name.name = PlyEdge::PROPERTY_RED;
	} else if (name == "green" || name == "g")
	{
		edge_name.name = PlyEdge::PROPERTY_GREEN;
	} else if (name == "blue" || name == "b")
	{
		edge_name.name = PlyEdge::PROPERTY_BLUE;
	}

	if (type == "int8" || type == "char") {
		edge_name.type = PlyPropertyType::INT8;
	}
	else if (type == "uint8" || type == "uchar") {
		edge_name.type = PlyPropertyType::UINT8;
	}
	else if (type == "int16" || type == "short") {
		edge_name.type = PlyPropertyType::INT16;
	}
	else if (type == "uint16" || type == "ushort") {
		edge_name.type = PlyPropertyType::UINT16;
	}
	else if (type == "int32" || type == "int") {
		edge_name.type = PlyPropertyType::INT32;
	}
	else if (type == "uint32" || type == "uint") {
		edge_name.type = PlyPropertyType::UINT32;
	}
	else if (type == "float32" || type == "float") {
		edge_name.type = PlyPropertyType::FLOAT32;
	}
	else if (type == "float64" || type == "double") {
		edge_name.type = PlyPropertyType::FLOAT64;
	}
	
	this->names.emplace_back(edge_name);
	return true;
}
void vistart::point_cloud_base_presentation::PlyEdgeList::SetCountInHeader(unsigned int count)
{
	this->count_in_header = count;
}
unsigned int vistart::point_cloud_base_presentation::PlyEdgeList::GetCountInHeader() const
{
	return this->count_in_header;
}
std::shared_ptr<std::vector<std::shared_ptr<vistart::point_cloud_base_presentation::PlyEdge>>> vistart::point_cloud_base_presentation::PlyEdgeList::GetEdges() const
{
	return this->edges;
}
#endif
