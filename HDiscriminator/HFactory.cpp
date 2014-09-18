# include "HMva.hh"
# include "HFactory.hh"

int main()
{
    HMva *Mva = new HMva();
  
    HFactory *Factory = new HFactory(Mva);

    delete Factory;

    delete Mva;
    
    cout << "end main" << endl;

    return 0;

}
