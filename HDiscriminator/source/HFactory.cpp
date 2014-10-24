# include "HMvaDiscriminator.hh"
# include "HFactory.hh"

int main()
{
    HMvaDiscriminator *Mva = new HMvaDiscriminator();

    Analysis::HFactory *Factory = new Analysis::HFactory(Mva);

    delete Factory;

    delete Mva;

    return 0;

}
