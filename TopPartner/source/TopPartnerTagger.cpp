# include "../include/TopPartnerTagger.hh"

toppartner::TopPartnerTagger::TopPartnerTagger()
{
//         DebugLevel = analysis::Object::kDetailed;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsSemi");
    top_reader_.set_tagger(top_tagger_);
    z_hadronic_reader_.set_tagger(z_hadronic_tagger);
    DefineVariables();
}

void toppartner::TopPartnerTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

int toppartner::TopPartnerTagger::Train(analysis::Event &event,  analysis::PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Get Higgs Tags");
    std::vector< analysis::Triplet> triplets = top_reader_.Multiplets<analysis::TopHadronicTagger>(event);
    std::vector< analysis::Doublet> doublets = z_hadronic_reader_.Multiplets<analysis::ZHadronicTagger>(event);
    std::vector< analysis::Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            analysis::Quintet quintet(triplet, doublet);
            if (quintet.overlap()) continue;
            quintet.SetTag(tag);
            quintets.emplace_back(quintet);
        }
    return SaveEntries<TopPartnerBranch>(quintets);
}

std::vector<analysis::Quintet>  toppartner::TopPartnerTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    std::vector< analysis::Triplet> triplets = top_reader_.Multiplets<analysis::TopHadronicTagger>(event);
    std::vector< analysis::Doublet> doublets = z_hadronic_reader_.Multiplets<analysis::ZHadronicTagger>(event);
    std::vector< analysis::Quintet > quintets;
    for (const auto & doublet : doublets)
        for (const auto & triplet : triplets) {
            analysis::Quintet quintet(triplet, doublet);
            if (quintet.overlap()) continue;
            branch_ = branch<TopPartnerBranch>(quintet);
            quintet.SetBdt(Bdt(reader));
            quintets.emplace_back(quintet);
        }
    return ReduceResult(quintets);
}


