# include "HMvaDiscriminator.hh"
# include "HFactory.hh"

int main()
{
  HiggsCPV::HMva *Mva = new HiggsCPV::HMva();

    Analysis::HFactory *Factory = new Analysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
