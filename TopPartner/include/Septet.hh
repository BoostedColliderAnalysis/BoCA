#pragma once

#include "Quintet.hh"

namespace analysis
{

namespace toppartner
{

  class Septet : public Multiplet<analysis::Quintet, analysis::Doublet>
{

public:

  using Multiplet<analysis::Quintet, analysis::Doublet>::Multiplet;

   analysis::Quintet Quintet()const {
        return Multiplet1();
    }

     analysis::Doublet Doublet()const {
        return Multiplet2();
    }

protected:

    virtual  std::string ClassName() const {
        return "Septet";
    }

private:

};

}

}
