# include "../include/SignatureTagger.hh"

namespace higgscpv
{

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
    AddVariable(branch().BottomBdt, "BottomBdt");
    AddVariable(branch().PairBottomBdt, "PairBottomBdt");
    AddVariable(branch().HardTopPt, "HardTopPt");
    AddVariable(branch().SoftTopPt, "SoftTopPt");
    AddVariable(branch().Bdt1, "Bdt1");
    AddVariable(branch().Bdt2, "Bdt2");
    AddVariable(branch().Rho, "Rho");
    AddSpectator(branch().Tag, "Tag");
}


int SignatureTagger::Train(analysis::Event &event, analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Train");
    std::vector<analysis::Sextet> sextets = triplet_pair_reader_.Multiplets<TopLeptonicPairTagger>(event);
    if (sextets.empty()) {
        Print(kInformation, "No sextets", sextets.size());
        return 0;
    }

    std::vector<analysis::Doublet> doublets = higgs_reader_.Multiplets<analysis::HiggsTagger>(event);
    if (doublets.empty()) Print(kInformation, "No doublets", doublets.size());

    std::vector<analysis::Doublet> final_doublets;
    switch (tag) {
    case kSignal : {
        analysis::Jets HiggsParticles = event.Partons().GenParticles();
        analysis::Jets Even = analysis::copy_if_abs_particle(HiggsParticles, HiggsId);
        analysis::Jets Odd = analysis::copy_if_abs_particle(HiggsParticles, CpvHiggsId);
        HiggsParticles = analysis::Join(Even, Odd);
        final_doublets = analysis::CopyIfClose(doublets, HiggsParticles);
        break;
    }
    case kBackground :
        final_doublets = doublets;
        break;
    }
    if (final_doublets.empty()) return 0;

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

    if (tag == kSignal) octets = ReduceResult(octets, 1);
    return SaveEntries(octets);
}


std::vector< analysis::Octet62 > SignatureTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
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
            octet.SetBdt(Bdt(octet,reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}
