/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/branch/Result.hh"

namespace boca
{

namespace branch
{

/**
* @brief %Cut base tree branch
*
*/
class Cut : public Result
{

public:

    Cut();

    std::vector<bool> passed;

    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        Result::Fill(multiplet);
        passed = multiplet.Passed();
    }

private:

    ClassDef(Cut, 1)

};

}

}
