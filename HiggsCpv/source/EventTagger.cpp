# include "EventTagger.hh"

higgscpv::EventTagger::EventTagger()
{
    Print(kNotification , "Constructor");
    set_tagger_name("EventTagger");
    signature_reader_.set_tagger(signature_tagger_);
    DefineVariables();
}

void higgscpv::EventTagger::DefineVariables()
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

int higgscpv::EventTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kNotification, "Train");
    std::vector<analysis::Octet62> octets = signature_reader_.Multiplets<SignatureTagger>(event);
    std::vector< analysis::MultipletEvent< analysis::Octet62 > > events;
    return SaveEntries<EventBranch>(events);
}

std::vector< analysis::MultipletEvent< analysis::Octet62 > > higgscpv::EventTagger::Multiplets(analysis::Event& event, const TMVA::Reader& reader)
{
  std::vector<analysis::Octet62> octets = signature_reader_.Multiplets<SignatureTagger>(event);
  std::vector< analysis::MultipletEvent< analysis::Octet62 > > events;
  return events;
}
