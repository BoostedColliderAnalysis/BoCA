// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaBTagger.hh"
// # include "HReaderSimple.hh"


int main()
{

  hbtagger::HMva *Mva = new hbtagger::HMva();

    hmva::HReader *Reader = new hmva::HReader(Mva);

    delete Reader;

    delete Mva;

    return 0;

}
