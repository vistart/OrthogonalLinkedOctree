/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/
#pragma once
#ifndef __LINKED_COORDINATE_H__
#define __LINKED_COORDINATE_H__
#include <vector>
#include <iostream>
#include <map>
#include <iterator>
#include "Coordinate.h"
#include "InvalidLinkedCoordinateHeadAndTail.h"

namespace vistart
{
	namespace orthogonal_linked_list
	{
		/**
		 * 正交链接坐标。
		 * 1. 此类为“坐标”类的派生类。在基类基础上添加了有关维护沿维度轴方向前后链接的方法和字段。
		 * 2. 链接是双向的。即可以从前到后，也可以从后到前。
		 * 3. 每个维度都会维护“头（head）”和“尾（tail）”无序表。此无序表作为当前维度头元素和尾元素的指针。因此类型同样是 adjacent_ptr，元素数量为 D。
		 *    使用无序表存储“头”和“尾”是充分考虑到空间的稀疏性。例如二维空间每个维度的坐标范围是 0..2^31-1。如果使用连续类型，例如“vector”，则会导致大量空间浪费。而采用无序表则可以实现接近O(1)的时间复杂度时尽可能不产生冗余空间。
		 * TODO:
		 * 1. 配合实现迭代器
		 * 2. 配合实现算法
		 *
		 * @param D 定义与基类相同。
		 * @param T 定义与基类相同。
		 */
		template<unsigned char D, typename T>
	    class LinkedCoordinate : public Coordinate<D, T>
		{
		public:
		    /**
		     * 坐标值的定义。
		     * 目前坐标值的实质是 unsigned int，即坐标值的支持范围为 0 ~ 2^32 - 1 内的整数。
		     */
			typedef typename vistart::orthogonal_linked_list::Coordinate<D, T>::coordinate_type base_coord;
			/**
			 * 坐标的定义。
			 * 目前坐标的实质是 std::vector<unsigned int>，即坐标为 unsigned int 数组。
			 * 注意：定义并不限制数组元素的数量必须与 D 一致，因此，在使用此定义时，你需要自行保证数组元素数量与 D 一致。
			 */
			typedef typename vistart::orthogonal_linked_list::Coordinate<D, T>::coordinates_type base_coord_col;

			/**
			 * TODO:
			 * 1. 初始化每个维度的“头（head）”和“尾（tail）”指针组。每个维度的容器内元素代表一个维度的头尾节点指针组。
			 */
			LinkedCoordinate()
			{
				this->init_head_and_tail_in_all_dimensions();
			}
			LinkedCoordinate(const LinkedCoordinate& c)
            {
			    this->head_and_tail_in_all_dimensions = c.head_and_tail_in_all_dimensions;
			    this->adjacent_pointers = c.adjacent_pointers;
			    this->coordinates_pointers = c.coordinates_pointers;
			    this->pointers = c.pointers;
#ifdef _DEBUG
			    std::cout << "Linked Coordinate Copied." << std::endl;
#endif
            }
			~LinkedCoordinate() override = default;
#pragma region 定义

#pragma region 近邻指针定义
			typedef std::shared_ptr<base_coord_col> prev_or_next_ptr;
			/**
			 * 单维度近邻指针节点。
			 * 此结构体用于表示某个节点某个维度的前后邻居。但允许前后邻居为空，因此不适合直接用标量，而需要指针。
			 * 如果指针为 nullptr，则表示没有前驱或后继。
			 */
			typedef struct
			{
				prev_or_next_ptr prev; // 前驱
				prev_or_next_ptr next; // 后继
			} adjacent_ptr;
#pragma endregion

#pragma region 所有维度近邻指针节点
			/**
			 * 所有维度近邻指针节点
			 * 由 vector 容器组成。容器元素数量与 vistart::orthogonal_linked_list::Coordinate<D, T>::coordinates_type 的规模相同，即 D。
			 */
			typedef std::vector<adjacent_ptr> adjacent_ptrs;
#pragma endregion

#pragma region 坐标-近邻指针组映射表定义
			/**
			 * 坐标-近邻指针组映射表。
			 * 此映射表的规模和元素位置与基类 Coordinate<D, T>::pointers_map 的完全相同。
			 */
			typedef std::unordered_map<
				base_coord_col,
				std::shared_ptr<adjacent_ptrs>, // 指向所有维度近邻指针节点的指针。使用指针是因为返回该内容时避免复制一份而浪费时间和空间。
				struct Coordinate<D, T>::Hash
			> adjacent_ptrs_map;
			/**
			 * 坐标-做表指针映射表。
			 * 此映射表是为了保存当前元素的完整坐标，且只需要保存一份。需要的时候指向其坐标即可，无须复制。
			 */
			typedef std::unordered_map<
				base_coord_col,
				std::shared_ptr<base_coord_col>,
				struct Coordinate<D, T>::Hash
			> coordinates_map;
#pragma endregion

#pragma region 头尾指针定义
			/**
			 * 头尾指针定义。
			 * 共享指针指向头或尾的坐标（索引）。如果指向 nullptr，则代表当前维度没有元素。
			 */
			typedef std::shared_ptr<base_coord_col> head_or_tail_ptr;
			/**
			 * 头尾指针组。
			 * 此结构体包含指向头坐标的指针和指向尾坐标的指针。
			 */
			typedef struct
			{
				head_or_tail_ptr head; // *head 即为当前维度当前坐标区间内第一个元素。如果为 nullptr，代表此坐标区间为空。
				head_or_tail_ptr tail; // *tail 即为当前维度当前坐标区间内最后一个元素。如果为 nullptr，代表此坐标区间内为空。
				// 由于链接设计为双向，因此 head 和 tail 只能同时为 nullptr 或同时不为 nullptr。如果单独一个为 nullptr，则非正常状态。不论何处遇到非正常状态，都应该立即抛出异常。
			} head_and_tail;
#pragma endregion

#pragma region 单维度头尾指针组定义
			/**
			 * 当前坐标维度所有头尾节点映射。
			 * 此处采用“有序映射”是因为单个维度坐标范围可能会很大，而有效元素很少，且方便按顺序遍历。
			 * 如果存储全部范围，则会造成巨大空间浪费，相比无序映射带来的访问时间效率提升却不明显。
			 */
			typedef std::map<base_coord_col, head_and_tail> head_and_tail_in_dimension;
#pragma endregion

#pragma region 迭代器
            template<unsigned char __D, typename __T>
			struct iterator{
			    enum {BEGIN = 0, END = 1};
			    using value_type = __T;
                using origin = LinkedCoordinate<__D, __T>;
			    using head_and_tail_iterator = typename origin::head_and_tail_in_dimension::iterator;
			    using value_coordinate = typename origin::coordinates_type;
			    iterator(origin* o, unsigned int d, unsigned int di = __D - 1) : o_ptr(o), dimension(di) {
			        if (d == BEGIN)
                    {
			            ht_iter = o_ptr->head_and_tail_in_all_dimensions[dimension].begin();
			            c_ptr = ht_iter->second.head;
                    }
			        else
                    {
			            ht_iter = o_ptr->head_and_tail_in_all_dimensions[dimension].end();
                    }
			    }
                std::shared_ptr<value_type> operator*() {
			        return o_ptr->get(*c_ptr);
			    }
			    // Prefix increment
			    iterator& operator++() {
			        auto next_ptr = o_ptr->get_next_in_dimension(*c_ptr, dimension);
			        if (next_ptr)
                    {// 还有下一个
			            c_ptr = next_ptr;
			            return *this;
                    }
                    ht_iter++;
                    c_ptr = (ht_iter == o_ptr->head_and_tail_in_all_dimensions[dimension].end()) ? nullptr : ht_iter->second.head;
			        return *this;
			    }
			    // Postfix increment
			    iterator operator++(int) {
			        iterator tmp = *this;
                    ++(*this);
			        return tmp;
			    }
			    iterator& operator--() {
                    auto prev_ptr = o_ptr->get_prev_in_dimension(*c_ptr, dimension);
                    if (prev_ptr)
                    {// 还有前一个
                        c_ptr = prev_ptr;
                        return *this;
                    }
                    ht_iter--;
                    c_ptr = ht_iter->second.head;
                    return *this;
			    }
			    iterator operator--(int) {
			        iterator tmp = *this;
			        --(*this);
			        return tmp;
			    }
                friend bool operator== (const iterator& a, const iterator& b) {
			        return (a.ht_iter == b.ht_iter && a.c_ptr == b.c_ptr);
			    };
                friend bool operator!= (const iterator& a, const iterator& b) {
                    return (a.ht_iter != b.ht_iter || a.c_ptr != b.c_ptr);
                };
            private:
			    head_and_tail_iterator ht_iter;
                std::shared_ptr<value_coordinate> c_ptr;
                origin* o_ptr;
                value_type m_ptr;
                unsigned char dimension = 0;
			};
			iterator<D, T> begin(unsigned char dimension = D - 1) {
			    return iterator(this, iterator<D, T>::BEGIN, dimension);
			}
			iterator<D, T> end(unsigned char dimension = D - 1) {
			    return iterator(this, iterator<D, T>::END, dimension);
			}
#pragma endregion

#pragma region 拼接张量
            template<unsigned char __D, typename __T>
            struct tensor
            {
                using origin = LinkedCoordinate<__D, __T>;
                tensor() = delete;
                tensor(origin* o, typename Coordinate<__D, __T>::coordinates_type const& lower, typename Coordinate<__D, __T>::coordinates_type const& upper, std::shared_ptr<__T> null_position_value = nullptr)
                {
                    this->lower = lower;
                    this->upper = upper;
                    this->null_position_value = null_position_value;
                    build_tensor(o);
                }
                tensor(origin* o, typename LinkedCoordinate<__D, __T>::base_coord_col const& c, unsigned int radius = 0, std::shared_ptr<__T> null_position_value = nullptr)
                {
                    for (int i = 0; i < __D; i++)
                    {
                         this->lower[i] = c[i] - radius;
                         this->upper[i] = c[i] + radius;
                    }
                    this->null_position_value = null_position_value;
                    build_tensor(o);
                }
            private:
                typename Coordinate<__D, __T>::coordinates_type lower;
                typename Coordinate<__D, __T>::coordinates_type upper;
                std::shared_ptr<T> null_position_value = nullptr;
                std::map<std::vector<int>, std::shared_ptr<__T>> result;
                origin* o_ptr;
                void build_tensor(origin* o)
                {
                    for (int i = this->lower[0]; i <= this->upper[0]; i++)
                        for (int j = this->lower[1]; j <= this->upper[1]; j++)
                            for (int k = this->lower[2]; k <= this->upper[2]; k++)
                            {
                                typename orthogonal_linked_list::LinkedCoordinate<3, __T>::base_coord_col const c0 {static_cast<unsigned int>(i), static_cast<unsigned int>(j), static_cast<unsigned int>(k)};
                                result.insert({
                                    {i, j, k},
                                    (i < 0 || j < 0 || k < 0) ? nullptr : o->get(c0)});
                            }
                }
            };
			tensor<D, T> get_tensor(typename LinkedCoordinate<3, T>::base_coord_col const& c, unsigned int radius = 0, std::shared_ptr<T> null_position_value = nullptr)
            {
			    return tensor<D, T>(this, c, radius, null_position_value);
            }
#pragma endregion

#pragma endregion

#pragma region 设置元素
			/**
			 * 设置元素。
			 *
			 * @param c 坐标。元素出现的顺序代表了维度顺序。
			 * @param v 元素指针
			 * @param replace_existed 若已存在是否要替换。默认为 true。
			 */
			void set(base_coord_col const& c, std::shared_ptr<T> const& v, bool replace_existed = true) override
			{
				const auto existed = Coordinate<D, T>::exists(c);
				Coordinate<D, T>::set(c, v, replace_existed);

				if (existed) return; // 如果元素已经存在，则并不改变其链接状态。
				// 如果元素不存在，则需设置坐标指针，且要添加前后链接。
				set_coordinates_ptr(c);
				insert_links_in_all_dimensions(c);
			}

			virtual void set_coordinates_ptr(base_coord_col const& c)
			{
				if (this->coordinates_pointers.find(c) == this->coordinates_pointers.end())
				{
					this->coordinates_pointers.insert({ c, std::make_shared<base_coord_col>(c) });
				}
				else
				{
					//this->coordinates_pointers[c] = std::make_shared<base_coord_col>(c);
				}
			}

			/**
			 * 获得坐标 c 对应的值。
			 *
			 * @param c 坐标。
			 * @return 坐标 c 对应的值。
			 */
			std::shared_ptr<T> get(base_coord_col const& c) override
			{
				Coordinate<D, T>::check_coordinates_dimension_size(c);
				if (!Coordinate<D, T>::exists(c))
				{
					return nullptr;
				}
				const auto it = this->pointers.find(c);
				return it->second;
			}

			virtual std::shared_ptr<base_coord_col> get_coordinates_ptr(base_coord_col const& c)
			{
				this->set_coordinates_ptr(c);
				return this->coordinates_pointers[c];
			}

			/**
			 * 从空间中删除指定坐标，并删除所有链接。
			 *
			 * @return 非负数，代表被成功删除的元素的个数。
			 */
			size_t erase(base_coord_col const& c) override
			{
				Coordinate<D, T>::check_coordinates_dimension_size(c);
				remove_links_in_all_dimensions(c);
				this->erase_coordinate_ptr(c);
				return Coordinate<D, T>::erase(c);
			}

			virtual size_t erase_coordinate_ptr(base_coord_col const& c)
			{
				return this->coordinates_pointers.erase(c);
			}
#pragma endregion

#pragma region 调试_用于暴露保护和私有级别的方法和属性
#ifdef _DEBUG
			std::vector<head_and_tail_in_dimension> const& __debug_head_and_tail_in_all_dimensions = head_and_tail_in_all_dimensions;
			adjacent_ptrs_map const& __debug_adjacent_pointers = adjacent_pointers;
			virtual bool __debug_adjacent_exists(base_coord_col const& c)
			{
				return this->adjacents_exists(c);
			}
			virtual std::shared_ptr<adjacent_ptrs> __debug_get_adjacents(base_coord_col const& c)
			{
				return this->get_adjacents(c);
			}
			virtual bool __debug_is_first_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				return this->is_first_in_dimension(c, d);
			}
			virtual bool __debug_is_last_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				return this->is_last_in_dimension(c, d);
			}
#endif
#pragma endregion

		protected:
			/**
			 * 保存每个元素的近邻指针。不要求元素的位置与近邻指针的位置相匹配。
			 * 如果元素存在而对应位置的近邻指针不存在，则近邻指针视为 {{prev: nullptr, next: nullptr}, ..., {prev: nullptr, next: nullptr}}。
			 * 如果元素不存在而对应位置的近邻指针存在，则应立即删除近邻指针，并返回不存在。
			 */
			adjacent_ptrs_map adjacent_pointers;
			/**
			 * 保存坐标指针映射表。
			 */
			coordinates_map coordinates_pointers;

#pragma region 所有维度头尾指针组
			/**
			 * 所有维度头尾指针组
			 * 这个旨在辅助遍历，不与坐标-近邻指针映射合并。
			 * 当前数据结构的实质是保存每个维度头尾指针的向量容器，容器大小应当与 D 相同，但此处定义并不检查，因此需要你在使用时主动保证。
			 */
			std::vector<head_and_tail_in_dimension> head_and_tail_in_all_dimensions;
#pragma endregion

			/**
			 * 初始化所有维度头尾指针。
			 * 所有头尾指针的头和尾均指向空。
			 * 头尾指针组是保存每个维度头尾指针的容器，即头尾指针组的元素数量应当与 D 相同。
			 */
			void init_head_and_tail_in_all_dimensions()
			{
				this->head_and_tail_in_all_dimensions.clear();
				std::vector<head_and_tail_in_dimension>().swap(this->head_and_tail_in_all_dimensions);
				head_and_tail_in_dimension ht;
				for (int i = 0; i < D; i++)
				{
					this->head_and_tail_in_all_dimensions.push_back(ht);
				}
			}
#pragma region 判断指定坐标是否存在近邻指针节点
			/**
			 * 判断指定坐标是否存在近邻指针节点。
			 *
			 * @param c 坐标。坐标的元素个数必须与维度数相匹配。
			 * @return 若存在，则返回 true；否则返回 false。
			 */
			virtual bool adjacents_exists(base_coord_col const& c)
			{
				return this->adjacent_pointers.find(c) != this->adjacent_pointers.end();
			}
#pragma endregion

#pragma region 获得指定坐标对应的近邻指针坐标
			/**
			 * 获取坐标 c 元素的近邻坐标。
			 * 若不存在，则返回空指针。
			 *
			 * @param c 坐标。
			 * @return 对应坐标的近邻坐标组指针。如果指定坐标不存在对应元素，则返回 nullptr。注意：由于存储坐标使用的是“无序映射”，因此返回 nullptr 指的是映射表中没有此元素，而非保存了 nullptr 元素。
			 */
			virtual std::shared_ptr<adjacent_ptrs> get_adjacents(base_coord_col const& c)
			{
				if (Coordinate<D, T>::exists(c))
				{// 若元素存在
					if (!adjacents_exists(c))
					{// 但对应位置近邻指针不存在，则需要构建空指针。
						this->adjacent_pointers.insert({ c, this->build_empty_adjacent_ptrs(c) });
					}
					const auto& it = this->adjacent_pointers.find(c);
					return it->second;
				}
				// 若元素不存在而对应位置近邻指针存在，则要先删除近邻指针，再返回。
				if (this->adjacents_exists(c))
					this->adjacent_pointers.erase(c);
				return nullptr;
			}
#pragma endregion

#pragma region 为指定坐标设置对应的近邻指针元素
			/**
			 * 将坐标 c 元素的近邻坐标组设为 v。
			 * 若已存在，但不允许替换，则什么也不会发生。
			 * 注意：此方法不应对所有用户公开。因为设置连接应该是自动完成的。
			 *
			 * @param c 坐标。
			 * @param v 该坐标的近邻坐标组。
			 * @param replace_existed 已存在时是否允许替换。默认为“允许”。
			 */
			virtual void set_adjacents(base_coord_col const& c, std::shared_ptr<adjacent_ptrs> const& v, bool replace_existed = true)
			{
				const auto existed = adjacents_exists(c);
				if (existed && !replace_existed) return; // 若临近坐标已存在且不允许替换，则直接退出。
				this->adjacent_pointers[c] = v;
			}
#pragma endregion

#pragma region 判断头尾节点是否存在
			/**
			 * 判断维度 d 坐标 i 的头尾指针是否存在。
			 * 假设维度 d = 0，坐标 i 为 { 3, 4, 5 }。则首先将 i[d] 设为 0，即新的 i 为 { 0, 4, 5 }。
			 * 然后在第 0 个头尾指针元素（unordered_map）中，查找 { 0, 4, 5 } 是否存在，即是否指向了尾部。
			 *
			 * @param d 维度。
			 * @param c 坐标。注意，此坐标值传入后会将当前维度索引置零，因此调用此函数前无须处理此维度。
			 * @return 判断当前维度当前坐标是否存在头尾指针。
			 */
			virtual bool head_and_tail_exists(unsigned int d, base_coord_col const& c)
			{
				if (d >= D) throw CoordinateDimensionMismatchException(d, D);
				// auto 类型为 std::unordered_map<typename Coordinate<D, T>::coordinate_type, head_and_tail>
				const auto& ht = this->head_and_tail_in_all_dimensions[d];
				return ht.find(Coordinate<D, T>::coordinates_beyond_dimension(c, d)) != ht.end();
			}
#pragma endregion

#pragma region 设置头尾节点
			/**
			 * 设置头尾节点。
			 *
			 * @param d 维度。
			 * @param c 坐标。
			 * @param v 头尾指针。默认头尾指针均为空。
			 */
			virtual void set_head_and_tail(unsigned int d, base_coord_col const& c, const head_and_tail& v = { nullptr, nullptr })
			{
				// 检查维度
				if (d >= D) throw CoordinateDimensionMismatchException(d, D);
				const auto& ht = this->head_and_tail_in_all_dimensions[d];
				if (head_and_tail_exists(d, c))
				{ // 如果存在则替换：
					const auto& ht = this->head_and_tail_in_all_dimensions[d][Coordinate<D, T>::coordinates_beyond_dimension(c, d)];
					this->head_and_tail_in_all_dimensions[d][Coordinate<D, T>::coordinates_beyond_dimension(c, d)] = v;
				} // 如果不存在则插入：
				else
				{
					this->head_and_tail_in_all_dimensions[d].insert({ Coordinate<D, T>::coordinates_beyond_dimension(c, d), v });
				}
			}

			/**
			 * 将维度 d 坐标 c 的头尾节点设置为空。
			 *
			 * @param d 维度。
			 * @param c 坐标（索引）。
			 */
			virtual void set_empty_head_and_tail(unsigned int d, base_coord_col const& c)
			{
				this->set_head_and_tail(d, Coordinate<D, T>::coordinates_beyond_dimension(c, d), { nullptr, nullptr });
			}
#pragma endregion

#pragma region 判断元素相对头尾节点的位置
			/**
			 * 判断当前元素是否为当前维度第一个。
			 * 注意：[[get_adjacents()]] 方法有返回 nullptr 的风险，而当前方法并不检查，
			 * 因此你需要在使用此方法前自行检查 get_adjacents(c) 返回值是否为 nullptr，以免出现无权访问问题。
			 *
			 * @param c 坐标。
			 * @param d 维度。
			 * @return 是否为第一个。
			 */
			virtual bool is_first_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				const auto& c_ptr = this->get_adjacents(c);
				return c_ptr != nullptr && (*c_ptr)[d].prev == nullptr;
			}

			/**
			 * 判断当前元素是否为当前维度最后一个。
			 * 注意：[[get_adjacents()]] 方法有返回 nullptr 的风险，而当前方法并不检查，
			 * 因此你需要在使用此方法前自行检查 get_adjacents(c) 返回值是否为 nullptr，以免出现无权访问问题。
			 *
			 * @param c 坐标。
			 * @param d 维度。
			 * @return 是否为最后一个。
			 */
			virtual bool is_last_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				const auto& c_ptr = this->get_adjacents(c);
				return c_ptr != nullptr && (*c_ptr)[d].next == nullptr;
			}
#pragma endregion

#pragma region 获得头尾节点
			/**
			 * 或的头尾节点。
			 * 如果指定维度 d 坐标 c 不存在头尾指针，则返回 nullptr。注意：由于存储坐标使用的是“无序映射”，因此返回 nullptr 指的是映射表中没有此元素，而非保存了 nullptr 元素。
			 *
			 * @param d 维度。
			 * @param c 坐标。
			 * @return 若指定维度坐标存在头尾节点，则返回指向该头尾节点的共享指针；否则返回 nullptr。
			 */
			virtual std::shared_ptr<head_and_tail> get_head_and_tail(unsigned int const d, base_coord_col const& c)
			{
				if (head_and_tail_exists(d, c))
				{
					return std::make_shared<head_and_tail>(this->head_and_tail_in_all_dimensions[d][Coordinate<D, T>::coordinates_beyond_dimension(c, d)]);
				}
				return nullptr;
			}
#pragma endregion

#pragma region 检查头尾节点有效性
			/**
			 * 检查某维度头尾节点是否有效。
			 * 如果头尾节点不存在，或头尾节点同为 nullptr，或头尾节点同时不为 nullptr 即为有效。
			 *
			 * @return 当前维度头尾节点有效性。
			 */
			virtual bool check_head_and_tail_in_dimension_valid(unsigned int d, base_coord_col const& c)
			{
				if (d >= D) throw CoordinateDimensionMismatchException(d, D);
				const auto& ht = this->get_head_and_tail(d, c);
				return ht == nullptr || ht->head == nullptr && ht->tail == nullptr || ht->head != nullptr && ht->tail != nullptr;
			}
#pragma endregion

#pragma region 获得指定维度当前节点的下一个节点或前一个节点
			/**
			 * 获得坐标 c 维度 d 的下一个近邻的坐标（索引）值。
			 * 假设，坐标 c（三维）为（1,3,5），维度 d=2 存在下一个近邻坐标（1,3,7）。因此此方法获得的值应当为“7”。
			 * 总而言之，任意维度坐标的某个维度的下一个近邻坐标（索引）值均为一个数。通俗地说就是，二维坐标下，去掉一个维度后，剩余一个维度表示的是恒定与另一个维度的一条线；
			 * 三维坐标下，去掉一个维度后，剩余两个维度表示的是一条线；更高维度无法在现实空间中找到对应，只存在理论可能。
			 *
			 * @param c 坐标。
			 * @param d 维度。
			 * @return 指向当前坐标当前维度的下一个坐标（索引）的指针。如果返回 nullptr，代表不存在近邻指针，可以认为当前节点为最后一个节点（非尾指针）。
			 */
			virtual std::shared_ptr<base_coord_col> get_next_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				const std::shared_ptr<adjacent_ptrs>& next_ptr = this->get_adjacents(c);
				if (next_ptr == nullptr) return nullptr; // 如果不存在近邻指针，则返回 nullptr。注意，并不是坐标-近邻指针映射保存的是 nullptr 元素。
				return (*next_ptr)[d].next;
			}

			/**
			 * 获得某坐标某维度前一个近邻的坐标（索引）。
			 * 其意义与 get_next_in_dimension() 相同，只是方向相反。
			 *
			 * @param c 坐标。
			 * @param d 维度。
			 * @return 指向当前坐标当前维度的前一个坐标（索引）的指针。如果返回 nullptr，代表不存在近邻指针，可以认为当前节点为第一个节点（非头指针）。
			 */
			virtual std::shared_ptr<base_coord_col> get_prev_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				const auto& prev_ptr = this->get_adjacents(c);
				if (prev_ptr == nullptr) return nullptr;
				return (*prev_ptr)[d].prev;
			}
#pragma endregion

#pragma region 构建新的近邻指针
			/**
			 * 构建指定坐标的近邻指针。
			 *
			 * 注意：本方法仅构建近邻指针，不改变映射表现状。因此，不能将获得到近邻指针视作同步改变映射表。
			 *
			 * @param c 坐标
			 * @return 指向新构建近邻指针的共享指针。
			 */
			virtual std::shared_ptr<adjacent_ptrs> build_adjacent_ptrs(base_coord_col const& c)
			{
				std::shared_ptr<adjacent_ptrs> a_ptrs = std::make_shared<adjacent_ptrs>();
				for (int i = 0; i < D; i++)
				{
					a_ptrs->push_back({ this->get_prev_in_dimension(c, i), this->get_next_in_dimension(c, i) });
				}
				return a_ptrs;
			}

			/**
			 * 构建空的近邻指针。
			 *
			 * @param c 坐标
			 * @return 指向新构建近邻指针的共享指针。
			 */
			virtual std::shared_ptr<adjacent_ptrs> build_empty_adjacent_ptrs(base_coord_col const& c)
			{
				std::shared_ptr<adjacent_ptrs> a_ptrs = std::make_shared<adjacent_ptrs>();
				for (int i = 0; i < D; i++)
				{
					a_ptrs->push_back({ nullptr, nullptr });
				}
				return a_ptrs;
			}
#pragma endregion

#pragma region 插入头尾节点
			/**
			 * 插入链接
			 *
			 * @param c 坐标。
			 */
			virtual void insert_links_in_all_dimensions(base_coord_col const& c)
			{
				for (int i = 0; i < D; i++)
				{
					insert_link_in_dimension(c, i);
				}
			}
			/**
			 *
			 * 此方法适用于元素已存在于坐标中但尚未添加链接时。因此不推荐单独使用此方法，除非你知道这么做的后果。
			 *
			 * @param c 坐标。待插入链接的坐标 c。
			 * @param d 维度。作用于第 d 维度。d 在这里是维度序号，而非坐标 c 的元素数。
			 */
			virtual void insert_link_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				// 检查维度
				if (d >= D) throw CoordinateDimensionMismatchException(d, D);
				// 检查元素是否存在
				if (!Coordinate<D, T>::exists(c)) return;
				// 检查头尾指针有效性
				if (!check_head_and_tail_in_dimension_valid(d, c)) throw InvalidLinkedCoordinateHeadAndTail();

				// 先获取头尾指针，以备之后遍历。
				const std::shared_ptr<head_and_tail>& ht = this->get_head_and_tail(d, c);
				if (ht == nullptr || ht->head == nullptr && ht->tail == nullptr)
				{// 如果不存在，则创建头尾指针，使其指向自己。当前维度即创建完毕。
					if (!this->adjacents_exists(c))
					{ // 如果近邻指针不存在，则插入空近邻指针。
						const auto& empty_adjacent_ptrs = this->build_empty_adjacent_ptrs(c);
						// 为当前元素在 adjacent_ptrs 对应位置添加空近邻指针，即 {{nullptr, nullptr}, ..., {nullptr, nullptr}}。
						this->adjacent_pointers.insert({ c, empty_adjacent_ptrs });
					}
					//const auto& coordinate_ptr = std::make_shared<base_coord_col>(c);
					set_head_and_tail(d, c, { this->get_coordinates_ptr(c), this->get_coordinates_ptr(c) });
					return;
				}

				// 如果已存在，则插入元素。
				// 先准备好对应位置的近邻指针。此时近邻指针是空的。
				const auto& c_a_ptr = this->get_adjacents(c);

				// 先寻找头指针指向的下一个元素是谁
				base_coord_col head = *ht->head;

				base_coord_col c_head = c; // 把原始坐标复制过来
				c_head[d] = head[d];          // 把指定维度 d 的元素替换为 head。替换后的 c_head 即为头节点指向的元素的坐标。

				if (head[d] > c[d])
				{// 新插入的位置在头节点之前
					// 双向指向
					(*c_a_ptr)[d].next = ht->head;
					const auto& c_a_head_ptr = this->get_adjacents(c_head);
					(*c_a_head_ptr)[d].prev = std::make_shared<base_coord_col>(c);
					// 改变头指针为新插入的节点。
					this->set_head_and_tail(d, c, { this->get_coordinates_ptr(c), this->get_head_and_tail(d, c)->tail });
				}
				else if (head[d] == c[d])
				{// 目标插入位置已存在，什么也不做。
				}
				else
					while (head[d] < c[d])
					{// 新插入的位置在头节点之后
						const auto& head_next = this->get_next_in_dimension(c_head, d);
						if (head_next == nullptr)
						{// 头节点为最后一个
							(*c_a_ptr)[d].prev = ht->head;
							const auto& c_a_head_ptr = this->get_adjacents(c_head);
							(*c_a_head_ptr)[d].next = std::make_shared<base_coord_col>(c);

							// 改变尾指针为新插入的节点。
							this->set_head_and_tail(d, c, { this->get_head_and_tail(d, c)->head, this->get_coordinates_ptr(c) });
							break;
						}
						if ((*head_next)[d] == c[d])
						{// 节点已存在， 什么也不做。
							break;
						}
						if ((*head_next)[d] < c[d])
						{// 下一个节点依然比当前坐标小，则继续迭代
							head = *head_next;
							c_head[d] = head[d];
							continue;
						}
						if ((*head_next)[d] > c[d])
						{// 夹在前后两个点中间
							(*c_a_ptr)[d].next = head_next;
							(*c_a_ptr)[d].prev = std::make_shared<base_coord_col>(head);
							const auto& c_a_head_ptr = this->get_adjacents(c_head);
							(*c_a_head_ptr)[d].next = std::make_shared<base_coord_col>(c);

							base_coord_col c_next = c;
							c_next[d] = (*head_next)[d];

							const auto& c_a_next_ptr = this->get_adjacents(c_next);
							(*c_a_next_ptr)[d].prev = std::make_shared<base_coord_col>(c);
							break;
						}
					}

				// 再寻找尾指针指向的前一个元素是谁
				base_coord_col tail = *ht->tail;

				base_coord_col c_tail = c;
				c_tail[d] = tail[d];

				if (tail[d] < c[d])
				{// 新插入的位置在尾节点之后
					// 双向指向
					(*c_a_ptr)[d].prev = ht->tail;
					const auto& c_a_tail_ptr = this->get_adjacents(c_tail);
					(*c_a_tail_ptr)[d].next = std::make_shared<base_coord_col>(c);
					// 改变尾指针为新插入的节点。
					this->set_head_and_tail(d, c, { this->get_head_and_tail(d, c)->head, this->get_coordinates_ptr(c) });
				}
				else if (tail[d] == c[d])
				{// 目标插入位置已存在，什么也不做。

				}
				else
					while (tail[d] > c[d])
					{
						const auto& tail_prev = this->get_prev_in_dimension(c_tail, d);
						if (tail_prev == nullptr)
						{// 尾节点为第一个
							(*c_a_ptr)[d].next = ht->tail;
							const auto& c_a_tail_ptr = this->get_adjacents(c_tail);
							(*c_a_tail_ptr)[d].prev = std::make_shared<base_coord_col>(c);

							// 改变尾指针为新插入的节点。
							this->set_head_and_tail(d, c, { this->get_coordinates_ptr(c), this->get_head_and_tail(d, c)->tail });
							break;
						}
						if ((*tail_prev)[d] == c[d])
						{// 节点已存在， 什么也不做。
							break;
						}
						if ((*tail_prev)[d] > c[d])
						{// 下一个节点依然比当前坐标大，则继续迭代
							tail = *tail_prev;
							c_tail[d] = tail[d];
							continue;
						}
						if ((*tail_prev)[d] < c[d])
						{// 夹在前后两个点中间
							(*c_a_ptr)[d].prev = tail_prev;
							(*c_a_ptr)[d].next = std::make_shared<base_coord_col>(tail);
							const auto& c_a_tail_ptr = this->get_adjacents(c_tail);
							(*c_a_tail_ptr)[d].prev = std::make_shared<base_coord_col>(c);

							base_coord_col c_prev = c;
							c_prev[d] = (*tail_prev)[d];

							const auto& c_a_prev_ptr = this->get_adjacents(c_prev);
							(*c_a_prev_ptr)[d].next = std::make_shared<base_coord_col>(c);
							break;
						}
					}
			}

			/**
			 * 删除某个坐标的所有链接
			 *
			 * @param c 坐标。
			 */
			virtual void remove_links_in_all_dimensions(base_coord_col const& c)
			{
				for (int i = 0; i < D; i++)
				{
					remove_link_in_dimension(c, i);
				}
				this->adjacent_pointers.erase(c);
			}

			/**
			 * 删除某个维度的链接。
			 *
			 * @param c 坐标
			 * @param d 维度。
			 */
			virtual void remove_link_in_dimension(base_coord_col const& c, unsigned int const d)
			{
				if (d >= D) throw CoordinateDimensionMismatchException(d, D);
				const std::shared_ptr<head_and_tail>& ht = this->get_head_and_tail(d, c);
				if (ht == nullptr)
				{// 如果不存在，则代表当前区间内不可能有链接，也就无需删除。
					return;
				}
				// 四种情况：
				// 1. 当前节点是当前维度的第一个节点，但不是最后一个节点，即前驱为 nullptr。删除时，需要将头节点指向当前节点的后继，当前节点后继的前驱改为 nullptr。
				// 2. 当前节点不是当前维度的第一个节点，也不是最后一个节点，即前驱和后缀均不为 nullptr。删除时，需要将前驱的后继指向自己的后继，将后继的前驱指向自己的前驱。
				// 3. 当前节点是当前维度的最后一个节点，但不是第一个节点，即后继为 nullptr。删除时，需要将尾节点指向当前节点的前驱，当前节点前驱的后继改为 nullptr。
				// 4. 当前节点是当前维度的第一个节点，也是最后一个节点。即前驱和后继均为 nullptr。删除时，将头节点和尾节点指向 nullptr 即可。

				// 如果当前节点的前驱是否为空，决定了是否修改头节点指向。如果前驱为空，则需要改头节点，否则不需要。后继为空与修改尾节点的关系类同。
				// 如果前驱不为空，后继为 nullptr 时，前驱的后继改为 nullptr；后继不为 nullptr 时，前驱的后继改为当前的后继，因此前驱如果存在，则不必判断当前节点的后继是否为空，直接改指向即可；后继与后继的前驱处理方法类似。
				if (!this->get_adjacents(c)) return;
				const auto is_first = is_first_in_dimension(c, d);
				const auto is_last = is_last_in_dimension(c, d);

				const auto& c_a_ptr = this->get_adjacents(c);

				if (is_first && is_last)
				{
					this->set_empty_head_and_tail(d, c);
				}
				else if (is_first && !is_last)
				{
					// const auto& c_next = this->get_next_in_dimension(c, d);
					base_coord_col c_next = c;
					c_next[d] = (*this->get_next_in_dimension(c, d))[d];

					const auto& c_next_ptr = this->get_adjacents(c_next);
					(*c_next_ptr)[d].prev = (*c_a_ptr)[d].prev;

					const auto& ht = this->get_head_and_tail(d, c);
					this->set_head_and_tail(d, c, { (*c_a_ptr)[d].next, ht->tail });
				}
				else if (!is_first && is_last)
				{
					base_coord_col c_prev = c;
					c_prev[d] = (*this->get_prev_in_dimension(c, d))[d];

					const auto& c_prev_ptr = this->get_adjacents(c_prev);
					(*c_prev_ptr)[d].next = (*c_a_ptr)[d].next;

					const auto& ht = this->get_head_and_tail(d, c);
					this->set_head_and_tail(d, c, { ht->head, (*c_a_ptr)[d].prev });
				}
				else
					// if (!is_first && !is_last)
				{
					base_coord_col c_next = c;
					c_next[d] = (*this->get_next_in_dimension(c, d))[d];
					const auto& c_next_ptr = this->get_adjacents(c_next);
					(*c_next_ptr)[d].prev = (*c_a_ptr)[d].prev;

					base_coord_col c_prev = c;
					c_prev[d] = (*this->get_prev_in_dimension(c, d))[d];
					const auto& c_prev_ptr = this->get_adjacents(c_prev);
					(*c_prev_ptr)[d].next = (*c_a_ptr)[d].next;


					const auto& ht = this->get_head_and_tail(d, c);
					// this->set_head_and_tail(d, c, { (*c_next_ptr)[d].next, (*c_prev_ptr)[d].prev });
				}
				// this->adjacent_pointers.erase(c);
			}
#pragma endregion

		private:
		};

	}
}
#endif
