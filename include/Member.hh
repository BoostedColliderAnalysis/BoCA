/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Particles.hh"
#include "LorentzVector.hh"

class TLorentzVector;

namespace boca
{

/**
 * @brief Position outside of a vector
 *
 */
static int EmptyPosition = -1;

class Member
{

public:

    Member() {}

    Member(int id);

    Member(int id, int position);

    Member(LorentzVector const& momentum, int id, int position);

    Member(TLorentzVector const& momentum, int id, int position);

    LorentzVector Momentum() const;

    int Position() const;

    int Id() const;

    void Set(int id, int position);

private:

    LorentzVector momentum_;

    int position_ = EmptyPosition;

    int id_ = int(boca::Id::empty);

};

}
