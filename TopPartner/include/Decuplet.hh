# pragma once

# include "Quintet.hh"

namespace toppartner
{

class Decuplet : public analysis::Multiplet<analysis::Quintet, analysis::Quintet>
{

public:

    using analysis::Multiplet<analysis::Quintet, analysis::Quintet>::Multiplet;

    inline analysis::Quintet Quintet1()const {
        return Multiplet1();
    }

    inline analysis::Quintet Quintet2()const {
        return Multiplet2();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Decuplet";
    }

private:

};

}
