// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaDiscriminator.hh"
// # include "HReaderSimple.hh"


int main()
{

  hcpvhiggs::HMva *Mva = new hcpvhiggs::HMva();

    hanalysis::HReader *Reader = new hanalysis::HReader(Mva);

    delete Reader;

    delete Mva;

    return 0;

}
