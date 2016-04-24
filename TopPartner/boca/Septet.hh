#include "boca/multiplets/Quintet.hh"
#include "boca/multiplets/Doublet.hh"

namespace boca
{

  namespace naturalness
  {

    class Septet : public TwoBody<boca::Quintet, boca::Doublet>
    {

    public:

      using TwoBody<boca::Quintet, boca::Doublet>::TwoBody;

      boca::Quintet const& Quintet() const {
        return Multiplet1();
      }

      boca::Doublet const& Doublet() const {
        return Multiplet2();
      }

    };

  }

}
