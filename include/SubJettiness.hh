/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

namespace boca
{

class SubJettiness
{

public:

    float tau1_beta1() const;
    float tau2_beta1() const;
    float tau3_beta1() const;
    float tau21_beta1() const;
    float tau32_beta1() const;

    float tau1_beta2() const;
    float tau2_beta2() const;
    float tau3_beta2() const;
    float tau21_beta2() const;
    float tau32_beta2() const;

    void tau1_beta1(float tau);
    void tau2_beta1(float tau);
    void tau3_beta1(float tau);
    void tau21_beta1(float tau);
    void tau32_beta1(float tau);

    void tau1_beta2(float tau);
    void tau2_beta2(float tau);
    void tau3_beta2(float tau);
    void tau21_beta2(float tau);
    void tau32_beta2(float tau);

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

}
