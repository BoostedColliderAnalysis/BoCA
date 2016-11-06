/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

namespace boca {

/**
* @brief The Tag distinguishes between signal and background events
*
*/
enum class Tag {
    background = 0, ///< Background
    signal = 1 ///< Signal
};

/**
* @brief Name of Tag
*/
std::string Name(Tag tag);

/**
 * @brief Stream the name of a particle with given Id
 *
 */
std::ostream& operator<<(std::ostream & stream, Tag tag);

}

