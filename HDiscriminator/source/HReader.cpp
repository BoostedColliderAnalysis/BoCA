// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaDiscriminator.hh"
// # include "HReaderSimple.hh"


int main()
{

    HMvaDiscriminator *Mva = new HMvaDiscriminator();

    Analysis::HReader *Reader = new Analysis::HReader(Mva);

    delete Reader;

    delete Mva;

    return 0;

}
