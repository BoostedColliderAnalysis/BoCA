# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

  hanalysis::HMva *Mva = new hheavyhiggs::HMva();

  hanalysis::HReader  *Reader = new hanalysis::HReader (Mva);

    Reader->MVALoop();

    delete Reader;

    delete Mva;

    return 1;

}
