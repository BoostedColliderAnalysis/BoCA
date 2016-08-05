#include "Analysis.hh"
#include "Tagger.hh"

int main(){
  Analysis<Tagger> analysis;
  analysis.Run(boca::Output::cut);
}
