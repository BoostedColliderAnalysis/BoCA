#include "Reader.hh"

#include "Debug.hh"

namespace analysis
{

void Reader::SetTagger(Tagger &tagger)
{
    Note();
    tagger_ = &tagger;
    AddVariable();
    BookMva();
}

void Reader::AddVariable()
{
    Note();
    const std::string default_options = "!Color:Silent";
    for (auto & observable : tagger().observables()) reader_.AddVariable(observable.expression(), observable.value());
    for (auto & spectator : tagger().spectators()) reader_.AddSpectator(spectator.expression(), spectator.value());

}

void Reader::BookMva()
{
    Note();
    const std::string bdt_weight_file = tagger().analysis_name() + "/" + tagger().bdt_weight_name();
    Note("Opening Weight File", bdt_weight_file);
    reader_.BookMVA(tagger().bdt_method_name(), bdt_weight_file);
}

int Reader::Bdt(const Event &event, analysis::PreCuts &pre_cuts) const
{
    Check(tagger_, "what is wrong with the tagger?");
    return tagger().GetBdt(event, pre_cuts, reader_);
}

analysis::Tagger &Reader::tagger() const
{
  return *tagger_;
}

const TMVA::Reader &Reader::reader() const
{
  return reader_;
}

}
