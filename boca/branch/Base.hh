/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TObject.h"

namespace boca
{

namespace branch
{

/**
 * @brief Basic tree branches
 *
 */
class Base : public TObject
{

public:

    static float InitialValue();

private:

    ClassDef(Base, 1)

};

}

}
