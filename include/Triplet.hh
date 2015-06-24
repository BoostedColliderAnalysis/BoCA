# pragma once

# include "Doublet.hh"

namespace analysis
{

class SubJettiness
{
public:
    float tau1_beta1() const {
        return tau1_beta1_;
    }
    float tau2_beta1() const {
        return tau2_beta1_;
    }
    float tau3_beta1() const {
        return tau3_beta1_;
    }
    float tau21_beta1() const {
        if (tau1_beta1() > 0) return tau21_beta1_;
        return 0;
    }
    float tau32_beta1() const {
        if (tau2_beta1() > 0) return tau32_beta1_;
        return 0;
    }

    float tau1_beta2() const {
        return tau1_beta2_;
    }
    float tau2_beta2() const {
        return tau2_beta2_;
    }
    float tau3_beta2() const {
        return tau3_beta2_;
    }
    float tau21_beta2() const {
        if (tau1_beta2() > 0) return tau21_beta2_;
        return 0;
    }
    float tau32_beta2() const {
        if (tau2_beta2() > 0) return tau32_beta2_;
        return 0;
    }

    void tau1_beta1(const float tau) {
        tau1_beta1_ = tau;
    }
    void tau2_beta1(const float tau) {
        tau2_beta1_ = tau;
    }
    void tau3_beta1(const float tau) {
        tau3_beta1_ = tau;
    }
    void tau21_beta1(const float tau) {
        tau21_beta1_ = tau;
    }
    void tau32_beta1(const float tau) {
        tau32_beta1_ = tau;
    }

    void tau1_beta2(const float tau) {
        tau1_beta2_ = tau;
    }
    void tau2_beta2(const float tau) {
        tau2_beta2_ = tau;
    }
    void tau3_beta2(const float tau) {
        tau3_beta2_ = tau;
    }
    void tau21_beta2(const float tau) {
        tau21_beta2_ = tau;
    }
    void tau32_beta2(const float tau) {
        tau32_beta2_ = tau;
    }

private:

    float tau1_beta1_;
    float tau2_beta1_;
    float tau3_beta1_;
    float tau21_beta1_;
    float tau32_beta1_;

    float tau1_beta2_;
    float tau2_beta2_;
    float tau3_beta2_;
    float tau21_beta2_;
    float tau32_beta2_;
};

class Triplet : public Multiplet<analysis::Doublet, analysis::Singlet>
{

public:

    using Multiplet<analysis::Doublet, analysis::Singlet>::Multiplet;

    analysis::Doublet &Doublet() const;

    fastjet::PseudoJet SingletJet() const;

    analysis::Singlet &Singlet() const;

    void set_sub_jettiness(const SubJettiness &sub_jettiness) {
        sub_jettiness_ = sub_jettiness;
    }

    float pt() const {
        return pt_;
    }

    void set_pt(const float &pt) {
        pt_ = pt;
    }

    SubJettiness sub_jettiness() const {
        return sub_jettiness_;
    }

protected:

    virtual  std::string ClassName() const {
        return "Triplet";
    }

private:

    SubJettiness sub_jettiness_;

    float pt_;

};

}
