# pragma once

# include "Quintet.hh"

namespace analysis
{

namespace toppartner
{

  class Septet : public Multiplet<analysis::Quintet, analysis::Doublet>
{

public:

  using Multiplet<analysis::Quintet, analysis::Doublet>::Multiplet;

  inline analysis::Quintet Quintet()const {
        return Multiplet1();
    }

    inline analysis::Doublet Doublet()const {
        return Multiplet2();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Septet";
    }

private:

};

}

}
