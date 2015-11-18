#include "Quintet.hh"
#include "Quartet.hh"

namespace boca
{

namespace naturalness
{

class Nonet : public TwoBody<boca::Quintet, Quartet22>
{

public:

    using TwoBody<boca::Quintet, Quartet22>::TwoBody;

    boca::Quintet const& Quintet() const {
        return Multiplet1();
    }

    Quartet22 const& Quartet() const {
        return Multiplet2();
    }

};

}

}
