// # include "HReaderMulti.hh"
# include "HReader.hh"
# include "HMvaBTagger.hh"
// # include "HReaderSimple.hh"


int main()
{
    hbtagger::HMva Mva;
    hanalysis::HReader  Reader(Mva);
    Reader.MVALoop();
    return 0;
}
