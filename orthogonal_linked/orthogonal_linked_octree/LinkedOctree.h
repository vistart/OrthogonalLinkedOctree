/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/

#include <type_traits>

#include "../../file_format/point_cloud_base_presentation/PointList.h"
#include "../orthogonal_linked_list/LinkedCoordinate.h"
#include "OctreeNode.h"

namespace vistart
{
	namespace orthogonal_linked_octree
	{
		template<class TPointList,
				 class TPoint,
				 typename = typename std::enable_if<std::is_base_of<point_cloud_base_presentation::PointList<TPoint>, TPointList>::value, TPointList>::type>
		class LinkedOctree : orthogonal_linked_list::Coordinate<3, OctreeNode>
		{
			LinkedOctree() = default;
		};
	}
}