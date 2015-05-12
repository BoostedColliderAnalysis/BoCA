# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (TopMass - WMass) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(kNotification , "Define Variables");

    ClearVectors();

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.WPt, "WPt");


    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");

//     AddVariable(branch_.VertexMass, "VertexMass");
//     AddVariable(branch_.MaxDisplacement, "MaxDisplacement");
//     AddVariable(branch_.MeanDisplacement, "MeanDisplacement");
//     AddVariable(branch_.SumDisplacement, "SumDisplacement");
//     AddVariable(branch_.Multipliticity, "Multipliticity");
//     AddVariable(branch_.Spread, "Spread");
//     AddVariable(branch_.VertexDeltaR, "VertexDeltaR");
//     AddVariable(branch_.VertexSpread, "VertexSpread");
//     AddVariable(branch_.EnergyFraction, "EnergyFraction");

    AddVariable(branch_.WBdt, "WBdt");
    AddVariable(branch_.BBdt, "BBdt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");

    Print(kNotification, "Variables defined");

}

TopSemiBranch hanalysis::HTopSemiTagger::GetBranch(const hanalysis::Triplet &triplet) const
{
    Print(kInformation, "Fill Top Tagger", triplet.Bdt());

    TopSemiBranch branch;
//     branch.Mass = triplet.Jet().m();
//     branch.Rap = triplet.Jet().rap();
//     branch.Phi = triplet.Jet().phi();
//     branch.Pt = triplet.Jet().pt();
//     branch.Ht = triplet.Ht();//
//     branch.BottomPt = triplet.singlet().pt();
//     branch.WPt = triplet.doublet_jet().pt();//
//     branch.DeltaPt = triplet.DeltaPt();
//     branch.DeltaM = triplet.DeltaM();
//     branch.DeltaHt = triplet.DeltaHt();
//     branch.DeltaR = triplet.DeltaR();
//     branch.DeltaRap = triplet.DeltaRap();
//     branch.DeltaPhi = triplet.DeltaPhi();
//     GetBottomInfo(branch, triplet.singlet());
//     branch.BBdt = triplet.singlet().user_info<JetInfo>().Bdt();
//     branch.WBdt = triplet.doublet().Bdt();
//     branch.Bdt = triplet.Bdt();
//     branch.Tag = triplet.Tag();
    branch.FillBranch(triplet);
    return branch;
}




void hanalysis::HTopSemiTagger::GetBottomInfo(TopSemiBranch &branch, const fastjet::PseudoJet jet) const
{
//     branch.VertexMass = jet.user_info<hanalysis::JetInfo>().VertexMass();
//     float MaxDisp = jet.user_info<hanalysis::JetInfo>().MaxDisplacement();
//     if (MaxDisp > 0) branch.MaxDisplacement = std::log10(MaxDisp);
//     else branch.MaxDisplacement = -3;
//     float MeanDisp = jet.user_info<hanalysis::JetInfo>().MeanDisplacement();
//     if (MeanDisp > 0) branch.MeanDisplacement = std::log10(MeanDisp);
//     else branch.MeanDisplacement = -3;
//     float SumDisp = jet.user_info<hanalysis::JetInfo>().SumDisplacement();
//     if (SumDisp > 0) branch.SumDisplacement = std::log10(SumDisp);
//     else branch.SumDisplacement = -3;
//     branch.Multipliticity = jet.user_info<hanalysis::JetInfo>().VertexNumber();
//     //     top_hadronic_branch.DeltaR = GetDeltaR(jet);
//     branch.Spread = GetSpread(jet);
//     branch.VertexDeltaR = GetDeltaR(jet.user_info<hanalysis::JetInfo>().VertexJet());
//     branch.VertexSpread = GetSpread(jet.user_info<hanalysis::JetInfo>().VertexJet());
//     branch.EnergyFraction = jet.user_info<hanalysis::JetInfo>().VertexEnergy() / jet.e();
}



int hanalysis::HTopSemiTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Get Top Tags");

    float pre_cut = 0;

    int WSemiId = w_semi_tagger_.WSemiId(event);
    Jets TopParticles = event.GetParticles()->Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());


    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<hanalysis::Doublet> doublets = static_cast<HWSemiTagger &>(w_semi_reader_.tagger()).GetDoublets(event, w_semi_reader_.reader());

    Jets Leptons = event.GetLeptons()->GetLeptonJets();
    Print(kInformation, "Lepton Number", Leptons.size());

    std::vector<Triplet> triplets;
    if (!boost_) {

        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue; // should be enabled again
                if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
                if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                triplet.SetTag(tag);
                triplets.emplace_back(triplet);
            }
        }

    }

    for (const auto & Jet : jets) {
        for (const auto & Lepton : Leptons) {
            Doublet doublet(Lepton);
            Triplet triplet(doublet, Jet);
            if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue; // should be enabled again
            if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
            if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
            if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
            triplet.SetTag(tag);
            triplets.emplace_back(triplet);
        }
    }

    std::vector<TopSemiBranch> top_semi_branches;
    int SemiLeptonicTopNumber = 1; // Must be 1 for the analysis!!;
    if (tag == kSignal &&
            triplets.size() > SemiLeptonicTopNumber) {
        std::sort(triplets.begin(), triplets.end(), SortByMass(TopMass));
        triplets.erase(triplets.begin() + SemiLeptonicTopNumber, triplets.end());
    }
    Print(kInformation, "Number triplets", triplets.size());

    return SaveEntries(triplets);
}



std::vector<hanalysis::Triplet>  hanalysis::HTopSemiTagger::GetTriplets(HEvent &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get Bdt");

    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<hanalysis::Doublet> doublets = static_cast<HWSemiTagger &>(w_semi_reader_.tagger()).GetDoublets(event, w_semi_reader_.reader());

    std::vector<Triplet> triplets;
    if (!boost_) {

        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                branch_ = GetBranch(triplet);
                triplet.SetBdt(Bdt(reader));
                triplets.emplace_back(triplet);
            }
        }
    }

    for (const auto & Jet : jets) {
        for (const auto & Predoublet : doublets) {
            Doublet doublet(Predoublet.Singlet1());
            Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - TopMass) > TopWindow) continue; // reactivate this check
            branch_ = GetBranch(triplet);
            triplet.SetBdt(Bdt(reader));
            triplets.emplace_back(triplet);
        }
    }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());

    return triplets;
}



float hanalysis::HTopSemiTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(kDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float hanalysis::HTopSemiTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}









