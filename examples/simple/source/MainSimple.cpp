#include "simple/Analysis.hh"
#include "simple/Tagger.hh"

int main(){
//   Analysis<standardmodel::tagger::Bottom> bottom;
//   bottom.Run(boca::Output::normal);
  simple::Analysis<simple::Tagger> global;
  global.Run(boca::Output::efficiency);
}
