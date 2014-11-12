# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

    hmva::HMva *Mva = new hheavyhiggs::HMva();

    hmva::HReader *Reader = new hmva::HReader(Mva);

    delete Reader;

    delete Mva;

    return 1;

}
