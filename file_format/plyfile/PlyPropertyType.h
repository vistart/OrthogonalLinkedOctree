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
#ifndef __PLY_PROPERTY_TYPE_H__
#define __PLY_PROPERTY_TYPE_H__

#include <climits>
#include <fstream>
#include <type_traits>

#define IS_LITTLE_ENDIAN (1 == *(unsigned char *)&(const int){1})

namespace vistart
{
	namespace point_cloud_base_presentation
	{
		/*
		 This class is used to describe the property type appeared in ply file.
		 */
		class PlyPropertyType
		{
		public:
			/*
			 There are nine data types: NOTYPE, INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64.
			 */
			enum PropertyDataType { NOTYPE, INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64 };
			/*
			 Two supported endians: LITTLE, BIG.
			 */
			enum class Endian { LITTLE = 0, BIG = 1 };
			/*
			 The corresponding data types are: NOTYPE, INT8, UINT8, INT16, UINT16, INT32, UINT32, FLOAT32, FLOAT64.
			 */
			static const int PropertyDataTypeSize[9];

			/**
			 Swap the endian of the variable.
			 Any arithmetic types are supported.

			 @param s the variable to be swapped.
			 @return the variable which endian has been swapped.
			 */
			template <typename T>
			static T swap_endian(T& s)
			{
				static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

				union
				{
					T u;
					unsigned char u8[sizeof(T)];
				} source, dest;

				source.u = s;

				for (size_t k = 0; k < sizeof(T); k++)
					dest.u8[k] = source.u8[sizeof(T) - k - 1];

				return dest.u;
			}

			/**
			 Read binary little-endian property from specified file (stream).

			 The number of bytes read depends on the specified type.
			 For example, when the specified type is float, this method reads four bytes.

			 If the endian of the current architecture is not little-endian,
			 it will be adjusted to little-endian after reading the property.

			 @param file the file from which the property origin.
			 @return property value.
			 */
			template<typename T>
			static typename std::enable_if<std::is_arithmetic<T>::value, T>::type read_binary_le_property(std::fstream& file)
			{
				T p = 0;
				file.read(reinterpret_cast<char*>(&p), sizeof(T));
#ifdef IS_LITTLE_ENDIAN
				return p;
#else
				return swap_endian<T>(p);
#endif
			}

			/**
			 Read binary big-endian property from specified file (stream).

			 The number of bytes read depends on the specified type.
			 For example, when the specified type is float, this method reads four bytes.

			 If the endian of the current architecture is not big-endian,
			 it will be adjusted to big-endian after reading the property.

			 @param file the file from which the property origin.
			 @return  property value.
			 */
			template<typename T>
			static typename std::enable_if<std::is_arithmetic<T>::value, T>::type read_binary_be_property(std::fstream& file)
			{
				T p = 0;
				file.read(reinterpret_cast<char*>(&p), sizeof(T));
#ifdef IS_LITTLE_ENDIAN
				return swap_endian<T>(p);
#else
				return p;
#endif
			}

			/**
			 Check the endianness of the current architecture.

			 @return Endian::LITTLE or Endian::BIG.
			 */
			static Endian check_endian();

			template <int N>
			struct TypeSelector {
				using type = double;
			};
		};
	}
}
#endif
