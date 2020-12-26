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

#ifndef __PLY_COMMENT_LIST_H__
#define __PLY_COMMENT_LIST_H__

constexpr auto PLY_TAG_COMMENT = "comment";

#include <memory>
#include <vector>
#include <string>

namespace vistart
{
	namespace point_cloud_base_presentation
	{
        /*
         This class is used to describe the comment list of ply file.
         */
        class PlyCommentList
        {
        public:
            /**
             No action is required by default.
             */
            PlyCommentList();

            /**
             All comments need to be cleared first.
             */
            ~PlyCommentList();

            /**
             Add comment.

             @param comment the comment to be added.
             @return True if comment added.
             */
            [[nodiscard]] bool add(std::string const& comment) const;

            /**
             Get all the comments.

             @return vector<string>: the stored comments.
             */
            [[nodiscard]] std::shared_ptr<std::vector<std::string>> getComments() const;

            /**
             Add comment.

             @param comment the comment to be added.
             @return PlyCommentList&: itself.
             */
            PlyCommentList& operator<<(std::string const& comment);
        protected:
            /**
             * The stored comments.
             */
            std::shared_ptr<std::vector<std::string>> comments;
        };
	}
}
#endif