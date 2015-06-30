#pragma once

#include "Object.hh"

namespace analysis
{

enum class Tag
{
    background = 0,
    signal = 1

};

std::string Name(const Tag tag);

class Identification : public Object
{

public:

    Identification();

    virtual void SetBdt(const float bdt);

    void SetBdt(const float bdt_1, const float bdt_2);

    virtual float Bdt() const;

    void SetTag(const analysis::Tag tag);

    void SetTag(const analysis::Tag tag_1, const analysis::Tag tag_2);

    analysis::Tag Tag() const;

    void SetFlag(const bool flag);

    void SetFlag(const bool flag_1, const bool flag_2);

    bool Flag() const;

    bool Degenerate() const {
        return degenerate_;
    }

    void SetDegenerate(const bool degenerate) {
        degenerate_ = degenerate;
    }

    void SetDegenerate() {
        degenerate_ = true;
    }

    void UnsetDegenerate() {
        degenerate_ = false;
    }

    float initial_value() const {
        return -11.1111111; // this must be identical to the initial value in the branch
    }

    template<typename Multiplet>
    bool operator < (const Multiplet &multiplet) const {
        // largest bdt in front
        return (Bdt() > multiplet.Bdt());
    }

protected:

    virtual  std::string ClassName() const {
        return "Identification";
    }

private:

    float bdt_;

    analysis::Tag tag_;

    bool flag_;

    bool degenerate_;

};

}

