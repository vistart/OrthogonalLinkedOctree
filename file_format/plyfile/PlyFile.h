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

#ifndef __PLY_FILE_H__
#define __PLY_FILE_H__

#include "PlyFileEncoding.h"
#include "PlyVertexList.h"
#include "PlyFaceList.h"
#include "PlyEdgeList.h"
#include "PlyCommentList.h"
#include <fstream>
#include <string>

#include "../point_cloud_base_presentation/PointCloud.h"
namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 This class is used to describe the ply file.
		 */
		class PlyFile : public PointCloud<PlyVertexList, PlyVertex, PlyEdgeList, PlyEdge, PlyFaceList, PlyFace, PlyFile>
		{
		public:
#pragma region Constructor & Destructor
			/**
			 *
			 */
			explicit PlyFile(std::string const& file_path);
			virtual ~PlyFile();
#pragma endregion

#pragma region File Format
			[[nodiscard]] std::string get_file_format() const;
#pragma endregion

#pragma region File Encoding
			std::shared_ptr<PlyFileEncoding> FileEncoding;
#pragma endregion

#pragma region Comment
			std::shared_ptr<PlyCommentList> CommentList;
#pragma endregion

#pragma region Vertex
			std::shared_ptr<PlyVertexList> GetPointList() override;
#pragma endregion

#pragma region Face
			std::shared_ptr<PlyFaceList> GetPointFaceList() override;
#pragma endregion

#pragma region Edge
			std::shared_ptr<PlyEdgeList> GetPointEdgeList() override;
#pragma endregion

			bool GetIsValid() const;

		protected:
			/* The file currently being accessed. */
			std::fstream file;
			/* The filename currently being accessed. */
			std::string filename;
			/* Indicates whether the file was read correctly. */
			bool valid = false;
			/**
			 Open the file.

			 @param file_path the filename to be opened.
			 @return bool true if the file was opened successfully.
			 */
			bool open(std::string const& file_path);
			/* Supported header tags */
			enum Tag { PLY, FORMAT, COMMENT, ELEMENT, PROPERTY, END_HEADER };
			/**
			 Read from ply file.
			 The file format only supports ply, and the encoding format can be ASCII
			 and binary (both big and little endian).
			 To use this method, you need to use "fstream" to represent an open file
			 stream.

			 @param file the file to be read.
			 @return bool true if the file was read successfully.
			 */
			bool read(std::fstream& file);
			/**
			 * Read header from ply file.
			 * This method resets the file pointer to the beginning because the file
			 * header is at the beginning of the file.
			 *
			 * Note: It is not recommended to call this method directly unless you know
			 * the consequences of doing so.
			 *
			 * @param file the file to be read.
			 * @return bool true if the file was read successfully.
			 */
			bool read_header(std::fstream& file);
			/**
			 * This method starts at the position pointed to by the incoming file
			 * stream parameter, and determines the amount of data to be read according
			 *
			 * Note: It is not recommended to call this method directly unless you know
			 * the consequences of doing so. If you want to call this method separately,
			 * you need to make sure that the file pointer points to the appropriate
			 * location yourself.
			 *
			 * @param file the file to be read.
			 * @return bool true if the file was read successfully.
			 */
			bool read_body(std::fstream& file);

#pragma region File Format
			enum FileFormatType { FILE_FORMAT_PLY };
			int file_format = FILE_FORMAT_PLY;
			/**
			 * Set file format. The only supported format is "ply".
			 *
			 * False returned if you pass another string.
			 *
			 * @param file_format File format string.
			 * @return true only "ply" passed.
			 */
			bool set_file_format(std::string const& file_format);
#pragma endregion

#pragma region File Encoding
			/**
			 *
			 * @param tag Tag string.
			 * @param file File stream.
			 * @return true if file encoding read.
			 */
			bool read_file_encoding(std::string const& tag, std::fstream& file);
#pragma endregion

#pragma region Comment
			/**
			 * When the tag is "comment", everything after this tag in the current line is a comment.
			 *
			 * @param tag Tag string.
			 * @param file File stream.
			 * @return true if comments read.
			 */
			bool read_comment(std::string const& tag, std::fstream& file) const;
#pragma endregion

#pragma region Vertex
			/**
			 * Read Vertex Name from ply file.
			 * This method is called when the tag of a line is "vertex". Therefore, the
			 * file pointer should point to the content after "vertex".
			 *
			 * @param file the file to be read.
			 * @return bool true if the file was read successfully.
			 */
			bool read_element_vertex_names(std::fstream&) const;
			/**
			 * Read Vertex Encoding from ply file.
			 * This method is called before reading vertex to determine the specific
			 * file encoding.
			 *
			 * @param file_encoding the file encoding.
			 * @return true if the file was read successfully.
			 */
			bool read_element_vertex_encoding(PlyFileEncoding const& file_encoding) const;
			/**
			 * Read Vertex from ply file.
			 * You need to determine the file encoding and number of points before
			 * calling this method.
			 * This method determines the meaning of each property based on vertex_names.
			 *
			 * @param f the file to be read.
			 * @return bool true if the file was read successfully.
			 */
			bool read_element_vertex(std::fstream& f) const;
			// std::shared_ptr<PlyVertexList> point_list;
#pragma endregion

#pragma region Face
	/**
	 * Read Face Name from ply file.
	 * This method is called when the tag of a line is "face". Therefore, the
	 * file pointer should point to the content after "face".
	 *
	 * @param file the file to be read.
	 * @return bool true if the file was read successfully.
	 */
			bool read_element_face_names(std::fstream&) const;
			bool read_element_face_encoding(PlyFileEncoding const&) const;
			/**
			 * Read Face from ply file.
			 * You need to determine the file encoding and number of points before
			 * calling this method.
			 * This method determines the meaning of each property based on face list.
			 *
			 * @param file the file to be read.
			 * @return bool true if the file was read successfully.
			 * @todo Implement this method.
			 */
			bool read_element_face(std::fstream&) const;
#pragma endregion

#pragma region Edge
			/**
			 * Read Edge Name from ply file.
			 * This method is called when the tag of a line is "edge". Therefore, the
			 * file pointer should point to the content after "edge".
			 *
			 * @param file the file to be read.
			 * @return true if the file was read successfully.
			 */
			bool read_element_edge_names(std::fstream& file) const;
			bool read_element_edge_encoding(PlyFileEncoding const&) const;
			/**
			 * Read Edge from ply file.
			 * You need to determine the file encoding and number of points before
			 * calling this method.
			 * This method determines the meaning of each property based on edge list.
			 *
			 * @param file the file to be read.
			 * @return bool true if the file was read successfully.
			 */
			bool read_element_edge(std::fstream& file) const;
#pragma endregion

#pragma region User-Defined Elements
			/**
			 * @todo Implement this method.
			 */
			bool read_element_user_defined_names(std::fstream&) const;
			/**
			 * Read User-defined elements from ply file.
			 * You need to determine the file encoding and number of points before
			 * calling this method.
			 * This method determines the meaning of each property based on user-defined list.
			 *
			 * @param file the file to be read.
			 * @return bool true if the file was read successfully.
			 */
			bool read_element_user_defined(std::fstream& file);
#pragma endregion
		};
	}
}

#endif