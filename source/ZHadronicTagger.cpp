# include "ZHadronicTagger.hh"

analysis::ZHadronicTagger::ZHadronicTagger()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WHadronic");
    z_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

void analysis::ZHadronicTagger::DefineVariables()
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

analysis::ZHadronicBranch analysis::ZHadronicTagger::GetBranch(const Doublet &doublet) const
{
    Print(kInformation, "FillPairTagger", doublet.Bdt());
    ZHadronicBranch branch;
    branch.Fill(doublet);
    return branch;
}

int analysis::ZHadronicTagger::Train(analysis::Event &event, PreCuts &pre_cuts, const analysis::Object::Tag tag)
{
    Print(kInformation, "Get W Tags");

    Jets z_hadronic_daughters = ZDaughters(event);

    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    Print(kInformation, "Bottom Tagger Number", jets.size());

    // 2 Jets form 1 W
    std::vector<Doublet> doublets;
    for (auto jet1 = jets.begin(); jet1 != jets.end(); ++jet1) {
        for (const auto & z_hadronic_daughter : z_hadronic_daughters) {
            switch (tag) {
            case kSignal :
                if ((*jet1).delta_R(z_hadronic_daughter) > detector_geometry().JetConeSize) continue;
                break;
            case kBackground :
                if ((*jet1).delta_R(z_hadronic_daughter) < detector_geometry().JetConeSize) continue;
                break;
            }
        }
        for (auto jet2 = jet1 + 1; jet2 != jets.end(); ++jet2) {
            if (tag == kSignal) {
                bool tagged = false;
                for (const auto & z_hadronic_daughter : z_hadronic_daughters) if ((*jet2).delta_R(z_hadronic_daughter) < detector_geometry().JetConeSize) tagged = true;
                if (!tagged) continue;
            }
            Doublet doublet(*jet1, *jet2);
            if (tag == kSignal && std::abs(doublet.Jet().m() - ZMass) > z_mass_window_) continue;
            doublets.emplace_back(doublet);
        }
    }

    int z_hadronic_id = ZHadronicId(z_hadronic_daughters);
    Jets z_particles = event.partons().Generator();
    z_particles = RemoveIfWrongParticle(z_particles, z_hadronic_id);

    Jets z_jets;
    switch (tag) {
    case kSignal :
        z_jets = CopyIfClose(jets, z_particles);
        break;
    case kBackground :
        z_jets = RemoveIfClose(jets, z_particles);
        break;
    }

//  1 Jet (2 subjets) form(s) 1 Z
    for (const auto & jet : z_jets) {
        const int sub_jet_number = 2;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetSubJetBdt(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (tag == kSignal && std::abs(doublet.Jet().m() - ZMass) > z_mass_window_) continue;
        doublets.emplace_back(doublet);
    }

    if (tag == kSignal && doublets.size() > z_particles.size()) {
        std::sort(doublets.begin(), doublets.end(), SortByMass(ZMass));
        doublets.erase(doublets.begin() + z_particles.size(), doublets.end());
    }
    return SaveEntries(doublets);
}


Jets analysis::ZHadronicTagger::ZDaughters(Event &event)
{
    Jets z_daughters = event.partons().Generator();
    z_daughters = RemoveIfWrongAbsMother(z_daughters, ZId);
    Print(kInformation, "W daughters", z_daughters.size());

    z_daughters = RemoveIfLetpons(z_daughters);
    Print(kInformation, "hadronic W daughters", z_daughters.size());
    return z_daughters;
}

int analysis::ZHadronicTagger::ZHadronicId(const Jets &jets)
{
    if (jets.empty()) return ZId;
    else return jets.front().user_info<analysis::JetInfo>().constituents().front().family().mother_1().Id;
}


std::vector<analysis::Doublet> analysis::ZHadronicTagger::GetDoublets(Event &event, const TMVA::Reader &reader)
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

    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<analysis::Doublet> analysis::ZHadronicTagger::GetJetDoublets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");
    return GetJetDoublets(static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader()), reader);
}

std::vector<analysis::Doublet> analysis::ZHadronicTagger::GetJetDoublets(const Jets &jets, const TMVA::Reader &reader)
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

std::vector<analysis::Doublet> analysis::ZHadronicTagger::GetSubJetDoublets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
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

std::vector<analysis::Doublet> analysis::ZHadronicTagger::GetDoublet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    Doublet doublet(jet_1, jet_2);
    if (doublet.DeltaR() < detector_geometry().MinCellResolution) return doublets;
    if (std::abs(doublet.Jet().m() - ZMass) > z_mass_window_) return doublets;
    branch_ = GetBranch(doublet);
    doublet.SetBdt(Bdt(reader));
    doublets.emplace_back(doublet);
    return doublets;
}

std::vector<analysis::Doublet> analysis::ZHadronicTagger::GetDoublet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    Print(kInformation, "Get doublet Bdt");
    std::vector<Doublet>  doublets;
    Jets subjets = GetSubJets(jet, 2);
    if (subjets.empty()) return doublets;
    Doublet doublet;
    if (subjets.size() == 1) doublet.SetSinglets(jet);
    else doublet.SetSinglets(subjets.at(0), subjets.at(1));
    if (std::abs(doublet.Jet().m() - ZMass) > z_mass_window_) return doublets;
    branch_ = GetBranch(doublet);
    doublet.SetBdt(Bdt(reader));
    doublets.emplace_back(doublet);
    return doublets;
}
