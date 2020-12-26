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

#ifndef __POINT_FACE_LIST_H__
#define __POINT_FACE_LIST_H__
#include "PointFace.h"
#include <memory>
#include <type_traits>
#include <vector>
namespace vistart
{
	namespace point_cloud_base_presentation
	{
		template <typename T, typename = typename std::enable_if<std::is_base_of<PointFace, T>::value, T>::type>
		class PointFaceList
		{
		public:
			PointFaceList()
			{
				this->faces = std::make_shared<std::vector<std::shared_ptr<T>>>();
			}
			PointFaceList(const PointFaceList<T>& f) = delete;
			PointFaceList& operator=(const PointFaceList<T>& f) = delete;

			virtual ~PointFaceList()
			{
				this->faces = nullptr;
			}
			/*
			virtual void SetFaces(std::shared_ptr<std::vector<std::shared_ptr<T>>> f) const noexcept
			{
				this->faces = f;
			}*/
			[[nodiscard]] virtual std::shared_ptr<std::vector<std::shared_ptr<T>>> GetFaces() const {
				return this->faces;
			}
		protected:
			std::shared_ptr<std::vector<std::shared_ptr<T>>> faces;
		};
	}
}
#endif
