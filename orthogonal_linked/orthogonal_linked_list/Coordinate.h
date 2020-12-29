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
#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include <memory>
#include <vector>
#include <unordered_map>
#include "CoordinateDimensionMismatchException.h"

namespace vistart
{
	namespace orthogonal_linked_list
	{
		/**
		 * 坐标。
		 * 1. 首先要确定参数 D。该参数指明正交链表有几个维度。最少是2。但不应当超过8，否则可能会产生性能问题。
		 * 2. 所有维度的范围均为D。即形状为平方型(D=2)、立方体(D=3)或超立方体(D>3)。
		 * 3. 不论维度为多少，内部存储均使用无序映射(unordered_map)。无序映射索引值和多维坐标之间的转换公式参见
		 *    struct Hash 的描述。
		   unordered_map 类型的索引范围上限为 2 的 64 次方。但这并不代表实际存储容量。
		 * 如果当前维度为2，即平面正交坐标系，则支持的坐标范围为[0..2147483647, 0..2147483647]；
		 * 如果当前维度为3，即平面立体正交坐标系，则支持的坐标范围为[0..2097151, 0..2097151, 0..2097151]；
		 * 以此类推，
		 * 如果当前维度为8，即八维超立方正交坐标系，则支持的坐标范围为[0..256, 0..256, ... , 0..256]，
		 * 即不论分为多少个维度，所有维度的长度均相等。在此基础上，所有维度表示范围总和不超过 2 的 64 次方，且每个维度的长度也是 2 的整数次幂。
		 * 超过此范围也可以继续存储，但考虑到相同键值存储在 unordered_map 中会产生冲突，而处理冲突则会产生额外时间消耗。具体处理规则参见 struct Hash 说明。
	     * 
		 * 4. 十字链表指向的类型 T。虽然 T 可以是任意类型，但实际只存储指向该类型的共享指针。
		 *     因此使用当前正交链表类保存标量类型在时间和空间上都不划算。
		 *
		 * TODO:
		 * 1. 尝试用模板偏特化限制此参数范围。
		 * 2. 补充说明
		 *
		 * @param D 维度数。大于等于2的正整数。但最好不要大于16。
		 * @param T 元素类型。为了避免移动、复制元素，实际实现为指向该元素的共享指针（shared_ptr）。
		 */
		template<unsigned char D, typename T>
		class Coordinate
		{
		public:
			Coordinate() = default;

			virtual ~Coordinate() = default;

			/**
			 * 定义每个坐标维度的值类型。
			 * 当前类型为 32 位非负整数，即坐标范围从零开始。
			 */
			typedef unsigned int coordinate_type;

			/**
			 * 定义所有坐标维度。
			 * 具体实现是将每个坐标维度置于 vector 内。元素出现的顺序即为维度顺序。
			 */
			typedef std::vector<coordinate_type> coordinates_type;

			/**
			 * 散列规则。
			 */
			struct Hash
			{
				/**
				 * 散列值类型固定为 size_t。此类型位数与操作系统和 CPU 位宽有关。
				 * 在 Windows x64 操作系统中，size_t 就是“无符号 64 位”，
				 * 即此时 size_t 代表的散列值有 64 位。
				 * 
				 * 这 64 位要平均分配给每个维度的坐标值。具体分配规则如下：
				 * 如果维度数能被 64 整除，则每个维度的宽度就是整除后的商。
				 * 例如二维坐标系中每个维度坐标值占 32 位，而八维坐标系每维度坐标值占 8 位。
				 * 如果维度数不能被 64 整除，则每个维度的宽度依然是整除后的商，忽略余数。
				 * 例如三维坐标系中每个维度坐标值占 21 位，而五维坐标系每维度坐标值占 12 位。
				 * 因此，不建议实际坐标值表示范围超过上述规则描述的范围。如果超过，则应当截取。
				 * 截取规则可以是截取高位，也可以是截取低位。
				 * 如果是截取高位，则坐标相邻的元素会产生冲突，散列堆积现象明显。
				 * 如果是截取低位（即“低位交叉”），则可以避免相邻元素产生散列堆积现象。
				 * 如果相邻元素等间隔分布，则采用高位截取；如果相邻元素分布较为集中，则采用低位截取。
				 * 当前方法采用低位截取。
				 * 
				 * 如果你觉得上述规则不满足你的实际需要，你可以自定义散列规则，并重新定义指针映射类型 pointer_map。
				 */
				size_t operator()(coordinates_type const& c) const
				{
					const auto type_length = sizeof(size_t) * 8;
					const auto dimension_length = type_length / D;

					// 设置掩码。掩码长度与维度位宽有关。
					// 如 D = 2 （二维）且键长度为 64 位时，每维度分得的宽度为 32 位，此时掩码为 0xFFFFFFFF。
					// 又如 D = 8 （八维）且键长度位 64 位时，每维度分得的宽度为 8 位，此时掩码为 0xFF。
					unsigned int mask = 0;
					for (size_t i = 0; i < dimension_length; i++)
					{
						mask <<= 1;
						mask += 1;
					}
					
					size_t index = 0;
					for (int i = 0; i < D; i++)
					{
						index += static_cast<size_t>(c[i] & mask) << i * dimension_length;
					}
					return index;
				}
			};

			/**
			 * 坐标-元素映射表。
			 * 坐标类型参见 vistart::orthogonal_linked_list::coordinates_type。
			 * 散列规则参见 vistart::orthogonal_linked_list::Hash。
			 */
			typedef std::unordered_map<
				coordinates_type,   // 某个维度的坐标（索引）
			    std::shared_ptr<T>, // 为了防止元素添加到映射表中复制一份导致浪费时间和空间，此处采用保存指向元素的共享指针。
			    Hash
			> pointers_map;

			/**
			 * 设置坐标保存指向某个元素的指针。
			 * 每个坐标只能保存一个指针，不允许重复保存。因此若坐标已存在且不允许替换，则直接退出，否则替换。
			 *
			 * @param c 坐标
			 * @param v 元素指针
			 * @param replace_existed 若已存在是否要替换。默认为 true。
			 * @throws CoordinateDimensionMismatchException 若坐标维度与空间维度不一致，则抛出此异常。
			 */
			virtual void set(coordinates_type const& c, std::shared_ptr<T> const& v, bool replace_existed = true)
			{
				check_coordinates_dimension_size(c);
				this->pointers.insert({ c, v });
				if (exists(c) && !replace_existed) return; // 若坐标已存在且不允许替换，则直接退出。
				this->pointers[c] = v;
			}

			/**
			 * 判断当前坐标是否存在元素。
			 *
			 * @return 若存在则返回 true，否则返回 false。
			 * @throws CoordinateDimensionMismatchException 若坐标维度与空间维度不一致，则抛出此异常。
			 */
			virtual bool exists(coordinates_type const& c)
			{
				check_coordinates_dimension_size(c);
				return this->pointers.find(c) != this->pointers.end();
			}

			/**
			 * 根据坐标获取元素指针。
			 * 先检测当前坐标是否有对应元素，如果有则返回，否则返回 nullptr。
			 *
			 * @param c 坐标
			 * @return 指向坐标对应元素的指针。如果坐标对应元素不存在，则返回 nullptr。
			 * @throws CoordinateDimensionMismatchException 若坐标维度与空间维度不一致，则抛出此异常。
			 */
			virtual std::shared_ptr<T> get(coordinates_type const& c)
			{
				check_coordinates_dimension_size(c);
				if (!exists(c))
				{
					return nullptr;
				}
				const auto it = this->pointers.find(c);
				return it->second;
			}

			/**
			 * 从空间中删除指定坐标。
			 *
			 * @return 非负数，代表被成功删除的元素的个数。
			 */
			virtual size_t erase(coordinates_type const& c)
			{
				check_coordinates_dimension_size(c);
				return this->pointers.erase(c);
			}
			
			/**
			 * 检查坐标维度与空间维度是否一致。
			 * 若不一致，则会抛出异常。
			 * @return 若坐标维度与空间维度一致，则返回 true。
			 * @throws CoordinateDimensionMismatchException 若坐标维度与空间维度不一致，则抛出此异常。
			 */
			bool check_coordinates_dimension_size(coordinates_type const& c)
			{
				if (c.size() != D)
				{
					throw CoordinateDimensionMismatchException(static_cast<unsigned char>(c.size()), D);
				}
				return true;
			}

			/**
			 * 不考虑某个维度时，判断两个坐标其余维度是否相等。
			 *
			 * @param c1 坐标 1。
			 * @param c2 坐标 2。
			 * @param d 要避开的维度。
			 * @return 是否相等。
			 */
			[[nodiscard]] static bool coordinates_equal_beyond_dimension(coordinates_type const& c1, coordinates_type const& c2, unsigned int d)
			{
				if (c1.size() != c2.size()) throw CoordinateDimensionMismatchException(c1.size(), c2.size());
				for (int i = 0; i < D; i++)
				{
					if (i == d) continue;
					if (c1[i] != c2[i]) return false;
				}
				return true;
			}

			/**
			 * 将坐标的某个维度屏蔽。
			 * 屏蔽的方式为置零。
			 *
			 * @param c 坐标。
			 * @param d 维度。当前维度会被置零。
			 * @return 处理后的坐标。
			 */
			[[nodiscard]] static coordinates_type coordinates_beyond_dimension(coordinates_type c, unsigned int d)
			{
				if (c.size() != D) throw CoordinateDimensionMismatchException(c.size(), D);
				c[d] = 0;
				return c;
			}

			Coordinate& operator<<(std::tuple<coordinates_type, std::shared_ptr<T>> v)
            {
                const auto& [c, t] = v;
                this->set(c, v);
            }
		
		protected:
			pointers_map pointers;
		};
	}
}

#endif
