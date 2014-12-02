# include "HMvaEvent.hh"
# include "HFactory.hh"

int main()
{
  hanalysis::HMva *Mva = new hhiggscpv::HMvaEvent();

  hanalysis::HFactory *Factory = new hanalysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
