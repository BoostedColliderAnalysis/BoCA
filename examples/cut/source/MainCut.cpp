#include "include/Analysis.hh"
#include "include/Tagger.hh"

int main(){
//   Analysis<boca::standardmodel::tagger::Bottom> bottom;
//   bottom.Run(boca::Output::normal);
  Analysis<Tagger> global;
  global.Run(boca::Output::efficiency);
}
