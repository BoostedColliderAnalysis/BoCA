# include "Reader.hh"
# include "HMvaHeavyHiggs.hh"


int main()
{

  hheavyhiggs::HMva Mva;

  analysis::Reader Reader(Mva);
//   Reader.MVALoop(); // must be reactivated
  return 0;

}
