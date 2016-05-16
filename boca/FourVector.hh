/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once


namespace boca
{

class TreeReader;

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
