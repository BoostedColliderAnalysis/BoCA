# include "HMvaHeavyHiggs.hh"
# include "HFactory.hh"

int main()
{
    HMvaHeavyHiggs *Mva = new HMvaHeavyHiggs();

    Analysis::HFactory *Factory = new Analysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
