/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <string>

namespace boca
{

/**
* @brief The stage of the multivariant tagging process
*
*/
enum class Stage
{
    trainer,                                                ///< Training stage
    reader                                                  ///< Reading stage
};

/**
* @brief Name of the multivariant tagging stage
*/
std::string Name(Stage stage);

}
