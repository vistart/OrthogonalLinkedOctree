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
#ifndef __POINT_CLOUD_H__
#define __POINT_CLOUD_H__

#include "PointList.h"
#include "PointEdgeList.h"
#include "PointFaceList.h"

/*
 * This class is used to describe the Point Cloud.
 * There are a point list property for all points and a shared pointer to it.
 * The class that describes a point list can be the PointList class or its inherited class,
 * otherwise, the compilation fails.
 *
 * If you think that this class definition cannot meet your needs, you can inherit
 * the current class and implement it yourself according to your needs.
 *
 * If you need to implement inherited classes, be sure to follow the following specifications:
 * 1. Define the point list property that holds all points and make shared pointer point to it.
 * 2. Initialize the shared pointer of above point list property in Constructor.
 * 3. Make the point list to nullptr in Destructor.
*/
namespace vistart
{
	namespace point_cloud_base_presentation
	{

        template <
            typename TPointList,
            typename TPoint,
            typename TPointEdgeList,
            typename TPointEdge,
            typename TPointFaceList,
            typename TPointFace,
            typename = typename std::enable_if<std::is_base_of<PointList<TPoint>, TPointList>::value&&
            std::is_base_of<PointEdgeList<TPointEdge>, TPointEdgeList>::value&&
            std::is_base_of<PointFaceList<TPointFace>, TPointFaceList>::value
            >::type
        >
            class PointCloud
        {
        public:
            PointCloud() {
                this->point_list = std::make_shared<TPointList>();
                this->point_edge_list = std::make_shared<TPointEdgeList>();
                this->point_face_list = std::make_shared<TPointFaceList>();
            }
            PointCloud(const PointCloud&) = default;
            PointCloud& operator=(const PointCloud&) = default;
            PointCloud(PointCloud&&) = default;
            PointCloud& operator=(PointCloud&&) = default;
            virtual ~PointCloud() {
                this->point_face_list = nullptr;
                this->point_edge_list = nullptr;
                this->point_list = nullptr;
            }
            virtual std::shared_ptr<TPointList> GetPointList() {
                return this->point_list;
            }
            virtual std::shared_ptr<TPointEdgeList> GetPointEdgeList() {
                return this->point_edge_list;
            }
            virtual std::shared_ptr<TPointFaceList> GetPointFaceList() {
                return this->point_face_list;
            }
        protected:
            std::shared_ptr<TPointList> point_list;
            std::shared_ptr<TPointEdgeList> point_edge_list;
            std::shared_ptr<TPointFaceList> point_face_list;
        };
	}
}
#endif
