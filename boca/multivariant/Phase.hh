/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Tag.hh"
#include "boca/multivariant/Stage.hh"

namespace boca
{

/**
* @brief The phases of the multivariant tagging process
*
*/
class Phase
{
public:
    /**
    * @brief Constructor
    */
    Phase(boca::Stage stage, boca::Tag tag);

    /**
    * @brief The Tag of the multivariant tagging process
    *
    * either signal or background
    */
    boca::Tag Tag() const;

    /**
    * @brief The stage of the multivariant tagging process
    *
    * either reading or tagging stage
    */
    boca::Stage Stage() const;

private:

    boca::Tag tag_;

    boca::Stage stage_;

};

}
