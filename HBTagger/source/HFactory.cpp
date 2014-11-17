# include "HMvaBTagger.hh"
# include "HFactory.hh"

int main()
{
  hmva::HMva *Mva = new hbtagger::HMva();

    hmva::HFactory *Factory = new hmva::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
