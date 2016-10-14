/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TObject.h"

namespace boca
{

/**
* @ingroup Boca
* @brief Tree branches for root files
*
*/
namespace branch
{

/**
 * @brief %Base tree branch
 *
 */
class Base : public TObject
{

public:

    static float InitialValue();

    Base() {};

    Base(Base const&) = default;

    Base(Base &&) = default;

    Base &operator=(Base const&) & = default;

    Base &operator=(Base &&) & = default;

protected:

    ~Base() {}

private:

    ClassDef(Base, 1)

};

}

}
