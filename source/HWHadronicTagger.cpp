# include "HWHadronicTagger.hh"

hanalysis::HWHadronicTagger::HWHadronicTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();

}

void hanalysis::HWHadronicTagger::SetTagger(const HBottomTagger &NewBottomTagger)
{
    Print(HNotification, "Set Tagger");
    BottomTagger = NewBottomTagger;
    WMassWindow = 20;
    DefineVariables();
}

void hanalysis::HWHadronicTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    SetTaggerName("WHadronic");
    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.Bdt, "Bdt");

    AddSpectator(Branch.Tag, "Tag");
}

HWBranch hanalysis::HWHadronicTagger::GetBranch(const HDoublet &Doublet) const
{
    Print(HInformation, "FillPairTagger", Doublet.Bdt());
    HWBranch WBranch;
    WBranch.Mass = Doublet.Jet().m();
    WBranch.Rap = Doublet.Jet().rap();
    WBranch.Phi = Doublet.Jet().phi();
    WBranch.Pt = Doublet.Jet().pt();
    WBranch.Ht = Doublet.Ht();
    WBranch.DeltaPt = std::abs(Doublet.DeltaPt());
    WBranch.DeltaR = Doublet.DeltaR();
    WBranch.DeltaRap = std::abs(Doublet.DeltaRap());
    WBranch.DeltaPhi = std::abs(Doublet.DeltaPhi());
    WBranch.Bdt = Doublet.Bdt();
    WBranch.Tag = Doublet.Tag();
    return WBranch;

}

std::vector<HWBranch> hanalysis::HWHadronicTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
{
    Print(HInformation, "Get W Tags");
    std::vector<HDoublet> Doublets;

    HJets Jets = GetJets(Event);
    Print(HInformation, "Jets Number", Jets.size());
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    Print(HInformation, "Bottom Tagger Number", Jets.size());

    HJets WKids = GetWDaughters(Event);
    int WHadId = WId;
    if (WKids.size() > 0) WHadId = GetWHadId(WKids);

    // 2 Jets form 1 W
    HJets JetPairs;
    if (WKids.size() > 0) std::sort(Jets.begin(), Jets.end(), MinDeltaR(WKids.at(0)));
    if (Tag == kSignal && Jets.size() > 1) JetPairs.push_back(Jets.front());
    if (Tag == kBackground && Jets.size() > 1) JetPairs.insert(JetPairs.end(), Jets.begin() + 1 , Jets.end());

    if (WKids.size() > 1) std::sort(Jets.begin(), Jets.end(), MinDeltaR(WKids.at(1)));
    if (Tag == kSignal && Jets.size() > 1) JetPairs.push_back(Jets.front());
    if (Tag == kSignal && JetPairs.size() != 2) Print(HError, "lost the W jets", JetPairs.size());

    for (const auto & Jet1 : JetPairs) {
        for (const auto & Jet2 : JetPairs) {
            if (Jet1.delta_R(Jet2) < DetectorGeometry.JetConeSize) continue;
            HDoublet Doublet(Jet1, Jet2);
            if (Tag == kSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            Doublets.push_back(Doublet);
        }
    }


    HJets WParticles = Event.GetParticles()->Generator();
    WParticles = RemoveIfWrongParticle(WParticles, WHadId);
    fastjet::PseudoJet WParticle;
    if (Tag == kSignal) {
        if (WParticles.size() == 1) {
            WParticle = WParticles.front();
            std::sort(Jets.begin(), Jets.end(), MinDeltaR(WParticle));
        } else Print(HError, "Where is the W?", WParticles.size());
    }

//  1 Jet (2 subjets) form(s) 1 W
    HJets WJets;
    if (Tag == kSignal && Jets.size() > 1) WJets.push_back(Jets.front());
    if (Tag == kBackground && Jets.size() > 1) WJets.insert(WJets.end(), Jets.begin() + 1 , Jets.end());
    for (const auto & Jet : WJets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Tag == kSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                if (Tag == kSignal && Doublet.Jet().delta_R(WParticle) > DetectorGeometry.JetConeSize) continue;
                if (Tag == kBackground && Doublet.Jet().delta_R(WParticle) < DetectorGeometry.JetConeSize) continue;
                Doublets.push_back(Doublet);
            }
        }
    }
//
//     HJets TopParticles = Event.GetParticles()->Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(sgn(WHadId)*TopId)), TopParticles.end());
//     Print(HInformation, "Particle size", TopParticles.size());
//     if (TopParticles.size() != 1) Print(HError, "Where is the Top?", TopParticles.size());
//     std::sort(Jets.begin(), Jets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == kSignal && Jets.size() > 1) Jets.erase(Jets.begin() + 1, Jets.end());
//     if (Tag == HBackground && Jets.size() > 0) Jets.erase(Jets.begin());

    // W is in 2 of 3 subjets
    for (const auto & Jet : WJets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Tag == kSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                if (Tag == kSignal && Doublet.Jet().delta_R(WParticle) > DetectorGeometry.JetConeSize) continue;
                if (Tag == kBackground && Doublet.Jet().delta_R(WParticle) < DetectorGeometry.JetConeSize) continue;
                Doublets.push_back(Doublet);
            }
    }

    // W is in 1 of 2 subjet
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece : Pieces) {
            HDoublet Doublet(Piece);
            if (Tag == kSignal && std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            if (Tag == kSignal && Doublet.Jet().delta_R(WParticle) > DetectorGeometry.JetConeSize) continue;
            if (Tag == kBackground && Doublet.Jet().delta_R(WParticle) < DetectorGeometry.JetConeSize) continue;
            Doublets.push_back(Doublet);
        }
    }



    const int WNumber = 1; // MUST BE 1 FOR THE ANALYSIS
//     std::sort(Doublets.begin(), Doublets.end(), MinDeltaR(WParticles));
    std::sort(Doublets.begin(), Doublets.end(), SortByMass(WMass));
    if (Tag == kSignal && Doublets.size() > WNumber) Doublets.erase(Doublets.begin() + WNumber, Doublets.end());
    if (Tag == kBackground && Doublets.size() > WNumber) Doublets.erase(Doublets.begin());

    std::vector<HWBranch> Branches;
    for (const auto & Doublet : Doublets) Branches.push_back(GetBranch(Doublet));
    return Branches;
}

// hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const HDoublet &Doublet)
// {
//     Print(HInformation, "Get Doublet Tag");
//
//     if (std::abs(Doublet.Singlet1().user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
//
//     if (Doublet.Singlet1().user_info<HJetInfo>().MaximalId() != Doublet.Singlet2().user_info<HJetInfo>().MaximalId()) return HBackground;
//
//     return kSignal;
// }

// hanalysis::HObject::HTag hanalysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
// {
//     Print(HInformation, "Get Singlet Tag");
//
//     if (std::abs(Singlet.user_info<HJetInfo>().MaximalId()) != WId) return HBackground;
//     return kSignal;
// }

HJets hanalysis::HWHadronicTagger::GetWDaughters(HEvent &Event)
{
    HJets WKids = Event.GetParticles()->Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(HError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfLetpons(WKids);
    if (WKids.size() != 2) Print(HError, "Where is the W 2?", WKids.size());
    else Print(HInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id));
    return WKids;
}

int hanalysis::HWHadronicTagger::GetWHadId(const HJets &Jets)
{
    if (Jets.size() < 1) return WId;
    else return Jets.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id;
}


std::vector<hanalysis::HDoublet> hanalysis::HWHadronicTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &WReader, hanalysis::HBottomTagger &BottomTagger, hanalysis::HReader &BottomReader)
{
    Print(HInformation, "Get Doublet Bdt");

    // W in 2 jets
    std::vector<HDoublet>  Doublets;
    for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            HDoublet Doublet(*Jet1, *Jet2);
            if (Doublet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
            if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(WReader.Bdt());
            Doublets.push_back(Doublet);
        }

//  1 Jet (2 subjets) form(s) 1 W
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Doublet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
                if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                Branch = GetBranch(Doublet);
                Doublet.SetBdt(WReader.Bdt());
                Doublets.push_back(Doublet);
            }
        }
    }


// W is in 2 of 3 subjets
    for (const auto & Jet : Jets) {
        HJets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2)continue;
                HDoublet Doublet(Piece1, Piece2);
                if (Doublet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
                if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
                Branch = GetBranch(Doublet);
                Doublet.SetBdt(WReader.Bdt());
                Doublets.push_back(Doublet);
            }
    }

    //  1 of 2 subjets are the W
    for (const auto & Jet : Jets) {
      HJets Pieces = GetSubJets(Jet, 2);
      Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
      for (const auto & Piece : Pieces) {
          HDoublet Doublet(Piece);
          if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
          Branch = GetBranch(Doublet);
          Doublet.SetBdt(WReader.Bdt());
          Doublets.push_back(Doublet);
        }
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());
    return Doublets;
}

std::vector<hanalysis::HDoublet> hanalysis::HWHadronicTagger::GetBdt(const HJets &Jets, const hanalysis::HReader &WReader)
{
  Print(HInformation, "Get Doublet Bdt");

  std::vector<HDoublet>  Doublets;
  for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
    for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
      HDoublet Doublet(*Jet1, *Jet2);
//       if (Doublet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
//       if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(Doublet);
      Doublet.SetBdt(WReader.Bdt());
      Doublets.push_back(Doublet);
    }

  for (const auto & Jet : Jets){
      HDoublet Doublet(Jet);
//       if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(Doublet);
      Doublet.SetBdt(WReader.Bdt());
      Doublets.push_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());
    return Doublets;
}

std::vector<hanalysis::HDoublet> hanalysis::HWHadronicTagger::GetPairBdt(const HJets &Jets, const hanalysis::HReader &WReader)
{
  Print(HInformation, "Get Doublet Bdt");

  std::vector<HDoublet>  Doublets;
  for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1)
    for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
      HDoublet Doublet(*Jet1, *Jet2);
//       if (Doublet.DeltaR() < DetectorGeometry.MinCellResolution) continue;
//       if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(Doublet);
      Doublet.SetBdt(WReader.Bdt());
      Doublets.push_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());
    return Doublets;
}

std::vector<hanalysis::HDoublet> hanalysis::HWHadronicTagger::GetSingletBdt(const HJets &Jets, const hanalysis::HReader &WReader)
{
  Print(HInformation, "Get Doublet Bdt");

  std::vector<HDoublet>  Doublets;
    for (const auto & Jet : Jets){
      HDoublet Doublet(Jet);
//       if (std::abs(Doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(Doublet);
      Doublet.SetBdt(WReader.Bdt());
      Doublets.push_back(Doublet);
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());
    return Doublets;
}


hanalysis::HDoublet hanalysis::HWHadronicTagger::GetBdt(HDoublet &Doublet, const hanalysis::HReader &WReader)
{
    Print(HInformation, "Get Doublet Bdt");

    Branch = GetBranch(Doublet);
    Doublet.SetBdt(WReader.Bdt());
    return Doublet;
}

// std::vector<HParticleBranch> hanalysis::HWTagger::GetConstituentBranches()
// {
//
//     Print(HInformation, "Get Higgs Tags");
//
//     std::vector<HDoublet> JetPairs;
//
//     Print(HInformation, "Number of Jet Pairs", JetPairs.size());
//
//     std::vector<HParticleBranch> ConstituentBranches;
//     for (const auto & JetPair : JetPairs) for (const auto & Constituent : JetPair.Constituents()) ConstituentBranches.push_back(GetBranch(Constituent));
//     return ConstituentBranches;
// }
//
// HParticleBranch hanalysis::HWTagger::GetBranch(const HKinematics &Vector)
// {
//     Print(HInformation, "Fill Constituent Branch");
//
//     HParticleBranch ConstituentBranch;
//     ConstituentBranch.Pt = Vector.GetPt();
//     ConstituentBranch.Rap = Vector.GetRap();
//     ConstituentBranch.Phi = Vector.GetPhi();
//     return ConstituentBranch;
// }
