# include "EventTagger.hh"

namespace higgscpv
{

EventTagger::EventTagger()
{
    Print(kNotification , "Constructor");
//     debug_level_ = kDebug;
    set_tagger_name("Event");
    signature_reader_.set_tagger(signature_tagger_);
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void EventTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.LeptonNumber, "LeptonNumber");
    AddVariable(branch_.JetNumber, "JetNumber");
    AddVariable(branch_.BottomNumber, "BottomNumber");
    AddVariable(branch_.MissingEt, "MissingEt");
    AddVariable(branch_.ScalarHt, "ScalarHt");
    AddVariable(branch_.LeptonHt, "LeptonHt");

    AddVariable(branch_.JetMass, "JetMass");
    AddVariable(branch_.JetPt, "JetPt");
    AddVariable(branch_.JetHt, "JetHt");
    AddVariable(branch_.JetPhi, "JetPhi");
    AddVariable(branch_.JetRap, "JetRap");

    AddVariable(branch_.Bdt1, "Bdt1");
    AddVariable(branch_.Bdt2, "Bdt2");
    AddSpectator(branch_.Tag, "Tag");
}

int EventTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
  Print(kInformation, "Train");
    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    std::vector<analysis::Octet62> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    Print(kInformation, "Octets", octets.size());
    std::vector< analysis::MultipletEvent< analysis::Octet62 > > multipletevents;
    for (const auto octet : octets) {
        analysis::MultipletEvent< analysis::Octet62 > multipletevent(octet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< analysis::MultipletEvent< analysis::Octet62 > > EventTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Print(kInformation, "Multiplets");
    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    std::vector<analysis::Octet62> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    std::vector< analysis::MultipletEvent< analysis::Octet62 > > multipletevents;
    for (const auto octet : octets) {
        analysis::MultipletEvent< analysis::Octet62 > multipletevent(octet, event,jets);
        branch_ = branch(multipletevent);
        multipletevent.SetBdt(Bdt(reader));
        multipletevents.emplace_back(multipletevent);
    }
    return ReduceResult(multipletevents);
}

}
