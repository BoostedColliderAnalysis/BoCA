// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaBTagger.hh"
// # include "HReaderSimple.hh"


int main()
{

    hbtagger::HMva *Mva = new hbtagger::HMva();

    hanalysis::HReader  *Reader = new hanalysis::HReader(Mva);

    Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 0;

}
