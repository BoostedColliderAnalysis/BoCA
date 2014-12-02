# include "HMvaBTagger.hh"
# include "HFactory.hh"

int main()
{
  hanalysis::HMva *Mva = new hbtagger::HMva();

  hanalysis::HFactory *Factory = new hanalysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
