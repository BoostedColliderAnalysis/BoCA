/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "math/LorentzVector.hh"

namespace boca
{

/**
 * @brief Family member with id, position, and 4-momentum
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

    LorentzVector<boca::Momentum> Momentum() const;

    int Position() const;

    int Id() const;

    std::string Name() const;

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
