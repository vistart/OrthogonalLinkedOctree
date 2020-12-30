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

#ifndef __PLY_VERTEX_H__
#define __PLY_VERTEX_H__

#include <iomanip>

#include "PlyFileEncoding.h"
#include <vector>
#include <sstream>

#include "../point_cloud_base_presentation/Point.h"

namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 This class is used to describe a vertex in ply format.
		 Compared with the base class Point, this class adds methods related to the ply file format.
		 */
		class PlyVertex : public Point
		{
		public:
			/*
			 NAME: PROPERTY_NONE, PROPERTY_X, PROPERTY_Y, PROPERTY_Z, PROPERTY_R, PROPERTY_G, PROPERTY_B,
				   PROPERTY_NX, PROPERTY_NY, PROPERTY_NZ, PROPERTY_ALPHA, PROPERTY_CONFIDENCE, PROPERTY_INTENSITY.
				   (originated from PlyVertex::PropertyNames)
			 TYPE: NOTYPE, INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64.
				   (originated from PlyPropertyType::PlyPropertyDataType)
			 */
			typedef struct {
				int name;
				int type;
			} VertexName;
			/*
			 Initialize a vertex, which is located at the origin, with the color is black,
			 the ALPHA value is 255, the confidence is 1, and the intensity is 0.5.
			 */
			PlyVertex() = default;

			/*
			 Initialize a vertex based on the string content.
			 The string should contain all properties describing the vertex. The order in which
			 each property appears follows the order described by the names variable(first parameter).
			 Each property value is separated by a space. This method will automatically convert
			 the current property content to the specified type.
			 This method is usually used for files that can be displayed with characters.

			 Note: The default values used when the following properties are not specified:
			 X: 0, Y: 0, Z: 0, R: 0, G: 0, B: 0, ALPHA: 255, CONFIDENCE: 1, INTENSIFY: 0.5.

			 @param vector<VertexName> const&: List of property names. The order of property names
			 determines the content type of the sub-string.
			 @param string const&: A string describing all property values of a vertex.
			 */
			PlyVertex(std::vector<VertexName> const&, std::string const&);

			/*
			 Initialize a vertex based on file stream and its encoding.
			 The specific read content starts from the current position of the file stream.
			 According to different file encodings, this method adopts different construction methods:

			 - FILE_ENCODING_ASCII: If the file is encoded with displayable characters,
			   this parameter should be used. This method will read each data in turn according
			   to the first parameter (property name list) with spaces, line breaks, tabs, etc.
			   as separators, and convert them to the corresponding properties.

			 - FILE_ENCODING_BINARY_BIG_ENDIAN: If the file is encoded with binary in big-endian,
			   this parameter should be used. This method will read the data of the corresponding
			   length in turn according to the first parameter (property name list),
			   and convert them to the corresponding properties.

			 - FILE_ENCODING_BINARY_LITTLE_ENDIAN: If the file is encoded with binary in little-endian,
			   this parameter should be used. This method will read the data of the corresponding
			   length in turn according to the first parameter (property name list),
			   and convert them to the corresponding properties.

			 @param names List of property names. The order of property names
			 determines the content type of the sub-string.
			 @param file the file from which the property origin.
			 @param file_encoding The encoding of the vertex property of this file.
			 */
			PlyVertex(std::vector<VertexName> const& names, std::fstream& file, PlyFileEncoding::FileEncoding const& file_encoding);

			/*
			 Initialize a vertex based on specified X,Y,Z,R,G,B.
			 the ALPHA value is 255, the confidence is 1, and the intensity is 0.5.

			 @param X
			 @param Y
			 @param Z
			 @param R
			 @param G
			 @param B
			 */
			PlyVertex(double X, double Y, double Z, unsigned char R, unsigned char G, unsigned char B);
			virtual ~PlyVertex() = default;
			enum PropertyNames {
				PROPERTY_NONE,
				PROPERTY_X, PROPERTY_Y, PROPERTY_Z,
				PROPERTY_R, PROPERTY_G, PROPERTY_B,
				PROPERTY_NX, PROPERTY_NY, PROPERTY_NZ,
				PROPERTY_ALPHA, PROPERTY_CONFIDENCE, PROPERTY_INTENSITY
			};

			/*
			 Pass location of vertex to the output stream.
			 The output format is: (X, Y, Z)

			 @param stream The stream of vertex to be output.
			 @param vertex Vertex to output.
			 @return The stream that has been passed with the vertex.
			 */
			friend std::ostream& operator<<(std::ostream& stream, PlyVertex const& vertex)
			{
				stream << "(" << std::setprecision(10) << vertex.__X << "," << std::setprecision(10) << vertex.__Y << "," << std::setprecision(10) << vertex.__Z << ")";
				return stream;
			}
		};
	}
}

#endif