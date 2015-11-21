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

    //     Member(Id id);
//
    Member(int id, int position);

    Member(LorentzVector const& momentum, int id, int position);

    Member(TLorentzVector const& momentum, int id, int position);

    LorentzVector momentum() const;

    int position() const;

    int id() const;

    void set(int id, int position) {
        id_ = id;
        position_ = position;
    }

private:

    LorentzVector momentum_;

    int position_ = EmptyPosition;

    int id_ = int(Id::empty);

};

}
