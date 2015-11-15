/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "SubJettiness.hh"

namespace boca
{

float SubJettiness::tau1_beta1() const
{
    return tau1_beta1_;
}
float SubJettiness::tau2_beta1() const
{
    return tau2_beta1_;
}
float SubJettiness::tau3_beta1() const
{
    return tau3_beta1_;
}
float SubJettiness::tau21_beta1() const
{
    if (tau1_beta1() > 0) return tau21_beta1_;
    return 0;
}
float SubJettiness::tau32_beta1() const
{
    if (tau2_beta1() > 0) return tau32_beta1_;
    return 0;
}
float SubJettiness::tau1_beta2() const
{
    return tau1_beta2_;
}
float SubJettiness::tau2_beta2() const
{
    return tau2_beta2_;
}
float SubJettiness::tau3_beta2() const
{
    return tau3_beta2_;
}
float SubJettiness::tau21_beta2() const
{
    if (tau1_beta2() > 0) return tau21_beta2_;
    return 0;
}
float SubJettiness::tau32_beta2() const
{
    if (tau2_beta2() > 0) return tau32_beta2_;
    return 0;
}
void SubJettiness::tau1_beta1(float tau)
{
    tau1_beta1_ = tau;
}
void SubJettiness::tau2_beta1(float tau)
{
    tau2_beta1_ = tau;
}
void SubJettiness::tau3_beta1(float tau)
{
    tau3_beta1_ = tau;
}
void SubJettiness::tau21_beta1(float tau)
{
    tau21_beta1_ = tau;
}
void SubJettiness::tau32_beta1(float tau)
{
    tau32_beta1_ = tau;
}
void SubJettiness::tau1_beta2(float tau)
{
    tau1_beta2_ = tau;
}
void SubJettiness::tau2_beta2(float tau)
{
    tau2_beta2_ = tau;
}
void SubJettiness::tau3_beta2(float tau)
{
    tau3_beta2_ = tau;
}
void SubJettiness::tau21_beta2(float tau)
{
    tau21_beta2_ = tau;
}
void SubJettiness::tau32_beta2(float tau)
{
    tau32_beta2_ = tau;
}

}
