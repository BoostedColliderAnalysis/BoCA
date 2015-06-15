# include "EventChargedTagger.hh"

namespace heavyhiggs {

EventChargedTagger::EventChargedTagger()
{
//       DebugLevel = kDebug;
    Print(kInformation , "Constructor");
    set_tagger_name("ChargedeventSemi");
    bottom_reader_.set_tagger(bottom_tagger_);
    signature_semi_reader_.set_tagger(signature_semi_tagger_);
    DefineVariables();
}

void EventChargedTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch().LeptonNumber, "LeptonNumber");
    AddVariable(branch().JetNumber, "JetNumber");
    AddVariable(branch().BottomNumber, "BottomNumber");
    AddVariable(branch().ScalarHt, "ScalarHt");

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

    AddVariable(branch().HiggsMass, "HiggsMass");
    AddVariable(branch().PairRap, "PairRap");
    AddVariable(branch().HiggsBdt, "HiggsBdt");
    AddVariable(branch().SignatureBdt, "SignatureBdt");
    AddVariable(branch().BottomBdt, "BottomBdt");
    AddVariable(branch().PairBottomBdt, "PairBottomBdt");

    AddVariable(branch().BottomBdt1, "BottomBdt1");
    AddVariable(branch().BottomBdt2, "BottomBdt2");
    AddVariable(branch().BottomBdt3, "BottomBdt3");
    AddVariable(branch().BottomBdt4, "BottomBdt4");
    AddVariable(branch().BottomBdt5, "BottomBdt5");
    AddVariable(branch().BottomBdt6, "BottomBdt6");
    AddVariable(branch().BottomBdt7, "BottomBdt7");
    AddVariable(branch().BottomBdt8, "BottomBdt8");
    AddVariable(branch().BottomBdt12, "BottomBdt12");
    AddVariable(branch().BottomBdt34, "BottomBdt34");
    AddVariable(branch().BottomBdt56, "BottomBdt56");
    AddVariable(branch().BottomBdt78, "BottomBdt78");

    AddVariable(branch().RestNumber, "RestNumber");
    AddVariable(branch().RestM, "RestM");
    AddVariable(branch().RestPt, "RestPt");
    AddVariable(branch().RestHt, "RestHt");
    AddVariable(branch().RestPhi, "RestPhi");
    AddVariable(branch().RestRap, "RestRap");
    AddVariable(branch().RestBdt, "RestBdt");
    AddVariable(branch().LeptonHt, "LeptonHt");
    AddVariable(branch().MissingEt, "MissingEt");

    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");

    Print(kNotification, "Variables defined");

}

int EventChargedTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets Leptons = event.Leptons().leptons();
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets<SignatureChargedTagger>(event);

    std::vector<analysis::MultipletEvent<Octet44>> events;
    for (const auto & octet : octets) {
      analysis::MultipletEvent<Octet44> octetevent(octet,event,jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(ReduceResult(events,1));
}


std::vector<analysis::MultipletEvent<Octet44>> EventChargedTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  Print(kInformation, "event Tags");
  analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    std::vector<Octet44> octets = signature_semi_reader_.Multiplets<SignatureChargedTagger>(event);
    std::vector<analysis::MultipletEvent<Octet44>> multiplet_events;
    for (auto & octet : octets) {
        analysis::MultipletEvent<Octet44> multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}

}
