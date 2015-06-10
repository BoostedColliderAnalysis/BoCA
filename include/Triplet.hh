# pragma once

# include "Doublet.hh"

namespace analysis {

struct SubJettiness {
    float tau1_beta1;
    float tau2_beta1;
    float tau3_beta1;
    float tau21_beta1;
    float tau32_beta1;

    float tau1_beta2;
    float tau2_beta2;
    float tau3_beta2;
    float tau21_beta2;
    float tau32_beta2;
};

class Triplet : public Multiplet<analysis::Doublet,analysis::Singlet>
{

public:

    using Multiplet<analysis::Doublet,analysis::Singlet>::Multiplet;

    analysis::Doublet Doublet() const;

    fastjet::PseudoJet SingletJet() const;

    analysis::Singlet Singlet() const;

    void set_sub_jettiness(const SubJettiness &sub_jettiness) {
        sub_jettiness_ = sub_jettiness;
    }

    SubJettiness sub_jettiness() const {
        return sub_jettiness_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Triplet";
    }

private:

    SubJettiness sub_jettiness_;

};

}
