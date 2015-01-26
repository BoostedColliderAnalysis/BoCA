# include "HReader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

  hheavyhiggs::HMva Mva;

  hanalysis::HReader Reader(Mva);
  Reader.MVALoop();
  return 0;

}
