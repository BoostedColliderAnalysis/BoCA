# include "HWHadronicTagger.hh"

hanalysis::HWHadronicTagger::HWHadronicTagger()
{
    //     DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WHadronic");
    w_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void hanalysis::HWHadronicTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
    ClearVectors();
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");
}

WHadronicBranch hanalysis::HWHadronicTagger::GetBranch(const Doublet &doublet) const
{
    Print(kInformation, "FillPairTagger", doublet.Bdt());
    WHadronicBranch branch;
    branch.FillBranch(doublet);
    return branch;

}

int hanalysis::HWHadronicTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Get W Tags");

    Jets WKids = GetWDaughters(event);
    int WHadId = WId;
    if (WKids.size() > 0) WHadId = GetWHadId(WKids);

//     Jets jets = GetJets(event);
    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    Print(kInformation, "Bottom Tagger Number", jets.size());

    // 2 Jets form 1 W
    Jets JetPairs;
    if (WKids.size() > 0) std::sort(jets.begin(), jets.end(), MinDeltaRTo(WKids.at(0)));
    if (tag == kSignal && jets.size() > 1) JetPairs.emplace_back(jets.front());
    if (tag == kBackground && jets.size() > 1) JetPairs.insert(JetPairs.end(), jets.begin() + 1 , jets.end());

    if (WKids.size() > 1) std::sort(jets.begin(), jets.end(), MinDeltaRTo(WKids.at(1)));
    if (tag == kSignal && jets.size() > 1) JetPairs.emplace_back(jets.front());
    if (tag == kSignal && JetPairs.size() != 2) Print(kError, "lost the W jets", JetPairs.size());

    std::vector<Doublet> doublets;
    for (const auto & Jet1 : JetPairs) {
        for (const auto & Jet2 : JetPairs) {
            if (Jet1.delta_R(Jet2) < detector_geometry().JetConeSize) continue;
            Doublet doublet(Jet1, Jet2);
            if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
            doublets.emplace_back(doublet);
        }
    }


    Jets WParticles = event.GetParticles()->Generator();
    WParticles = RemoveIfWrongParticle(WParticles, WHadId);
    fastjet::PseudoJet WParticle;
    if (tag == kSignal) {
        if (WParticles.size() == 1) {
            WParticle = WParticles.front();
            std::sort(jets.begin(), jets.end(), MinDeltaRTo(WParticle));
        } else Print(kError, "Where is the W?", WParticles.size());
    }

//  1 Jet (2 subjets) form(s) 1 W
    Jets WJets;
    if (tag == kSignal && jets.size() > 1) WJets.emplace_back(jets.front());
    if (tag == kBackground && jets.size() > 1) WJets.insert(WJets.end(), jets.begin() + 1 , jets.end());
    for (const auto & Jet : WJets) {
        Jets Pieces = GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, bottom_reader_); // TODO reenable this
        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                Doublet doublet(Piece1, Piece2);
                if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
                if (tag == kSignal && doublet.Jet().delta_R(WParticle) > detector_geometry().JetConeSize) continue;
                if (tag == kBackground && doublet.Jet().delta_R(WParticle) < detector_geometry().JetConeSize) continue;
                doublets.emplace_back(doublet);
            }
        }
    }
//
//     Jets TopParticles = Event.GetParticles()->Generator();
//     TopParticles.erase(std::remove_if(TopParticles.begin(), TopParticles.end(), WrongId(sgn(WHadId)*TopId)), TopParticles.end());
//     Print(kInformation, "Particle size", TopParticles.size());
//     if (TopParticles.size() != 1) Print(kError, "Where is the Top?", TopParticles.size());
//     std::sort(jets.begin(), jets.end(), MinDeltaR(TopParticles.front()));
//     if (Tag == kSignal && jets.size() > 1) jets.erase(jets.begin() + 1, jets.end());
//     if (Tag == HBackground && jets.size() > 0) jets.erase(jets.begin());

    // W is in 2 of 3 subjets
    for (const auto & Jet : WJets) {
        Jets Pieces = GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, bottom_reader_); // TODO reenable this
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2) continue;
                Doublet doublet(Piece1, Piece2);
                if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
                if (tag == kSignal && doublet.Jet().delta_R(WParticle) > detector_geometry().JetConeSize) continue;
                if (tag == kBackground && doublet.Jet().delta_R(WParticle) < detector_geometry().JetConeSize) continue;
                doublets.emplace_back(doublet);
            }
    }

    // W is in 1 of 2 subjet
    for (const auto & Jet : jets) {
        Jets Pieces = GetSubJets(Jet, 2);
        //         Pieces = bottom_tagger_.GetJetBdt(Pieces, bottom_reader_); // TODO reenable this
        for (const auto & Piece : Pieces) {
            Doublet doublet(Piece);
            if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
            if (tag == kSignal && doublet.Jet().delta_R(WParticle) > detector_geometry().JetConeSize) continue;
            if (tag == kBackground && doublet.Jet().delta_R(WParticle) < detector_geometry().JetConeSize) continue;
            doublets.emplace_back(doublet);
        }
    }



    const int WNumber = 1; // MUST BE 1 FOR THE ANALYSIS
//     std::sort(doublets.begin(), doublets.end(), MinDeltaR(WParticles));
    std::sort(doublets.begin(), doublets.end(), SortByMass(WMass));
    if (tag == kSignal && doublets.size() > WNumber) doublets.erase(doublets.begin() + WNumber, doublets.end());
    if (tag == kBackground && doublets.size() > WNumber) doublets.erase(doublets.begin());

//     std::vector<WHadronicBranch> Branches;
//     for (const auto & doublet : doublets) Branches.emplace_back(GetBranch(doublet));
//     return Branches;
    return SaveEntries(doublets);
}


Jets hanalysis::HWHadronicTagger::GetWDaughters(HEvent &Event)
{
    Jets WKids = Event.GetParticles()->Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(kError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfLetpons(WKids);
    if (WKids.size() != 2) Print(kError, "Where is the W 2?", WKids.size());
    else Print(kInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<hanalysis::JetInfo>().constituents().front().Family().ParticleId), GetParticleName(WKids.at(1).user_info<hanalysis::JetInfo>().constituents().front().Family().ParticleId), GetParticleName(WKids.at(0).user_info<hanalysis::JetInfo>().constituents().front().Family().Mother1Id), GetParticleName(WKids.at(1).user_info<hanalysis::JetInfo>().constituents().front().Family().Mother1Id));
    return WKids;
}

int hanalysis::HWHadronicTagger::GetWHadId(const Jets &jets)
{
    if (jets.empty()) return WId;
    else return jets.at(0).user_info<hanalysis::JetInfo>().constituents().front().Family().Mother1Id;
}


std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetDoublets(HEvent &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");

    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());

    // 2 jets form a W
    std::vector<Doublet> doublets = GetJetDoublets(jets, reader);

    // 1 jet (2 subjets) form a W
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 2);
        doublets = JoinVectors(doublets, GetJetDoublets(pieces, reader));
    }
    GetSubJetDoublets(jets,reader,2);

    // 2 of 3 subjets form a W
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 3);
        doublets = JoinVectors(doublets, GetJetDoublets(pieces, reader));
    }

    // 1 of 2 subjets forms a W
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), 2);
        for (const auto & piece : pieces) doublets = JoinVectors(doublets, GetDoublet(piece, reader));
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetJetDoublets(HEvent &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");
    return GetJetDoublets(static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader()), reader);
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetJetDoublets(const Jets &jets, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            doublets = JoinVectors(doublets, GetDoublet(*Jet1, *Jet2, reader));
        }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{
  Print(kInformation, "Get doublet Bdt");

  std::vector<Doublet>  doublets;
  for (const auto & jet : jets) {
    Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), sub_jet_number);
    for (const auto & piece : pieces) doublets = JoinVectors(doublets, GetDoublet(piece, reader));
  }

  std::sort(doublets.begin(), doublets.end());
  doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
  return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    Doublet doublet(jet_1, jet_2);
    if (doublet.DeltaR() < detector_geometry().MinCellResolution) return doublets;
    if (std::abs(doublet.Jet().m() - WMass) > w_mass_window_) return doublets;
    branch_ = GetBranch(doublet);
    doublet.SetBdt(Bdt(reader));
    doublets.emplace_back(doublet);
    return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");
    std::vector<Doublet>  doublets;
    Doublet doublet(jet);
    if (std::abs(doublet.Jet().m() - WMass) > w_mass_window_) return doublets;
    branch_ = GetBranch(doublet);
    doublet.SetBdt(Bdt(reader));
    doublets.emplace_back(doublet);
    return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetBdt(const Jets &jets, const hanalysis::Reader &WReader)
{
    Print(kInformation, "Get doublet Bdt");

    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet(*Jet1, *Jet2);
//       if (doublet.DeltaR() < detector_geometry().MinCellResolution) continue;
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
            branch_ = GetBranch(doublet);
            doublet.SetBdt(WReader.Bdt());
            doublets.emplace_back(doublet);
        }

    for (const auto & Jet : jets) {
        Doublet doublet(Jet);
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
        branch_ = GetBranch(doublet);
        doublet.SetBdt(WReader.Bdt());
        doublets.emplace_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetPairBdt(const Jets &jets, const hanalysis::Reader &WReader)
{
    Print(kInformation, "Get doublet Bdt");

    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            Doublet doublet(*Jet1, *Jet2);
//       if (doublet.DeltaR() < detector_geometry().MinCellResolution) continue;
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
            branch_ = GetBranch(doublet);
            doublet.SetBdt(WReader.Bdt());
            doublets.emplace_back(doublet);
        }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<hanalysis::Doublet> hanalysis::HWHadronicTagger::GetSingletBdt(const Jets &jets, const hanalysis::Reader &WReader)
{
    Print(kInformation, "Get doublet Bdt");

    std::vector<Doublet>  doublets;
    for (const auto & Jet : jets) {
        Doublet doublet(Jet);
//       if (std::abs(doublet.Jet().m() - WMass) > WMassWindow) continue;
        branch_ = GetBranch(doublet);
        doublet.SetBdt(WReader.Bdt());
        doublets.emplace_back(doublet);
    }

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}


hanalysis::Doublet hanalysis::HWHadronicTagger::GetBdt(Doublet &doublet, const hanalysis::Reader &WReader)
{
    Print(kInformation, "Get doublet Bdt");

    branch_ = GetBranch(doublet);
    doublet.SetBdt(WReader.Bdt());
    return doublet;
}
