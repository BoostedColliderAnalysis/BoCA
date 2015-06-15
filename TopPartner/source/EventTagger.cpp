# include "EventTagger.hh"

namespace toppartner
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

    AddVariable(branch().Mass, "Mass");
    AddVariable(branch().Pt, "Pt");
    AddVariable(branch().Rap, "Rap");
    AddVariable(branch().Phi, "Phi");
    AddVariable(branch().Ht, "Ht");

    AddVariable(branch().DeltaPt, "DeltaPt");
    AddVariable(branch().DeltaHt, "DeltaHt");
    AddVariable(branch().DeltaM, "DeltaM");
    AddVariable(branch().DeltaRap, "DeltaRap");
    AddVariable(branch().DeltaPhi, "DeltaPhi");
    AddVariable(branch().DeltaR, "DeltaR");
    AddVariable(branch().Rho, "Rho");

    AddVariable(branch().LeptonNumber, "LeptonNumber");
    AddVariable(branch().JetNumber, "JetNumber");
    AddVariable(branch().BottomNumber, "BottomNumber");
    AddVariable(branch().MissingEt, "MissingEt");
    AddVariable(branch().ScalarHt, "ScalarHt");
    AddVariable(branch().LeptonHt, "LeptonHt");

    AddVariable(branch().JetMass, "JetMass");
    AddVariable(branch().JetPt, "JetPt");
    AddVariable(branch().JetHt, "JetHt");
    AddVariable(branch().JetPhi, "JetPhi");
    AddVariable(branch().JetRap, "JetRap");

    AddVariable(branch().Bdt1, "Bdt1");
    AddVariable(branch().Bdt2, "Bdt2");
    AddSpectator(branch().Tag, "Tag");
}

int EventTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
  Print(kInformation, "Train");
    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    std::vector<Quattuordecuplet> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    Print(kInformation, "Octets", octets.size());
    std::vector< analysis::MultipletEvent< Quattuordecuplet > > multipletevents;
    for (const auto octet : octets) {
        analysis::MultipletEvent< Quattuordecuplet > multipletevent(octet, event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector< analysis::MultipletEvent< Quattuordecuplet > > EventTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Print(kInformation, "Multiplets");
    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    std::vector<Quattuordecuplet> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    std::vector< analysis::MultipletEvent< Quattuordecuplet > > multiplet_events;
    for (const auto octet : octets) {
        analysis::MultipletEvent< Quattuordecuplet > multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}

}
