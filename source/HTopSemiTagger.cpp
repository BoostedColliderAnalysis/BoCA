# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (TopMass - WMass) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

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

    AddVariable(branch_.VertexMass, "VertexMass");
    AddVariable(branch_.MaxDisplacement, "MaxDisplacement");
    AddVariable(branch_.MeanDisplacement, "MeanDisplacement");
    AddVariable(branch_.SumDisplacement, "SumDisplacement");
    AddVariable(branch_.Multipliticity, "Multipliticity");
    AddVariable(branch_.Spread, "Spread");
    AddVariable(branch_.VertexDeltaR, "VertexDeltaR");
    AddVariable(branch_.VertexSpread, "VertexSpread");
    AddVariable(branch_.EnergyFraction, "EnergyFraction");

    AddVariable(branch_.WBdt, "WBdt");
    AddVariable(branch_.BBdt, "BBdt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");

    Print(HNotification, "Variables defined");

}

HTopSemiBranch hanalysis::HTopSemiTagger::GetBranch(const hanalysis::HTriplet &triplet) const
{
    Print(HInformation, "Fill Top Tagger", triplet.Bdt());

    HTopSemiBranch branch;
    branch.Mass = triplet.Jet().m();
    branch.Rap = triplet.Jet().rap();
    branch.Phi = triplet.Jet().phi();
    branch.Pt = triplet.Jet().pt();
    branch.Ht = triplet.Ht();

    branch.BottomPt = triplet.Singlet().pt();
    branch.WPt = triplet.DoubletJet().pt();

    branch.DeltaPt = triplet.DeltaPt();
    branch.DeltaM = triplet.DeltaM();
    branch.DeltaHt = triplet.DeltaHt();
    branch.DeltaR = triplet.DeltaR();
    branch.DeltaRap = triplet.DeltaRap();
    branch.DeltaPhi = triplet.DeltaPhi();

    GetBottomInfo(branch, triplet.Singlet());

    branch.BBdt = triplet.Singlet().user_info<HJetInfo>().Bdt();
    branch.WBdt = triplet.Doublet().Bdt();
    branch.Bdt = triplet.Bdt();
    branch.Tag = triplet.Tag();

    return branch;
}




void hanalysis::HTopSemiTagger::GetBottomInfo(HTopSemiBranch &branch, const fastjet::PseudoJet jet) const
{
    branch.VertexMass = jet.user_info<hanalysis::HJetInfo>().VertexMass();
    float MaxDisp = jet.user_info<hanalysis::HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) branch.MaxDisplacement = std::log10(MaxDisp);
    else branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<hanalysis::HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) branch.MeanDisplacement = std::log10(MeanDisp);
    else branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<hanalysis::HJetInfo>().SumDisplacement();
    if (SumDisp > 0) branch.SumDisplacement = std::log10(SumDisp);
    else branch.SumDisplacement = -3;
    branch.Multipliticity = jet.user_info<hanalysis::HJetInfo>().VertexNumber();
    //     TopHadronicBranch.DeltaR = GetDeltaR(jet);
    branch.Spread = GetSpread(jet);
    branch.VertexDeltaR = GetDeltaR(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    branch.VertexSpread = GetSpread(jet.user_info<hanalysis::HJetInfo>().VertexJet());
    branch.EnergyFraction = jet.user_info<hanalysis::HJetInfo>().VertexEnergy() / jet.e();
}



int hanalysis::HTopSemiTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag, float pre_cut)
{
    Print(HInformation, "Get Top Tags");

    int WSemiId = w_semi_tagger_.WSemiId(event);
    HJets TopParticles = event.GetParticles()->Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());


    HJets Jets = GetJets(event);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = bottom_tagger_.GetJetBdt(Jets, bottom_reader_.reader());

    HJets Leptons = event.GetLeptons()->GetLeptonJets();
    Print(HInformation, "Lepton Number", Leptons.size());

    fastjet::PseudoJet MissingEt = event.GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = w_semi_tagger_.GetBdt(Leptons, MissingEt, w_semi_reader_.reader());
    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    if (!boost_) {

        for (const auto & Jet : Jets) {
            for (const auto & Doublet : Doublets) {
                HTriplet Triplet(Doublet, Jet);
                if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue; // should be enabled again
                if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
                if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                Triplet.SetTag(tag);
                Triplets.emplace_back(Triplet);
            }
        }

    }

    for (const auto & Jet : Jets) {
        for (const auto & Lepton : Leptons) {
            HDoublet Doublet(Lepton);
            HTriplet Triplet(Doublet, Jet);
            if (tag == kSignal && std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue; // should be enabled again
            if (tag == kSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
            if (tag == kSignal && Triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
            if (tag == kBackground && Triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
            Triplet.SetTag(tag);
            Triplets.emplace_back(Triplet);
        }
    }

    std::vector<HTopSemiBranch> TopSemiBranches;
    int SemiLeptonicTopNumber = 1; // Must be 1 for the analysis!!;
    if (tag == kSignal &&
            Triplets.size() > SemiLeptonicTopNumber) {
        std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
        Triplets.erase(Triplets.begin() + SemiLeptonicTopNumber, Triplets.end());
    }
    Print(HInformation, "Number Triplets", Triplets.size());

    SaveEntries(Triplets);
    return Triplets.size();
}



std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetTriplets(HEvent &event, const TMVA::Reader &reader)
{
    Print(HInformation, "Get Bdt");

    HJets jets = bottom_reader_.GetMultiplets(event);
    std::vector<hanalysis::HDoublet> Doublets = w_semi_reader_.GetMultiplets(event);

    std::vector<HTriplet> Triplets;
    if (!boost_) {

        for (const auto & Jet : jets) {
            for (const auto & Doublet : Doublets) {
                HTriplet Triplet(Doublet, Jet);
                if (std::abs(Triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                branch_ = GetBranch(Triplet);
                Triplet.SetBdt(Bdt(reader));
                Triplets.emplace_back(Triplet);
            }
        }
    }

    for (const auto & Jet : jets) {
        for (const auto & PreDoublet : Doublets) {
            HDoublet Doublet(PreDoublet.Singlet1());
            HTriplet Triplet(Doublet, Jet);
//             if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // reactivate this check
            branch_ = GetBranch(Triplet);
            Triplet.SetBdt(Bdt(reader));
            Triplets.emplace_back(Triplet);
        }
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());

    return Triplets;
}



float hanalysis::HTopSemiTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(HDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float hanalysis::HTopSemiTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(HInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * Constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}









