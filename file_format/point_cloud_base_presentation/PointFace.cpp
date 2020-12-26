/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2020 vistart
 * @license https://vistart.me/license/
*/
#ifndef __POINT_FACE__
#include "PointFace.h"
#endif

#ifdef __POINT_FACE__
using namespace std;
#ifdef _MSC_VER
#include <exception>
#endif
#ifdef __GNUC__
#include <stdexcept>
#endif

PointFace::PointFace()
{
	this->vertex_indices = make_shared<priority_queue<unsigned int, vector<unsigned int>, greater<>>>();
}

PointFace::~PointFace()
{
	this->vertex_indices = nullptr;
}

bool PointFace::operator==(PointFace const& face) const
{
	if (this->vertex_indices->size() != face.vertex_indices->size()) return false;
	auto a = this->vertex_indices;
	auto b = face.vertex_indices;
	while (!a->empty())
	{
		if (a->top() != b->top()) return false;
		a->pop();
		b->pop();
	}
	return true;
}

bool PointFace::operator!=(PointFace const& face) const
{
	return !(*this == face);
}

#endif
