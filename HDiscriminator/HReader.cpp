// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMva.hh"
// # include "HReaderSimple.hh"


int main()
{
        
    HMva *Mva = new HMva();
  
    HReader *Reader = new HReader(Mva);
    
    delete Reader;
    
    delete Mva;

    cout << "end main" << endl;
    
    return 0;
    
}