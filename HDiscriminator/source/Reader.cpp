# include "Reader.hh"
# include "HMvaDiscriminator.hh"


int main()
{
  hcpvhiggs::HMva Mva;
  hanalysis::Reader Reader(Mva);
//   Reader.MVALoop(); \\ must be reactivated
 return 0;
}
