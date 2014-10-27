# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

    hanalysis::HMva *Mva = new hheavyhiggs::HMva();

    hanalysis::HReader *Reader = new hanalysis::HReader(Mva);

    delete Reader;

    delete Mva;

    cout << "end main" << endl;

    return 0;

}
