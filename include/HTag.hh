# pragma once

# include "Object.hh"

namespace analysis
{

class HTag : public Object
{

public:

    HTag();

    void SetBdt(const float NewBdt);

    void SetBdt(const float NewBdt1, const float NewBdt2);

    virtual float Bdt() const;

    void SetTag(const int NewTag);

    void SetTag(const int tag_1, const int tag_2);

    int Tag() const;

    void SetFlag(const bool NewFlag);

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
        return initial_value_;
    }

    template<typename HMultiplet>
    bool operator < (const HMultiplet &Multiplet) const {
        // largest bdt in front
        return (Bdt() > Multiplet.Bdt());
    }

protected:

    virtual inline std::string ClassName() const {
        return "HTag";
    }

private:

    float bdt_;

    int tag_;

    float initial_value_;

    bool flag_;

    bool degenerate_;

};

}

