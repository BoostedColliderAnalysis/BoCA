#include "tthh/Analysis.hh"
#include "tthh/Tagger.hh"

int main(){
//   Analysis<boca::standardmodel::tagger::Bottom> bottom;
//   bottom.Run(boca::Output::normal);
  tthh::Analysis<tthh::Tagger> global;
  global.Run(boca::Output::efficiency);
}
