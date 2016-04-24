/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/io/TreeReader.hh"

namespace boca
{

/**
 * @brief converts Clones to LorentzVectors and Jets
 *
 */
class FourVector
{

public:

  FourVector(boca::TreeReader const& tree_reader);

protected:

    boca::TreeReader const& TreeReader() const;

private:

    boca::TreeReader const* tree_reader_;

};

}
