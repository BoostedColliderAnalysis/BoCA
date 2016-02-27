/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "physics/LorentzVector.hh"

namespace boca
{

/**
 * @brief Position outside of a vector
 *
 */

class Member
{

public:

    Member();

    Member(int id);

    Member(int id, int position);

    Member(LorentzVector<boca::Momentum> const& momentum, int id, int position);

    Member(TLorentzVector const& momentum, int id, int position);

    LorentzVector<boca::Momentum>  const& Momentum() const;

    int Position() const;

    int Id() const;

    void Set(int id, int position);

    static int EmptyPosition();

    bool operator==(Member const& member);

    bool operator!=(Member const& member);

private:

    LorentzVector<boca::Momentum> momentum_;

    int position_ = EmptyPosition();

    int id_;

};

}
