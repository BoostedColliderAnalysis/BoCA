# include "HMvaDiscriminator.hh"
# include "HFactory.hh"

int main()
{
  Discriminator::HMva *Mva = new Discriminator::HMva();

    Analysis::HFactory *Factory = new Analysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
