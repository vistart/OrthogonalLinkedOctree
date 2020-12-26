/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __PLY_FILE_H__
#include "PlyFile.h"
#endif

#ifdef __PLY_FILE_H__
#include <iostream>
#include <iomanip>
#include <algorithm>

#ifdef _DEBUG
#include <chrono>
#endif

using namespace std;

#pragma region Constructor & Destructor
/*
 * Summary: Instantiate the current object from the ply file.
 * Parameters:
 *     std::string file_path: the file path to store the ply data.
 */
vistart::point_cloud_base_presentation::PlyFile::PlyFile(string const& file_path)
{
	this->filename = file_path;
	this->FileEncoding = make_shared<PlyFileEncoding>();
	this->CommentList = make_shared<PlyCommentList>();
	this->point_list = make_shared<PlyVertexList>();
	this->point_edge_list = make_shared<PlyEdgeList>();
	this->point_face_list = make_shared<PlyFaceList>();
	open(this->filename);
	if (read(this->file))
		this->valid = true;
}

vistart::point_cloud_base_presentation::PlyFile::~PlyFile()
{
	if (this->file.is_open()) {
		this->file.close();
	}
	this->point_face_list = nullptr;
	this->point_edge_list = nullptr;
	this->point_list = nullptr;
	this->CommentList = nullptr;
	this->FileEncoding = nullptr;
	this->filename = "";
}

bool vistart::point_cloud_base_presentation::PlyFile::GetIsValid() const
{
	return this->valid;
}
#pragma endregion

#pragma region File Format
string vistart::point_cloud_base_presentation::PlyFile::get_file_format() const
{
	if (this->file_format == FILE_FORMAT_PLY)
	{
		return "ply";
	}
	return "unknown type!";
}

bool vistart::point_cloud_base_presentation::PlyFile::set_file_format(string const& ff)
{
	if (ff == "ply") {
		this->file_format = FILE_FORMAT_PLY;
		return true;
	}
	return false;
}
#pragma endregion

#pragma region File Encoding
bool vistart::point_cloud_base_presentation::PlyFile::read_file_encoding(string const& tag, fstream& f)
{
	if (tag != string("format"))
		return false;
	auto& encoding = this->FileEncoding;
	*encoding << f;
	return true;
}
#pragma endregion

#pragma region Comment

bool vistart::point_cloud_base_presentation::PlyFile::read_comment(string const& tag, fstream& f) const
{
	if (tag != string(PLY_TAG_COMMENT))
		return false;

	string comment;
	getline(f, comment);
	*this->CommentList << comment;
	return true;
}
#pragma endregion

bool vistart::point_cloud_base_presentation::PlyFile::open(string const& file_path)
{
	if (this->file.is_open()) {
		this->file.close();
	}
	//std::cout << file_path << std::endl;
	this->file.open(file_path, ios::in | ios::binary);
	return this->file.good();
}

#pragma region Vertex
bool vistart::point_cloud_base_presentation::PlyFile::read_element_vertex_names(fstream& f) const
{
	this->point_list->read_element_vertex_names(f);
	PlyVertex::VertexName const back = this->point_list->names.back();
#ifdef _DEBUG
	cout << "Property: " << back.name << " | " << back.type << endl;
#endif
	return true;
}

bool vistart::point_cloud_base_presentation::PlyFile::read_element_vertex_encoding(PlyFileEncoding const& file_encoding) const
{
	auto& vertex_list = *this->point_list;
	vertex_list << file_encoding;
	return true;
}

bool vistart::point_cloud_base_presentation::PlyFile::read_element_vertex(fstream& f) const
{
	auto& vertex_list = *this->point_list;
	vertex_list << f;
	return true;
}

shared_ptr<vistart::point_cloud_base_presentation::PlyVertexList> vistart::point_cloud_base_presentation::PlyFile::GetPointList()
{
	return this->point_list;
}
#pragma endregion

#pragma region Face
bool vistart::point_cloud_base_presentation::PlyFile::read_element_face_names(fstream& f) const
{
	this->point_face_list->read_element_face_names(f);
	const auto& fd = this->point_face_list->face_description;
#ifdef _DEBUG
	cout << "List name: " << fd.list_name << "\tlist type:" << fd.list_type << "\tvertices index type:" << fd.vertex_type << "\tvertices index name: " << fd.vertex_name << endl;
#endif
	return true;
}
bool vistart::point_cloud_base_presentation::PlyFile::read_element_face_encoding(PlyFileEncoding const& file_encoding) const
{
	auto& face_list = *this->point_face_list;
	face_list << file_encoding;
	return true;
}
bool vistart::point_cloud_base_presentation::PlyFile::read_element_face(fstream& f) const
{
	auto& face_list = *this->point_face_list;
	face_list << f;
	return true;
}

shared_ptr<vistart::point_cloud_base_presentation::PlyFaceList> vistart::point_cloud_base_presentation::PlyFile::GetPointFaceList()
{
	return this->point_face_list;
}
#pragma endregion

#pragma region Edge
bool vistart::point_cloud_base_presentation::PlyFile::read_element_edge_names(fstream& f) const
{
	this->point_edge_list->read_element_edge_names(f);
	const auto& name = this->point_edge_list->names.back();
#ifdef _DEBUG
	cout << "Property: " << name.name << " | " << name.type << endl;
#endif
	return true;
}
bool vistart::point_cloud_base_presentation::PlyFile::read_element_edge_encoding(PlyFileEncoding const& file_encoding) const
{
	auto& edge_list = *this->point_edge_list;
	edge_list << file_encoding;
	return true;
}
bool vistart::point_cloud_base_presentation::PlyFile::read_element_edge(fstream& f) const
{
	auto& edge_list = *this->point_edge_list;
	edge_list << f;
	return true;
}

std::shared_ptr<vistart::point_cloud_base_presentation::PlyEdgeList> vistart::point_cloud_base_presentation::PlyFile::GetPointEdgeList()
{
	return this->point_edge_list;
}

#pragma endregion

#pragma region User-Defined Elements
bool vistart::point_cloud_base_presentation::PlyFile::read_element_user_defined_names(fstream& f) const
{
	return true;
}
bool vistart::point_cloud_base_presentation::PlyFile::read_element_user_defined(fstream& f)
{
	return false;
}
#pragma endregion

bool vistart::point_cloud_base_presentation::PlyFile::read_header(fstream& f)
{
	unsigned int element_count = 0;
	string buffer;
	enum ELEMENTS { NONE, VERTEX, FACE, EDGE, USER_DEFINED };
	int current_elements = NONE;

	// Regardless of the status of the current file, it searches from the beginning.
	file.seekg(0, ios::beg);

    // Reading the header of a ply file.
	while (f >> buffer)
	{
		// Regardless of the case of the current word, it is converted to lower case for comparison.
		transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

		// If `buffer` equals to "property", the content after it is regarded as the property name.
		if (buffer.c_str() == string("property")) {
			// There are three default property names: vertex, face and edge.
			if (current_elements == VERTEX) {
				read_element_vertex_names(f);
				continue;
			}
			if (current_elements == FACE) {
				read_element_face_names(f);
				continue;
			}
			if (current_elements == EDGE) {
				read_element_edge_names(f);
				continue;
			}
			// All others are user-defined.
			if (current_elements == USER_DEFINED) {
				read_element_user_defined_names(f);
				continue;
			}
		}

		current_elements = NONE;

		// If `buffer` equals to "ply", it indicates that the current file format is ply.
		if (buffer.c_str() == string("ply")) {
			cout << "PLY" << endl;
			this->set_file_format("ply");
			continue;
		}


		// If `buffer` equals to "format", it indicates that the following content is format and encoding.
		if (read_file_encoding(buffer.c_str(), f)) {
#ifdef _DEBUG
			cout << "FORMAT: " << (*this->FileEncoding).Encoding() << " VERSION:" << (*this->FileEncoding).Version() << endl;
#endif
			continue;
		}

		// If `buffer` equals to "comment", it indicates that the following content is comment.
		if (read_comment(buffer.c_str(), f)) {
#ifdef _DEBUG
			auto comments = *CommentList->getComments();
			for (const auto& comment :comments)
			{
				cout << "Comment: " << comment << endl;
			}
#endif
			continue;
		}

		// If `buffer` equals to "element", it indicates that the following content is element names.
		if (buffer.c_str() == string("element")) {
			string element_name;
			f >> element_name >> element_count;

			if (element_name == "vertex") {
				current_elements = VERTEX;
				auto point_list = this->GetPointList();
				point_list->SetCountInHeader(element_count);
#ifdef _DEBUG
				cout << "Element: " << element_name << point_list->GetCountInHeader() << endl;
#endif
				continue;
			}

			if (element_name == "face") {
				current_elements = FACE;
				auto face_list = this->GetPointFaceList();
				face_list->SetCountInHeader(element_count);
				continue;
			}

			if (element_name == "edge") {
				current_elements = EDGE;
				auto edge_list = this->GetPointEdgeList();
				edge_list->SetCountInHeader(element_count);
				continue;
			}
			continue;
		}

		if (buffer.c_str() == string("end_header")) {
#ifdef _DEBUG
			cout << "END of HEADER" << endl;
#endif
			break;
		}
	}
	return true;
}

bool vistart::point_cloud_base_presentation::PlyFile::read_body(fstream& f)
{
	f.get(); // throw out the last character ('\n').
	read_element_vertex_encoding(*this->FileEncoding);
	const auto vertex_count_in_header = this->GetPointList()->GetCountInHeader();
	for (unsigned int i = 0; i < vertex_count_in_header; i++)
	{
#ifdef _DEBUG
		// cout << "file pointer: " << file.tellg() << endl;
#endif
		read_element_vertex(f);
	}

	read_element_face_encoding(*this->FileEncoding);
	const auto face_count_in_header = this->GetPointFaceList()->GetCountInHeader();
	for (unsigned int i = 0; i < face_count_in_header; i++)
	{
#ifdef _DEBUG
		//cout << "file pointer: " << file.tellg() << endl;
#endif
		read_element_face(f);
	}
#ifdef _DEBUG
	if (this->GetPointFaceList()->GetFaces()->empty())
	{
		cout << "Empty face." << endl;
	} else cout << "The last face: " << *this->GetPointFaceList()->GetFaces()->back() << endl;
#endif

	read_element_edge_encoding(*this->FileEncoding);
	const auto edge_count_in_header = this->GetPointEdgeList()->GetCountInHeader();
	for (unsigned int i = 0; i < edge_count_in_header; i++)
	{
#ifdef _DEBUG
		//cout << "file pointer: " << file.tellg() << endl;
#endif
		read_element_edge(f);
	}
	return true;
}


bool vistart::point_cloud_base_presentation::PlyFile::read(fstream& f)
{
#ifdef _DEBUG
	const chrono::steady_clock::time_point time_start = chrono::steady_clock::now();
#endif
	if (!this->read_header(f)) {
		return false;
	}
#ifdef _DEBUG
	const chrono::steady_clock::time_point time_end_read_header = chrono::steady_clock::now();
	const chrono::duration<double> duration_read_header = chrono::duration_cast<chrono::duration<double>>(time_end_read_header - time_start);
	cout << "Time elapsed of reading header: " << duration_read_header.count() << " s" << endl;
#endif
	if (!this->read_body(f)) {
		return false;
	}
#ifdef _DEBUG
	const chrono::steady_clock::time_point time_end_read_body = chrono::steady_clock::now();
	const chrono::duration<double> duration_read_body = chrono::duration_cast<chrono::duration<double>>(time_end_read_body - time_end_read_header);
	cout << "Time elapsed of reading body: " << duration_read_body.count() << " s" << endl;
#endif
	return true;
}

#endif