# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

    HMvaHeavyHiggs *Mva = new HMvaHeavyHiggs();

    Analysis::HReader *Reader = new Analysis::HReader(Mva);

    delete Reader;

    delete Mva;

    cout << "end main" << endl;

    return 0;

}
