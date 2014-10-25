# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

  HeavyHiggs::HMva *Mva = new HeavyHiggs::HMva();

    Analysis::HReader *Reader = new Analysis::HReader(Mva);

    delete Reader;

    delete Mva;

    cout << "end main" << endl;

    return 0;

}
