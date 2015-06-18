# pragma once

# include "Decuplet.hh"
# include "Quartet22.hh"

namespace analysis
{

namespace toppartner
{

class Quattuordecuplet : public Multiplet<toppartner::Decuplet55, Quartet22>
{

public:

    using Multiplet<toppartner::Decuplet55, Quartet22>::Multiplet;

    inline toppartner::Decuplet55 Decuplet()const {
        return Multiplet1();
    }

    inline Quartet22 Quartet()const {
        return Multiplet2();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quattuordecuplet";
    }

private:

};

}

}
