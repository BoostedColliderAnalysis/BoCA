# include "../include/SignatureTagger.hh"

namespace higgscpv {

SignatureTagger::SignatureTagger()
{
//    debug_level_ = kDebug;
    Print(kNotification , "Constructor");
    set_tagger_name("Signature");
    higgs_reader_.set_tagger(higgs_tagger_);
    triplet_pair_reader_.set_tagger(triplet_pair_tagger_);
    DefineVariables();
}

void SignatureTagger::DefineVariables()
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
    AddVariable(branch_.HardTopPt, "HardTopPt");
    AddVariable(branch_.SoftTopPt, "SoftTopPt");
    AddVariable(branch_.Bdt1, "Bdt1");
    AddVariable(branch_.Bdt2, "Bdt2");
    AddSpectator(branch_.Tag, "Tag");
}


int SignatureTagger::Train(analysis::Event &event,analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Train");
    std::vector<analysis::Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    if (sextets.empty()) {
Print(kInformation, "No sextets", sextets.size());
return 0;
}

    analysis::Jets HiggsParticles = event.Partons().GenParticles();
    analysis::Jets Even = analysis::copy_if_abs_particle(HiggsParticles, HiggsId);
    analysis::Jets Odd = analysis::copy_if_abs_particle(HiggsParticles, CpvHiggsId);
    HiggsParticles = analysis::Join(Even,Odd);

    std::vector<analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    if (doublets.empty()) Print(kInformation, "No doublets", doublets.size());

    std::vector<analysis::Doublet> final_doublets;
    switch (tag) {
    case kSignal :
        final_doublets = analysis::CopyIfClose(doublets, HiggsParticles);
    case kBackground :
        final_doublets = doublets;
    }
if(final_doublets.empty()) return 0;

    std::vector<analysis::Octet62> octets;
    for (const auto & doublet : final_doublets) {
        for (const auto & sextet : sextets) {
            analysis::Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty()) Print(kInformation, "No octets", octets.size());

    if (tag == kSignal) octets = ReduceResult(octets,1);
    return SaveEntries(octets);
}


std::vector< analysis::Octet62 > SignatureTagger::Multiplets(analysis::Event& event, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader)
{
    Print(kInformation, "Multiplets");

    std::vector<analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    Print(kInformation, "Doublets", doublets.size());
    std::vector<analysis::Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    Print(kInformation, "Sextets", sextets.size());
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

}
