#include "include/Analysis.hh"
#include "include/Tagger.hh"

int main(){
//   Analysis<standardmodel::tagger::Bottom> bottom;
//   bottom.Run(boca::Output::normal);
  simple::Analysis<simple::Tagger> global;
  global.Run(boca::Output::efficiency);
}
