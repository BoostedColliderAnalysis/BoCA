# include "HReader.hh"
# include "HMvaDiscriminator.hh"


int main()
{
  hcpvhiggs::HMva Mva;
  hanalysis::HReader Reader(Mva);
//   Reader.MVALoop(); \\ must be reactivated
 return 0;
}
