/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/TwoBody.hh"

namespace boca
{

/**
* @ingroup Multiplets
* @brief A %Doublet consisting of two Singlets
*
*/
class Doublet : public boca::TwoBody<boca::Singlet, boca::Singlet>
{

public:

    using TwoBody<boca::Singlet, boca::Singlet>::TwoBody;

    boca::Singlet const &Singlet1() const;

    boca::Singlet const &Singlet2() const;

private:

    std::string Name() const override;

};

}

