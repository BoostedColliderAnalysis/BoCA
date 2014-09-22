# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{
        
    HMvaHeavyHiggs *Mva = new HMvaHeavyHiggs();
  
    HReader *Reader = new HReader(Mva);
    
    delete Reader;
    
    delete Mva;

    cout << "end main" << endl;
    
    return 0;
    
}