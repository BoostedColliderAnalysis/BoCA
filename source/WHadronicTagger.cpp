# include "WHadronicTagger.hh"

hanalysis::WHadronicTagger::WHadronicTagger()
{
//     DebugLevel = hanalysis::HObject::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WHadronic");
    w_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void hanalysis::WHadronicTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
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

WHadronicBranch hanalysis::WHadronicTagger::GetBranch(const Doublet &doublet) const
{
    Print(kInformation, "FillPairTagger", doublet.Bdt());
    WHadronicBranch branch;
    branch.FillBranch(doublet);
    return branch;
}

int hanalysis::WHadronicTagger::Train(hanalysis::Event &event, PreCuts &pre_cuts, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Get W Tags");

    Jets w_hadronic_daughters = GetWDaughters(event);

    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    Print(kInformation, "Bottom Tagger Number", jets.size());

    // 2 Jets form 1 W
    std::vector<Doublet> doublets;
    for (auto jet1 = jets.begin(); jet1 != jets.end(); ++jet1) {
        for (const auto & w_hadronic_daughter : w_hadronic_daughters) {
            switch (tag) {
            case kSignal :
                if ((*jet1).delta_R(w_hadronic_daughter) > detector_geometry().JetConeSize) continue;
                break;
            case kBackground :
                if ((*jet1).delta_R(w_hadronic_daughter) < detector_geometry().JetConeSize) continue;
                break;
            }
        }
        for (auto jet2 = jet1 + 1; jet2 != jets.end(); ++jet2) {
            if (tag == kSignal) {
                bool tagged = false;
                for (const auto & w_hadronic_daughter : w_hadronic_daughters) if ((*jet2).delta_R(w_hadronic_daughter) < detector_geometry().JetConeSize) tagged = true;
                if (!tagged) continue;
            }
            Doublet doublet(*jet1, *jet2);
            if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
            doublets.emplace_back(doublet);
        }
    }


    int w_hadronic_id = GetWHadId(w_hadronic_daughters);
    Jets w_particles = event.Partons().Generator();
    w_particles = RemoveIfWrongParticle(w_particles, w_hadronic_id);

    Jets w_jets;
    switch (tag) {
    case kSignal :
        w_jets = CopyIfClose(jets, w_particles);
        break;
    case kBackground :
        w_jets = RemoveIfClose(jets, w_particles);
        break;
    }

//  1 Jet (2 subjets) form(s) 1 W
    for (const auto & jet : w_jets) {
        const int sub_jet_number = 2;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
        doublets.emplace_back(doublet);
    }

// W is in 2 of 3 subjets
    for (const auto & jet : jets) {
        const int sub_jet_number = 3;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            for (auto piece2 = piece1 + 1; piece2 != pieces.end(); ++piece2) {
                Doublet doublet(*piece1, *piece2);
                if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
                doublets.emplace_back(doublet);
            }
        }
    }

// W is in 1 of 2 subjet
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (const auto & piece : pieces) {
            Doublet doublet(piece);
            if (tag == kSignal && std::abs(doublet.Jet().m() - WMass) > w_mass_window_) continue;
            continue;
            doublets.emplace_back(doublet);
        }
    }

    if (tag == kSignal && doublets.size() > w_particles.size()) {
        std::sort(doublets.begin(), doublets.end(), SortByMass(WMass));
        doublets.erase(doublets.begin() + w_particles.size(), doublets.end());
    }
    return SaveEntries(doublets);
}


Jets hanalysis::WHadronicTagger::GetWDaughters(Event &event)
{
    Jets w_daughters = event.Partons().Generator();
    w_daughters = RemoveIfWrongAbsMother(w_daughters, WId);
    Print(kInformation, "W daughters", w_daughters.size());

    w_daughters = RemoveIfLetpons(w_daughters);
    Print(kInformation, "hadronic W daughters", w_daughters.size());
    return w_daughters;
}

int hanalysis::WHadronicTagger::GetWHadId(const Jets &jets)
{
    if (jets.empty()) return WId;
    else return jets.front().user_info<hanalysis::JetInfo>().constituents().front().Family().Mother1Id;
}


std::vector<hanalysis::Doublet> hanalysis::WHadronicTagger::GetDoublets(Event &event, const TMVA::Reader &reader)
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
    GetSubJetDoublets(jets, reader, 2);

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

std::vector<hanalysis::Doublet> hanalysis::WHadronicTagger::GetJetDoublets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");
    return GetJetDoublets(static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader()), reader);
}

std::vector<hanalysis::Doublet> hanalysis::WHadronicTagger::GetJetDoublets(const Jets &jets, const TMVA::Reader &reader)
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

std::vector<hanalysis::Doublet> hanalysis::WHadronicTagger::GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
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

std::vector<hanalysis::Doublet> hanalysis::WHadronicTagger::GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader)
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

std::vector<hanalysis::Doublet> hanalysis::WHadronicTagger::GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");
    std::vector<Doublet>  doublets;
    Jets subjets = GetSubJets(jet, 2);
    if (subjets.empty()) return doublets;
    Doublet doublet;
    if (subjets.size() == 1) doublet.SetSinglets(jet);
    else doublet.SetSinglets(subjets.at(0), subjets.at(1));
    if (std::abs(doublet.Jet().m() - WMass) > w_mass_window_) return doublets;
    branch_ = GetBranch(doublet);
    doublet.SetBdt(Bdt(reader));
    doublets.emplace_back(doublet);
    return doublets;
}
