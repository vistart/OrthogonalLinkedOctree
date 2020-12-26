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

#ifndef __PLY_FILE_ENCODING_H__
#define __PLY_FILE_ENCODING_H__

constexpr auto PLY_TAG_FILE_ENCODING = "format";
constexpr auto PLY_FILE_ENCODING_ASCII = "ascii";
constexpr auto PLY_FILE_BINARY_BIG_ENDIAN = "binary_big_endian";
constexpr auto PLY_FILE_BINARY_LITTLE_ENDIAN = "binary_little_endian";

#include "PlyPropertyType.h"
#include <string>
#include <fstream>
namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 This class is used to describe the file encoding of ply file.
		 */
		class PlyFileEncoding
		{
		public:
			/*
			 Check and set endian of current situation.
			 Set the default encoding type as ASCII, and it's version is 1.0.
			 */
			PlyFileEncoding();
			~PlyFileEncoding() = default;
			enum FileEncodingType { FILE_ENCODING_ASCII, FILE_ENCODING_BINARY_BIG_ENDIAN, FILE_ENCODING_BINARY_LITTLE_ENDIAN };
			struct FileEncoding
			{
				int type = FILE_ENCODING_ASCII;
				float version = 1.0;
			};

			/*
			 Set the file encoding from the file stream.

			 @param file the file to be read the file encoding.
			 @return self
			 */
			PlyFileEncoding& operator<<(std::fstream& file);

			/*
			 Set the file encoding according to the giving FileEncoding value.

			 @param file_encoding target file encoding.
			 @return self
			 */
			PlyFileEncoding& operator<<(FileEncoding const& file_encoding);

			/*
			 Regard the string value as the encoding type.

			 @param format Format.
			 @return self
			 */
			PlyFileEncoding& operator<<(std::string const& format);

			/*
			 Regard the float value as the version of the encoding type.

			 @param version encoding version.
			 @return self
			 */
			PlyFileEncoding& operator<<(float version);
			[[nodiscard]] FileEncoding GetDefinition() const&;

			/*
			 Get the encoding title.

			 @return string: "ascii", "binary_big_endian" or " binary_little_endian".
			 */
			[[nodiscard]] std::string Encoding() const;

			/*
			 Set the encoding type.

			 @param encoding encoding type.
			 @return selfW
			 */
			PlyFileEncoding& Encoding(std::string const& encoding);

			/*
			 Get the version.

			 @return version.
			 */
			[[nodiscard]] float Version() const;

			/*
			 Set the version of file encoding.

			 @param version Version.
			 @return self
			 */
			PlyFileEncoding& Version(float version);

			/*
			 Check whether the current file encoding is equal to the specified one.

			 @param object object to compare.
			 @return true if equal.
			 */
			bool operator==(PlyFileEncoding const& object) const;

			/*
			 Check whether the current file encoding is not equal to the specified one.

			 @param object object to compare.
			 @return true if not equal.
			 */
			bool operator!=(PlyFileEncoding const& object) const;

			/*
			 Check whether the current file encoding is equal to the specified one.

			 @param object object to compare.
			 @return true if equal.
			 */
			bool operator==(FileEncoding const& object) const;

			/*
			 Check whether the current file encoding is not equal to the specified one.

			 @param object object to compare.
			 @return true if not equal.
			 */
			bool operator!=(FileEncoding const& object) const;

			/*
			 The attribute containing the endian of current situation.
			 The default value is related to the current architecture and is determined
			 at compile time. This value should be specified during instantiation, and
			 it is strongly not recommended to modify it thereafter.
			 */
			PlyPropertyType::Endian endian;
		protected:
			FileEncoding file_encoding;
		};
	}
}

#endif