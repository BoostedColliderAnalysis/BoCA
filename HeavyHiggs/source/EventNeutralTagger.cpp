# include "EventNeutralTagger.hh"

heavyhiggs::EventNeutralTagger::EventNeutralTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("EventNeutral");
    bottom_reader_.set_tagger(bottom_tagger_);
    signature_neutral_reader_.set_tagger(signature_neutral_tagger_);
    DefineVariables();
}

void heavyhiggs::EventNeutralTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");

    AddSpectator(branch_.LeptonNumber, "LeptonNumber");
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

    AddVariable(branch_.HardTopPt, "HardTopPt");
    AddVariable(branch_.SoftTopPt, "SoftTopPt");

    AddVariable(branch_.MissingEt, "MissingEt");

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

    AddVariable(branch_.SubBottomBdt1, "SubBottomBdt1");
    AddVariable(branch_.SubBottomBdt2, "SubBottomBdt2");
    AddVariable(branch_.SubBottomBdt3, "SubBottomBdt3");
    AddVariable(branch_.SubBottomBdt4, "SubBottomBdt4");
    AddVariable(branch_.SubBottomBdt5, "SubBottomBdt5");
    AddVariable(branch_.SubBottomBdt6, "SubBottomBdt6");
    AddVariable(branch_.SubBottomBdt7, "SubBottomBdt7");
    AddVariable(branch_.SubBottomBdt8, "SubBottomBdt8");
    AddVariable(branch_.SubBottomBdt12, "SubBottomBdt12");
    AddVariable(branch_.SubBottomBdt34, "SubBottomBdt34");
    AddVariable(branch_.SubBottomBdt56, "SubBottomBdt56");
    AddVariable(branch_.SubBottomBdt78, "SubBottomBdt78");

    AddVariable(branch_.RestNumber, "RestNumber");
    AddVariable(branch_.RestM, "RestM");
    AddVariable(branch_.RestPt, "RestPt");
    AddVariable(branch_.RestHt, "RestHt");
    AddVariable(branch_.RestPhi, "RestPhi");
    AddVariable(branch_.RestRap, "RestRap");
    AddVariable(branch_.RestBdt, "RestBdt");
    AddVariable(branch_.LeptonHt, "LeptonHt");

    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int heavyhiggs::EventNeutralTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");

    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets leptons = event.Leptons().leptons();

    std::vector<analysis::Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);

    std::vector<analysis::MultipletEvent<analysis::Octet62>> events;
    for (const auto & octet : octets) {
        analysis::MultipletEvent<analysis::Octet62> octetevent(octet);
        octetevent.Setglobal_observables(analysis::GlobalObservables(event));
        octetevent.SetLeptons(leptons);
        octetevent.SetTotalJets(jets);
//         octetevent.SetSubJets(SubJets);
        octetevent.SetTag(tag);
        for (const auto & Jet : jets)  octetevent.AddRestJet(Jet);
        events.emplace_back(octetevent);
    }
    return SaveEntries(events);
}

std::vector<analysis::MultipletEvent<analysis::Octet62>> heavyhiggs::EventNeutralTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "event Tags");
    std::vector<analysis::Octet62> octets = signature_neutral_reader_.Multiplets<SignatureNeutralTagger>(event);


    analysis::Jets jets = bottom_reader_.Multiplets<analysis::BottomTagger>(event);
    analysis::Jets Leptons = event.Leptons().leptons();

    std::vector<analysis::MultipletEvent<analysis::Octet62>> events;
    for (const auto & octet : octets) {
        analysis::MultipletEvent<analysis::Octet62> octetevent(octet, analysis::GlobalObservables(event));
        for (const auto & Jet : jets)  octetevent.AddRestJet(Jet);
        octetevent.SetLeptons(Leptons);
        octetevent.SetTotalJets(jets);
//         octetevent.SetSubJets(SubJets);
        branch_ = branch(octetevent);
        octetevent.SetBdt(Bdt(reader));
        events.emplace_back(octetevent);
    }

    std::sort(events.begin(), events.end());
    if (events.size() > 1) events.erase(events.begin() + 1, events.end());
    Print(kInformation, "event Number", events.size(), jets.size());
    return events;
}

