# pragma once

# include "Doublet.hh"

namespace analysis
{

class Quartet22 : public Multiplet<Doublet,Doublet>
{

public:

    using Multiplet<Doublet,Doublet>::Multiplet;

    inline Doublet Doublet1()const {
        return multiplet_1_;
    }

    inline Doublet Doublet2()const {
        return multiplet_2_;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Quartet22";
    }

private:

};

}
