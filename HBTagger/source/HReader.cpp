// # include "ReaderMulti.hh"
# include "Reader.hh"
# include "HMvaBTagger.hh"
// # include "ReaderSimple.hh"


int main()
{
    hbtagger::HMva Mva;
    hanalysis::Reader  Reader(Mva);
//     Reader.MVALoop(); // must be reactivated
    return 0;
}
