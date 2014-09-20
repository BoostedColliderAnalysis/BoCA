# include "HMvaDiscriminator.hh"
# include "HFactory.hh"

int main()
{
    HMvaDiscriminator *Mva = new HMvaDiscriminator();
  
    HFactory *Factory = new HFactory(Mva);

    delete Factory;

    delete Mva;
    
    cout << "end main" << endl;

    return 0;

}
