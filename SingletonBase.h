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
#ifndef __SINGLETON_BASE__
#define __SINGLETON_BASE__
namespace vistart
{
	template <class T>
	class SingletonBase
	{
	protected:
		SingletonBase() {}
	public:
		SingletonBase(SingletonBase const&) = delete;
		SingletonBase& operator=(SingletonBase const&) = delete;
		static T& get()
		{
			static T single;
			return single;
		}
	};
}
#endif
