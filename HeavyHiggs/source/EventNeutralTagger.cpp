# include "EventNeutralTagger.hh"

namespace heavyhiggs {

EventNeutralTagger::EventNeutralTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("EventNeutral");
    bottom_reader_.set_tagger(bottom_tagger_);
    signature_neutral_reader_.set_tagger(signature_neutral_tagger_);
    DefineVariables();
}

void EventNeutralTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");

    AddSpectator(branch().LeptonNumber, "LeptonNumber");
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

    AddVariable(branch().HardTopPt, "HardTopPt");
    AddVariable(branch().SoftTopPt, "SoftTopPt");

    AddVariable(branch().MissingEt, "MissingEt");

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

    AddVariable(branch().Bdt, "Bdt");
    AddSpectator(branch().Tag, "Tag");
}

int EventNeutralTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets leptons = event.Leptons().leptons();

    std::vector<analysis::Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);

    std::vector<analysis::MultipletEvent<analysis::Octet62>> events;
    for (const auto & octet : octets) {
      analysis::MultipletEvent<analysis::Octet62> octetevent(octet,event,jets);
        octetevent.SetTag(tag);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events);
}

std::vector<analysis::MultipletEvent<analysis::Octet62>> EventNeutralTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "event Tags");
    std::vector<analysis::Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);


    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets Leptons = event.Leptons().leptons();

    std::vector<analysis::MultipletEvent<analysis::Octet62>> multiplet_events;
    for (const auto & octet : octets) {
        analysis::MultipletEvent<analysis::Octet62> multiplet_event(octet, event,jets);
        multiplet_event.SetBdt(Bdt(multiplet_event,reader));
        multiplet_events.emplace_back(multiplet_event);
    }

    std::sort(multiplet_events.begin(), multiplet_events.end());
    if (multiplet_events.size() > 1) multiplet_events.erase(multiplet_events.begin() + 1, multiplet_events.end());
    Print(kInformation, "event Number", multiplet_events.size(), jets.size());
    return multiplet_events;
}

}
