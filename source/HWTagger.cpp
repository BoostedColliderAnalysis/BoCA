# include "HWTagger.hh"

analysis::HWTagger::HWTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    DefineVariables();

}

void analysis::HWTagger::SetTagger(const HBottomTagger &NewBottomTagger)
{
    Print(kNotification, "Set Tagger");
    BottomTagger = NewBottomTagger;
    WMassWindow = 20;
    DefineVariables();
}

void analysis::HWTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
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

WHadronicBranch analysis::HWTagger::GetBranch(const Doublet &doublet) const
{
    Print(kInformation, "FillPairTagger", doublet.Bdt());
    WHadronicBranch w_branch;
    w_branch.Mass = doublet.Jet().m();
    w_branch.Rap = doublet.Jet().rap();
    w_branch.Phi = doublet.Jet().phi();
    w_branch.Pt = doublet.Jet().pt();
    w_branch.Ht = doublet.Ht();
    w_branch.DeltaPt = std::abs(doublet.DeltaPt());
    w_branch.DeltaR = doublet.DeltaR();
    w_branch.DeltaRap = std::abs(doublet.DeltaRap());
    w_branch.DeltaPhi = std::abs(doublet.DeltaPhi());
    w_branch.Bdt = doublet.Bdt();
    w_branch.Tag = doublet.Tag();
    return w_branch;

}

std::vector<WHadronicBranch> analysis::HWTagger::GetBranches(analysis::Event &event, const analysis::Object::Tag Tag)
{
    Print(kInformation, "Get W Tags");
    std::vector<Doublet> doublets;

    Jets jets = GetJets(event);
    Print(kInformation, "Jets Number", jets.size());
    jets = BottomTagger.GetJetBdt(jets, BottomReader);
    Print(kInformation, "Bottom Tagger Number", jets.size());

    Jets WKids = GetWDaughters(event);
    int WHadId = WId;
    if (!WKids.empty()) WHadId = GetWHadId(WKids);

    // 2 Jets form 1 W
    Jets JetPairs;
    if (!WKids.empty()) std::sort(jets.begin(), jets.end(), MinDeltaR(WKids.at(0)));
    if (Tag == kSignal && jets.size() > 1) JetPairs.push_back(jets.front());
    if (Tag == kBackground && jets.size() > 1) JetPairs.insert(JetPairs.end(), jets.begin() + 1 , jets.end());

    if (WKids.size() > 1) std::sort(jets.begin(), jets.end(), MinDeltaR(WKids.at(1)));
    if (Tag == kSignal && jets.size() > 1) JetPairs.push_back(jets.front());
    if (Tag == kSignal && JetPairs.size() != 2) Print(kError, "lost the W jets", JetPairs.size());

    for (const auto & Jet1 : JetPairs) {
        for (const auto & Jet2 : JetPairs) {
            if (Jet1.delta_R(Jet2) < detector_geometry.JetConeSize) continue;
            Doublet doublet(Jet1, Jet2);
            if (Tag == kSignal && std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
            doublets.push_back(doublet);
        }
    }


    Jets WParticles = event.Partons().Generator();
    WParticles = RemoveIfWrongParticle(WParticles, WHadId);
    fastjet::PseudoJet WParticle;
    if (Tag == kSignal) {
        if (WParticles.size() == 1) {
            WParticle = WParticles.front();
            std::sort(jets.begin(), jets.end(), MinDeltaR(WParticle));
        } else Print(kError, "Where is the W?", WParticles.size());
    }

//  1 Jet (2 subjets) form(s) 1 W
    Jets WJets;
    if (Tag == kSignal && jets.size() > 1) WJets.push_back(jets.front());
    if (Tag == kBackground && jets.size() > 1) WJets.insert(WJets.end(), jets.begin() + 1 , jets.end());
    for (const auto & Jet : WJets) {
        Jets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                Doublet doublet(Piece1, Piece2);
                if (Tag == kSignal && std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
                if (Tag == kSignal && doublet.Jet().delta_R(WParticle) > detector_geometry.JetConeSize) continue;
                if (Tag == kBackground && doublet.Jet().delta_R(WParticle) < detector_geometry.JetConeSize) continue;
                doublets.push_back(doublet);
            }
        }
    }
//
//     Jets TopParticles = event.Partons().Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(sgn(WHadId)*TopId)), TopParticles.end());
//     Print(kInformation, "Particle size", TopParticles.size());
//     if (TopParticles.size() != 1) Print(kError, "Where is the Top?", TopParticles.size());
//     std::sort(jets.begin(), jets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == HSignal && jets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());

    // W is in 2 of 3 subjets
    for (const auto & Jet : WJets) {
        Jets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                Doublet doublet(Piece1, Piece2);
                if (Tag == kSignal && std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
                if (Tag == kSignal && doublet.Jet().delta_R(WParticle) > detector_geometry.JetConeSize) continue;
                if (Tag == kBackground && doublet.Jet().delta_R(WParticle) < detector_geometry.JetConeSize) continue;
                doublets.push_back(doublet);
            }
    }

    // W is in 1 of 2 subjet
    for (const auto & Jet : jets)  {
        Jets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece : Pieces) {
            Doublet doublet(Piece);
            if (Tag == kSignal && std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
            if (Tag == kSignal && doublet.Jet().delta_R(WParticle) > detector_geometry.JetConeSize) continue;
            if (Tag == kBackground && doublet.Jet().delta_R(WParticle) < detector_geometry.JetConeSize) continue;
            doublets.push_back(doublet);
        }
    }



    const int WNumber = 1; // MUST BE 1 FOR THE ANALYSIS
//     std::sort(doublets.begin(), doublets.end(), MinDeltaR(WParticles));
    std::sort(doublets.begin(), doublets.end(), SortByMass(WMass));
    if (Tag == kSignal && doublets.size() > WNumber) doublets.erase(doublets.begin() + WNumber, doublets.end());
    if (Tag == kBackground && doublets.size() > WNumber) doublets.erase(doublets.begin());

    std::vector<WHadronicBranch> Branches;
    for (const auto & doublet : doublets) Branches.push_back(GetBranch(doublet));
    return Branches;
}

// analysis::Object::HTag analysis::HWTagger::GetTag(const Doublet &doublet)
// {
//     Print(kInformation, "Get doublet Tag");
//
//     if (std::abs(doublet.Singlet1().user_info<JetInfo>().MaximalId()) != WId) return HBackground;
//
//     if (doublet.Singlet1().user_info<JetInfo>().MaximalId() != doublet.Singlet2().user_info<JetInfo>().MaximalId()) return HBackground;
//
//     return HSignal;
// }

// analysis::Object::HTag analysis::HWTagger::GetTag(const fastjet::PseudoJet &Singlet)
// {
//     Print(kInformation, "Get Singlet Tag");
//
//     if (std::abs(Singlet.user_info<JetInfo>().MaximalId()) != WId) return HBackground;
//     return HSignal;
// }

Jets analysis::HWTagger::GetWDaughters(Event &event)
{
    Jets WKids = event.Partons().Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(kError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfLetpons(WKids);
    if (WKids.size() != 2) Print(kError, "Where is the W 2?", WKids.size());
    else Print(kInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<analysis::JetInfo>().constituents().front().family().particle().Id), GetParticleName(WKids.at(1).user_info<analysis::JetInfo>().constituents().front().family().particle().Id), GetParticleName(WKids.at(0).user_info<analysis::JetInfo>().constituents().front().family().Mother1Id), GetParticleName(WKids.at(1).user_info<analysis::JetInfo>().constituents().front().family().Mother1Id));
    return WKids;
}

int analysis::HWTagger::GetWHadId(const Jets &jets)
{
    if (jets.size() < 1) return WId;
    else return jets.at(0).user_info<analysis::JetInfo>().constituents().front().family().Mother1Id;
}


std::vector<analysis::Doublet> analysis::HWTagger::GetBdt(const Jets &jets, const analysis::HReader &WReader, analysis::HBottomTagger &BottomTagger, analysis::HReader &BottomReader)
{
    Print(kInformation, "Get doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet(*Jet1, *Jet2);
            if (doublet.DeltaR() < detector_geometry.MinCellResolution) continue;
            if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
            Branch = GetBranch(doublet);
            doublet.SetBdt(WReader.Bdt());
            doublets.push_back(doublet);
        }

//  1 Jet (2 subjets) form(s) 1 W
    for (const auto & Jet : jets)  {
        Jets Pieces = GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                Doublet doublet(Piece1, Piece2);
                if (doublet.DeltaR() < detector_geometry.MinCellResolution) continue;
                if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
                Branch = GetBranch(doublet);
                doublet.SetBdt(WReader.Bdt());
                doublets.push_back(doublet);
            }
        }
    }


// W is in 2 of 3 subjets
    for (const auto & Jet : jets)  {
        Jets Pieces = GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2)continue;
                Doublet doublet(Piece1, Piece2);
                if (doublet.DeltaR() < detector_geometry.MinCellResolution) continue;
                if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
                Branch = GetBranch(doublet);
                doublet.SetBdt(WReader.Bdt());
                doublets.push_back(doublet);
            }
    }

    //  1 of 2 subjets are the W
    for (const auto & Jet : jets)  {
      Jets Pieces = GetSubJets(Jet, 2);
      Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
      for (const auto & Piece : Pieces) {
          Doublet doublet(Piece);
          if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
          Branch = GetBranch(doublet);
          doublet.SetBdt(WReader.Bdt());
          doublets.push_back(doublet);
        }
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<analysis::Doublet> analysis::HWTagger::GetBdt(const Jets &jets, const analysis::HReader &WReader)
{
  Print(kInformation, "Get doublet Bdt");

  std::vector<Doublet>  doublets;
  for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
    for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
      Doublet doublet(*Jet1, *Jet2);
//       if (doublet.DeltaR() < detector_geometry.MinCellResolution) continue;
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(doublet);
      doublet.SetBdt(WReader.Bdt());
      doublets.push_back(doublet);
    }

  for (const auto & Jet : jets) {
      Doublet doublet(Jet);
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(doublet);
      doublet.SetBdt(WReader.Bdt());
      doublets.push_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<analysis::Doublet> analysis::HWTagger::GetPairBdt(const Jets &jets, const analysis::HReader &WReader)
{
  Print(kInformation, "Get doublet Bdt");

  std::vector<Doublet>  doublets;
  for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
    for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
      Doublet doublet(*Jet1, *Jet2);
//       if (doublet.DeltaR() < detector_geometry.MinCellResolution) continue;
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(doublet);
      doublet.SetBdt(WReader.Bdt());
      doublets.push_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<analysis::Doublet> analysis::HWTagger::GetSingletBdt(const Jets &jets, const analysis::HReader &WReader)
{
  Print(kInformation, "Get doublet Bdt");

  std::vector<Doublet>  doublets;
    for (const auto & Jet : jets) {
      Doublet doublet(Jet);
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
      Branch = GetBranch(doublet);
      doublet.SetBdt(WReader.Bdt());
      doublets.push_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}


analysis::Doublet analysis::HWTagger::GetBdt(Doublet &doublet, const analysis::HReader &WReader)
{
    Print(kInformation, "Get doublet Bdt");

    Branch = GetBranch(doublet);
    doublet.SetBdt(WReader.Bdt());
    return doublet;
}

// std::vector<ParticleBranch> analysis::HWTagger::GetconstituentBranches()
// {
//
//     Print(kInformation, "Get Higgs Tags");
//
//     std::vector<Doublet> JetPairs;
//
//     Print(kInformation, "Number of Jet Pairs", JetPairs.size());
//
//     std::vector<ParticleBranch> constituentBranches;
//     for (const auto & JetPair : JetPairs) for (const auto & constituent : JetPair.constituents()) constituentBranches.push_back(GetBranch(constituent));
//     return constituentBranches;
// }
//
// ParticleBranch analysis::HWTagger::GetBranch(const HKinematics &Vector)
// {
//     Print(kInformation, "Fill constituent Branch");
//
//     ParticleBranch constituentBranch;
//     constituentBranch.Pt = Vector.GetPt();
//     constituentBranch.Rap = Vector.GetRap();
//     constituentBranch.Phi = Vector.GetPhi();
//     return constituentBranch;
// }
