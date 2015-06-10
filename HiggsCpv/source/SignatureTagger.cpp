# include "../include/SignatureTagger.hh"

higgscpv::SignatureTagger::SignatureTagger()
{
    //   DebugLevel = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("Signature");
    higgs_reader_.set_tagger(higgs_tagger_);
    triplet_pair_reader_.set_tagger(triplet_pair_tagger_);
    DefineVariables();
}

void higgscpv::SignatureTagger::DefineVariables()
{
    Print(kNotification, "Define Variables");
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
    AddVariable(branch_.BottomBdt, "BottomBdt");
    AddVariable(branch_.PairBottomBdt, "PairBottomBdt");
    AddVariable(branch_.PairBdt, "PairBdt");
    AddVariable(branch_.HiggsBdt, "HiggsBdt");
    AddVariable(branch_.HardTopPt, "HardTopPt");
    AddVariable(branch_.SoftTopPt, "SoftTopPt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}


int higgscpv::SignatureTagger::Train(analysis::Event &event, const Tag tag)
{
    Print(kInformation, "event Tags");
    std::vector<analysis::Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    if (sextets.empty())Print(kInformation, "No sextets", sextets.size());

    analysis::Jets HiggsParticles = event.Partons().GenParticles();
    analysis::Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, HeavyHiggsId, GluonId);
    analysis::Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, CPOddHiggsId, GluonId);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());

    std::vector<analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);

    std::vector<analysis::Doublet> final_doublets;
    switch (tag) {
    case kSignal :
        final_doublets = analysis::CopyIfClose(doublets, HiggsParticles);
    case kBackground :
        final_doublets = doublets;
    }

    std::vector<analysis::Octet62> octets;
    for (const auto & doublet : final_doublets) {
        for (const auto & sextet : sextets) {
            analysis::Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty())Print(kInformation, "No octets", octets.size());

    if (tag == kSignal && octets.size() > 1) {
        Print(kInformation, "more than one event", octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }
    return SaveEntries(octets);
}


std::vector< analysis::Octet62 > higgscpv::SignatureTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "event Tags");

    std::vector<analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    std::vector<analysis::Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    std::vector<analysis::Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            analysis::Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            branch_ = branch(octet);
            octet.SetBdt(Bdt(reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}
