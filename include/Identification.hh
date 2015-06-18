# pragma once

# include "Object.hh"

namespace analysis
{

class Identification : public Object
{

public:

    Identification();

    virtual void SetBdt(const float bdt);

    void SetBdt(const float bdt_1, const float bdt_2);

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

    template<typename Multiplet>
    bool operator < (const Multiplet &multiplet) const {
        // largest bdt in front
        return (Bdt() > multiplet.Bdt());
    }

protected:

    virtual inline std::string ClassName() const {
        return "Identification";
    }

private:

    float bdt_;

    int tag_;

    float initial_value_;

    bool flag_;

    bool degenerate_;

};

}

