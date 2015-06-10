# pragma once

# include "Doublet.hh"

namespace analysis
{

class Quartet22 : public Multiplet<Doublet, Doublet>
{

public:

    using Multiplet<Doublet, Doublet>::Multiplet;

    Doublet Doublet1()const;

    Doublet Doublet2()const;

protected:

    virtual inline std::string ClassName() const {
        return "Quartet22";
    }

private:

};

}
