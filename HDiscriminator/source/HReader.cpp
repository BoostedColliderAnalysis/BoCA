# include "HReader.hh"
# include "HMvaDiscriminator.hh"


int main()
{
  hcpvhiggs::HMva Mva;
  analysis::HReader Reader(Mva);
//   Reader.MVALoop(); \\ must be reactivated
 return 0;
}
