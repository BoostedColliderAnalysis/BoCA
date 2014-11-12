# include "HMvaHiggsCpv.hh"
# include "HFactory.hh"

int main()
{
  hmva::HMva *Mva = new hhiggscpv::HMva();

    hmva::HFactory *Factory = new hmva::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
