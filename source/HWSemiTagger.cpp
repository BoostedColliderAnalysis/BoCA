# include "HWSemiTagger.hh"
# include "Reader.hh"

hanalysis::HWSemiTagger::HWSemiTagger()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    set_tagger_name("WSemi");
    w_mass_window_ = 20;
    DefineVariables();
}


void hanalysis::HWSemiTagger::DefineVariables()
{
    Print(HNotification , "Define Variables");
    ClearVectors();
    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");
    AddVariable(branch_.NeutrinoPt, "NeutrinoPt");
    AddVariable(branch_.LeptonPt, "LeptonPt");
    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddSpectator(branch_.Tag, "Tag");
    Print(HNotification, "Variables defined");
}

HWSemiBranch hanalysis::HWSemiTagger::GetBranch(const hanalysis::HDoublet &doublet) const
{
    Print(HInformation, "Fill W Tagger", doublet.Bdt());
    HWSemiBranch w_semi_branch;
    w_semi_branch.Mass = doublet.Jet().m();
    w_semi_branch.Rap = doublet.Jet().rap();
    w_semi_branch.Phi = doublet.Jet().phi();
    w_semi_branch.Pt = doublet.Jet().pt();
    w_semi_branch.Ht = doublet.Ht();
    w_semi_branch.NeutrinoPt = doublet.Singlet2().pt();
    w_semi_branch.LeptonPt = doublet.Singlet1().pt();
    w_semi_branch.DeltaPt = doublet.DeltaPt();
    w_semi_branch.DeltaR = doublet.DeltaR();
    w_semi_branch.DeltaRap = doublet.DeltaRap();
    w_semi_branch.DeltaPhi = doublet.DeltaPhi();
    w_semi_branch.Bdt = doublet.Bdt();
    w_semi_branch.Tag = doublet.Tag();
    return w_semi_branch;
}

int hanalysis::HWSemiTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Get Top Tags");

    HJets Leptons = fastjet::sorted_by_pt(event.GetLeptons()->GetLeptonJets());
    if (Leptons.size() > 1) Leptons.erase(Leptons.begin() + 1, Leptons.end());

    const fastjet::PseudoJet MissingEt = event.GetJets()->GetMissingEt();

    HJets Particles = event.GetParticles()->Generator();
    int w_semi_id = WSemiId(event);
    fastjet::PseudoJet WBoson;
    Particles = RemoveIfWrongParticle(Particles, w_semi_id);
    if (Particles.size() == 1) {
        WBoson = Particles.front();
    } else Print(HError, "Where is the W?", Particles.size());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        HDoublet PreDoublet(Lepton, MissingEt);
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        std::sort(PostDoublets.begin(), PostDoublets.end(), MinDeltaRTo(WBoson));
        for (auto & PostDoublet : PostDoublets) {
            if (tag == kSignal && std::abs(PostDoublet.Jet().m() - WMass) > w_mass_window_) continue;
            if (tag == kSignal && PostDoublet.Jet().delta_R(WBoson) > detector_geometry().JetConeSize) continue;
            if (tag == kBackground && PostDoublet.Jet().delta_R(WBoson) > detector_geometry().JetConeSize) continue;
            PostDoublet.SetTag(tag);
            Doublets.emplace_back(PostDoublet);
        }
    }
//     std::vector<HWSemiBranch> WSemiBranches;
//     for (const auto & Doublet : Doublets) WSemiBranches.emplace_back(GetBranch(Doublet));
 SaveEntries(Doublets);
//     Print(HInformation, "Number Doublets", Doublets.size());
    return Doublets.size();
}

std::vector<hanalysis::HDoublet>  hanalysis::HWSemiTagger::GetDoublets(hanalysis::HEvent &event, const TMVA::Reader &reader)
{
    Print(HInformation, "Get Triple Bdt");
    HJets NewLeptons = fastjet::sorted_by_pt(event.GetLeptons()->GetLeptonJets());
    if (NewLeptons.size() > 1) NewLeptons.erase(NewLeptons.begin() + 1, NewLeptons.end());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : NewLeptons) {
        HDoublet PreDoublet(Lepton, event.GetJets()->GetMissingEt());
        std::vector<HDoublet> PostDoublets = GetNeutrinos(PreDoublet);
        for (auto & PostDoublet : PostDoublets) {
            if (std::abs(PostDoublet.Jet().m() - WMass) > w_mass_window_) continue;
            branch_ = GetBranch(PostDoublet);
            PostDoublet.SetBdt(Bdt(reader));
            Doublets.emplace_back(PostDoublet);
        }
    }
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());

    return Doublets;
}


std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetNeutrinos(const HDoublet &doublet)const
{

    Print(HInformation, "Get Neutrinos");
    const fastjet::PseudoJet lepton = doublet.Singlet1();
    const fastjet::PseudoJet missing_et = doublet.Singlet2();

    const float linear_term = (std::pow(WMass, 2) - lepton.m2()) / 2 + missing_et.px() * lepton.px() + missing_et.py() * lepton.py();

    const float lepton_square = std::pow(lepton.e(), 2) - std::pow(lepton.pz(), 2);
    const float missing_et_square = std::pow(missing_et.px(), 2) + std::pow(missing_et.py(), 2);

    const double radicant = std::pow(lepton.pz(), 2) * (std::pow(linear_term, 2) -  lepton_square * missing_et_square);

    std::vector<HDoublet> doublets;
    if (radicant < 0) {
        Print(HInformation, "Imaginary root", "move missing et towards lepton");
        HDoublet mod_doublet(lepton, missing_et + 0.1 * (lepton - missing_et));
        mod_doublet.SetFlag(true);
        mod_doublet.SetTag(doublet.Tag());
        return GetNeutrinos(mod_doublet);
    }

    if (radicant == 0) {
        Print(HError, "Radicant exactly zero", "implement this case!");
    }

    const float Sqrt = std::sqrt(radicant);

    const float Neutrino1E = (lepton.e() * linear_term - Sqrt) / lepton_square;
    const float Neutrino1Pz = (std::pow(lepton.pz(), 2) * linear_term - lepton.e() * Sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet Neutrino1(missing_et.px(), missing_et.py(), Neutrino1Pz, Neutrino1E);
    Print(HDebug, "Neutrnio 1", Neutrino1);
    HDoublet Doublet1(lepton, Neutrino1);
    Doublet1.SetTag(doublet.Tag());
    Doublet1.SetFlag(doublet.Flag());

    const float Neutrino2E = (lepton.e() * linear_term + Sqrt) / lepton_square;
    const float Neutrino2Pz = (std::pow(lepton.pz(), 2) * linear_term + lepton.e() * Sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet Neutrino2(missing_et.px(), missing_et.py(), Neutrino2Pz, Neutrino2E);
    Print(HDebug, "Neutrino 2", Neutrino2);
    HDoublet Doublet2(lepton, Neutrino2);
    Doublet2.SetTag(doublet.Tag());
    Doublet2.SetFlag(doublet.Flag());

    doublets.emplace_back(Doublet1);
    doublets.emplace_back(Doublet2);

    return doublets;

}


struct SortByError {
    SortByError(const fastjet::PseudoJet &NewNeutrino) {
        this->Neutrino = NewNeutrino;
    }
    bool operator()(const hanalysis::HDoublet &Doublet1, const hanalysis::HDoublet &Doublet2) {
        return ((Doublet1.Singlet2() + Neutrino).m() < (Doublet2.Singlet2() + Neutrino).m());
    }
    fastjet::PseudoJet Neutrino;
};

struct FindError {
    FindError(const fastjet::PseudoJet &NewNeutrino, const float NewError) {
        this->Neutrino = NewNeutrino;
        this->Error = NewError;
    }
    bool operator()(const hanalysis::HDoublet &Doublet) {
        return ((Doublet.Singlet2() + Neutrino).m() == Error);
    }
    fastjet::PseudoJet Neutrino;
    float Error;
};

// std::vector<hanalysis::HDoublet> hanalysis::HWSemiTagger::GetDoublets(const HDoublet &Doublet, const HJets &Neutrinos, const Tag Tag)
// {
//     Print(HInformation, "Get Triple Pair");
//
//     std::vector<HDoublet> Doublets = GetNeutrinos(Doublet);
//     Print(HDebug, "Number Solutions", Doublets.size());
//     if (Doublets.empty()) return Doublets;
//
//     float BestError = LargeNumber;
//     HDoublet BestDoublet;
//     for (const auto Neutrino : Neutrinos) {
//         std::sort(Doublets.begin(), Doublets.end(), SortByError(Neutrino));
//         float Error = (Doublets.front().Singlet2() + Neutrino).m();
//         if (Error < BestError) {
//             BestDoublet = Doublets.front();
//             BestError = Error;
//         }
//     }
//
//     std::vector<HDoublet> FinalDoublets;
//     switch (Tag) {
//     case kSignal:
//         FinalDoublets.emplace_back(BestDoublet);
//         return FinalDoublets;
//     case kBackground:
//         for (const auto Neutrino : Neutrinos) Doublets.erase(std::remove_if(Doublets.begin(), Doublets.end(), FindError(Neutrino, BestError)), Doublets.end());
//         return Doublets;
//     default:
//         Print(HError, "we should never end up here");
//         return Doublets;
//     }
//
//
// }




HJets hanalysis::HWSemiTagger::WSemiDaughters(HEvent &Event)
{
    HJets WKids = Event.GetParticles()->Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(HError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfQuark(WKids);
    if (WKids.size() != 2) Print(HError, "Where is the W 2?", WKids.size());
    else Print(HInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().ParticleId), GetParticleName(WKids.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id), GetParticleName(WKids.at(1).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id));
    return WKids;
}

int hanalysis::HWSemiTagger::WSemiId(const HJets &Jets)
{
    if (Jets.empty()) return WId;
    else return Jets.at(0).user_info<hanalysis::HJetInfo>().Constituents().front().Family().Mother1Id;
}

