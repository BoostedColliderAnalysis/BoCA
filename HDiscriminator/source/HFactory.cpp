# include "HMvaDiscriminator.hh"
# include "HFactory.hh"

int main()
{
    HMvaDiscriminator *Mva = new HMvaDiscriminator();
  
    HFactory *Factory = new HFactory(Mva);

    delete Factory;

    delete Mva;
    
    return 0;

}
