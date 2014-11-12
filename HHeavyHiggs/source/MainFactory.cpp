# include "HMvaHeavyHiggs.hh"
# include "HFactory.hh"

int main()
{
  hmva::HMva *Mva = new hheavyhiggs::HMva();

    hmva::HFactory *Factory = new hmva::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
