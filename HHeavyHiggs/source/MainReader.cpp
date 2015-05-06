# include "Reader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

  hheavyhiggs::HMva Mva;

  hanalysis::Reader Reader(Mva);
//   Reader.MVALoop(); // must be reactivated
  return 0;

}
