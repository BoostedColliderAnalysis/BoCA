# pragma once

# include "Decuplet.hh"
# include "Quartet22.hh"

namespace toppartner
{

  class Quattuordecuplet : public analysis::Multiplet<toppartner::Decuplet,analysis::Quartet22>
{

public:

  using analysis::Multiplet<toppartner::Decuplet,analysis::Quartet22>::Multiplet;

    inline toppartner::Decuplet Decuplet()const {
        return multiplet_1_;
    }

    inline analysis::Quartet22 Quartet()const {
        return multiplet_2_;
    }

    bool overlap() const;

protected:

    virtual inline std::string ClassName() const {
        return "Quattuordecuplet";
    }

private:

};

}
