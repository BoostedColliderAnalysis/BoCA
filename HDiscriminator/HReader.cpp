// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaDiscriminator.hh"
// # include "HReaderSimple.hh"


int main()
{

    HMvaDiscriminator *Mva = new HMvaDiscriminator();

    HReader *Reader = new HReader(Mva);

    delete Reader;

    delete Mva;

    cout << "end main" << endl;

    return 0;

}
