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
    AddVariable(branch_.LeptonNumber, "LeptonNumber");
    AddVariable(branch_.JetNumber, "JetNumber");
    AddVariable(branch_.BottomNumber, "BottomNumber");
    AddVariable(branch_.ScalarHt, "ScalarHt");

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

    AddVariable(branch_.HiggsMass, "HiggsMass");
    AddVariable(branch_.PairRap, "PairRap");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");
    AddVariable(branch_.SignatureBdt, "SignatureBdt");
    AddVariable(branch_.BottomBdt, "BottomBdt");
    AddVariable(branch_.PairBottomBdt, "PairBottomBdt");

    AddVariable(branch_.BottomBdt1, "BottomBdt1");
    AddVariable(branch_.BottomBdt2, "BottomBdt2");
    AddVariable(branch_.BottomBdt3, "BottomBdt3");
    AddVariable(branch_.BottomBdt4, "BottomBdt4");
    AddVariable(branch_.BottomBdt5, "BottomBdt5");
    AddVariable(branch_.BottomBdt6, "BottomBdt6");
    AddVariable(branch_.BottomBdt7, "BottomBdt7");
    AddVariable(branch_.BottomBdt8, "BottomBdt8");
    AddVariable(branch_.BottomBdt12, "BottomBdt12");
    AddVariable(branch_.BottomBdt34, "BottomBdt34");
    AddVariable(branch_.BottomBdt56, "BottomBdt56");
    AddVariable(branch_.BottomBdt78, "BottomBdt78");

    AddVariable(branch_.RestNumber, "RestNumber");
    AddVariable(branch_.RestM, "RestM");
    AddVariable(branch_.RestPt, "RestPt");
    AddVariable(branch_.RestHt, "RestHt");
    AddVariable(branch_.RestPhi, "RestPhi");
    AddVariable(branch_.RestRap, "RestRap");
    AddVariable(branch_.RestBdt, "RestBdt");
    AddVariable(branch_.LeptonHt, "LeptonHt");
    AddVariable(branch_.MissingEt, "MissingEt");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");

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
    std::vector<analysis::MultipletEvent<Octet44>> events;
    for (auto & octet : octets) {
        analysis::MultipletEvent<Octet44> octetevent(octet, event,jets);
        branch_ = branch(octetevent);
        octetevent.SetBdt(Bdt(reader));
        events.emplace_back(octetevent);
    }
    return ReduceResult(events,1);
}

}
