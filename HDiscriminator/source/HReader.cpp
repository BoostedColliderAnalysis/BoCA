// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaDiscriminator.hh"
// # include "HReaderSimple.hh"


int main()
{

  hcpvhiggs::HMva *Mva = new hcpvhiggs::HMva();

  hmva::HReader *Reader = new hmva::HReader(Mva);
  
  Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 0;

}
