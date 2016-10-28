/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/Tag.hh"

namespace boca {

class Identification {

public:

    Identification();

    virtual void SetBdt(double bdt);

    void SetBdt(double bdt_1, double bdt_2);

    virtual double Bdt() const;

    void SetTag(boca::Tag tag);

    void SetTag(boca::Tag tag_1, boca::Tag tag_2);

    boca::Tag Tag() const;

    static double InitialValue();

    /// largest bdt in front
    bool operator<(Identification const& identification) const;

    Identification(Identification const&) = default;

    Identification(Identification &&) = default;

    Identification &operator=(Identification const&) & = default;

    Identification &operator=(Identification &&) & = default;

protected:

    ~Identification() {}

private:

    double bdt_;

    boca::Tag tag_;

};

}

