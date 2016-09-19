#include "tthh/Analysis.hh"
#include "tthh/tagger/Global.hh"

int main(){
//   Analysis<boca::standardmodel::tagger::Bottom> bottom;
//   bottom.Run(boca::Output::normal);
  tthh::Analysis<tthh::tagger::Global> global;
  global.Run(boca::Output::efficiency);
}
