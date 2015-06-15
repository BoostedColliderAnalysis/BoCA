# pragma once

# include "Decuplet.hh"
# include "Quartet22.hh"

namespace toppartner
{

class Quattuordecuplet : public analysis::Multiplet<toppartner::Decuplet, analysis::Quartet22>
{

public:

    using analysis::Multiplet<toppartner::Decuplet, analysis::Quartet22>::Multiplet;

    inline toppartner::Decuplet Decuplet()const {
        return Multiplet1();
    }

    inline analysis::Quartet22 Quartet()const {
        return Multiplet2();
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quattuordecuplet";
    }

private:

};

}
