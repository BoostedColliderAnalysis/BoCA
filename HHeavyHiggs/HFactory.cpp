# include "HMvaHeavyHiggs.hh"
# include "HFactory.hh"

int main()
{
    HMvaHeavyHiggs *Mva = new HMvaHeavyHiggs();
  
    HFactory *Factory = new HFactory(Mva);

    delete Factory;

    delete Mva;
    
    cout << "end main" << endl;

    return 0;

}
