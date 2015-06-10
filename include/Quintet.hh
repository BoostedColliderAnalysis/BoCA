# pragma once

# include "Triplet.hh"

namespace analysis
{

class Quintet : public Multiplet<analysis::Triplet,analysis::Doublet>
{

public:

  using Multiplet<analysis::Triplet,analysis::Doublet>::Multiplet;

  inline analysis::Doublet Doublet()const {
        return multiplet_2_;
    }

    inline analysis::Triplet Triplet()const {
        return multiplet_1_;
    }

    bool overlap() const;

protected:

    virtual inline std::string ClassName() const {
        return "Quintet";
    }

private:

};

}
