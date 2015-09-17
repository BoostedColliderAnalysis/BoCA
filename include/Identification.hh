/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>

namespace boca {

enum class Tag {
    background = 0,
    signal = 1

};

std::string Name(Tag tag);

class Identification {

public:

    Identification();

    virtual void SetBdt(float bdt);

    void SetBdt(float bdt_1, float bdt_2);

    virtual float Bdt() const;

    void SetTag(Tag tag);

    void SetTag(boca::Tag tag_1, boca::Tag tag_2);

    boca::Tag Tag() const;

    static float InitialValue();

    /// largest bdt in front
    bool operator<(Identification const& multiplet) const;

private:

    float bdt_;

    boca::Tag tag_;

};

}

