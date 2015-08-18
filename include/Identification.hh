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

    void SetFlag(bool flag);

    void SetFlag(bool flag_1, bool flag_2);

    bool Flag() const;

    bool Degenerate() const
    {
        return degenerate_;
    }

    void SetDegenerate(bool degenerate)
    {
        degenerate_ = degenerate;
    }

    void SetDegenerate()
    {
        degenerate_ = true;
    }

    void UnsetDegenerate()
    {
        degenerate_ = false;
    }

    float initial_value() const
    {
        return -11.1111111; // this must be identical to the initial value in the branch
    }

//     template<typename Multiplet>
//     bool operator < (const Multiplet &multiplet) const {
//         // largest bdt in front
//         return (Bdt() > multiplet.Bdt());
//     }

    // largest bdt in front
    bool operator < (const Identification& multiplet) const
    {
        return (Bdt() > multiplet.Bdt());
    }

private:

    float bdt_;

    boca::Tag tag_;

    bool flag_;

    bool degenerate_;

};

}

