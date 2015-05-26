# include "WSemiTagger.hh"
# include "Reader.hh"

analysis::WSemiTagger::WSemiTagger()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WSemi");
    w_mass_window_ = 20;
    DefineVariables();
}


void analysis::WSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");
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
    Print(kNotification, "Variables defined");
}

int analysis::WSemiTagger::Train(analysis::Event &event, const analysis::Object::Tag tag)
{
    Print(kInformation, "Get Top Tags");

    Jets leptons = fastjet::sorted_by_pt(event.leptons().GetLeptonJets());
    if (leptons.size() > 1) leptons.erase(leptons.begin() + 1, leptons.end());

    const fastjet::PseudoJet missing_et = event.hadrons().GetMissingEt();

    Jets Particles = event.partons().Generator();
    int w_semi_id = WSemiId(event);
    fastjet::PseudoJet WBoson;
    Particles = RemoveIfWrongParticle(Particles, w_semi_id);
    if (Particles.size() == 1) {
        WBoson = Particles.front();
    } else Print(kError, "Where is the W?", Particles.size());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        Doublet Predoublet(lepton, missing_et);
        std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
        std::sort(Postdoublets.begin(), Postdoublets.end(), MinDeltaRTo(WBoson));
        for (auto & Postdoublet : Postdoublets) {
            if (tag == kSignal && std::abs(Postdoublet.Jet().m() - WMass) > w_mass_window_) continue;
            if (tag == kSignal && Postdoublet.Jet().delta_R(WBoson) > detector_geometry().JetConeSize) continue;
            if (tag == kBackground && Postdoublet.Jet().delta_R(WBoson) > detector_geometry().JetConeSize) continue;
            Postdoublet.SetTag(tag);
            doublets.emplace_back(Postdoublet);
        }
    }
 return SaveEntries<WSemiBranch>(doublets);
}

std::vector<analysis::Doublet>  analysis::WSemiTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get Triple Bdt");
    Jets leptons = fastjet::sorted_by_pt(event.leptons().GetLeptonJets());
    if (leptons.size() > 1) leptons.erase(leptons.begin() + 1, leptons.end());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        Doublet Predoublet(lepton, event.hadrons().GetMissingEt());
        std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
        for (auto & Postdoublet : Postdoublets) {
            if (std::abs(Postdoublet.Jet().m() - WMass) > w_mass_window_) continue;
            branch_ = branch<WSemiBranch>(Postdoublet);
            Postdoublet.SetBdt(Bdt(reader));
            doublets.emplace_back(Postdoublet);
        }
    }
    std::sort(doublets.begin(), doublets.end());
    doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());

    return doublets;
}

std::vector<analysis::Doublet> analysis::WSemiTagger::GetNeutrinos(const Doublet &doublet)const
{

    Print(kInformation, "Get Neutrinos");
    const fastjet::PseudoJet lepton = doublet.Singlet1();
    const fastjet::PseudoJet missing_et = doublet.Singlet2();

    const float linear_term = (std::pow(WMass, 2) - lepton.m2()) / 2 + missing_et.px() * lepton.px() + missing_et.py() * lepton.py();

    const float lepton_square = std::pow(lepton.e(), 2) - std::pow(lepton.pz(), 2);
    const float missing_et_square = std::pow(missing_et.px(), 2) + std::pow(missing_et.py(), 2);

    const double radicant = std::pow(lepton.pz(), 2) * (std::pow(linear_term, 2) -  lepton_square * missing_et_square);

    std::vector<Doublet> doublets;
    if (radicant < 0) {
        Print(kInformation, "Imaginary root", "move missing et towards lepton");
        Doublet mod_doublet(lepton, missing_et + 0.1 * (lepton - missing_et));
        mod_doublet.SetFlag(true);
        mod_doublet.SetTag(doublet.Tag());
        return GetNeutrinos(mod_doublet);
    }

    if (radicant == 0) {
        Print(kError, "Radicant exactly zero", "implement this case!");
    }

    const float Sqrt = std::sqrt(radicant);

    const float Neutrino1E = (lepton.e() * linear_term - Sqrt) / lepton_square;
    const float Neutrino1Pz = (std::pow(lepton.pz(), 2) * linear_term - lepton.e() * Sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet Neutrino1(missing_et.px(), missing_et.py(), Neutrino1Pz, Neutrino1E);
    Print(kDebug, "Neutrnio 1", Neutrino1);
    Doublet doublet1(lepton, Neutrino1);
    doublet1.SetTag(doublet.Tag());
    doublet1.SetFlag(doublet.Flag());

    const float Neutrino2E = (lepton.e() * linear_term + Sqrt) / lepton_square;
    const float Neutrino2Pz = (std::pow(lepton.pz(), 2) * linear_term + lepton.e() * Sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet Neutrino2(missing_et.px(), missing_et.py(), Neutrino2Pz, Neutrino2E);
    Print(kDebug, "Neutrino 2", Neutrino2);
    Doublet doublet2(lepton, Neutrino2);
    doublet2.SetTag(doublet.Tag());
    doublet2.SetFlag(doublet.Flag());

    doublets.emplace_back(doublet1);
    doublets.emplace_back(doublet2);

    return doublets;

}


struct SortByError {
    SortByError(const fastjet::PseudoJet &neutrino) {
        neutrino_ = neutrino;
    }
    bool operator()(const analysis::Doublet &doublet1, const analysis::Doublet &doublet2) {
        return ((doublet1.Singlet2() + neutrino_).m() < (doublet2.Singlet2() + neutrino_).m());
    }
    fastjet::PseudoJet neutrino_;
};

struct FindError {
    FindError(const fastjet::PseudoJet &NewNeutrino, const float NewError) {
        this->Neutrino = NewNeutrino;
        this->Error = NewError;
    }
    bool operator()(const analysis::Doublet &doublet) {
        return ((doublet.Singlet2() + Neutrino).m() == Error);
    }
    fastjet::PseudoJet Neutrino;
    float Error;
};

Jets analysis::WSemiTagger::WSemiDaughters(Event &event)
{
    Jets WKids = event.partons().Generator();
    WKids = RemoveIfWrongAbsMother(WKids, WId);
    if (WKids.size() != 4) Print(kError, "Where is the W 1?", WKids.size());

    WKids = RemoveIfQuark(WKids);
    if (WKids.size() != 2) Print(kError, "Where is the W 2?", WKids.size());
    else Print(kInformation, "W Daughters", GetParticleName(WKids.at(0).user_info<analysis::JetInfo>().constituents().front().family().particle().Id), GetParticleName(WKids.at(1).user_info<analysis::JetInfo>().constituents().front().family().particle().Id), GetParticleName(WKids.at(0).user_info<analysis::JetInfo>().constituents().front().family().mother_1().Id), GetParticleName(WKids.at(1).user_info<analysis::JetInfo>().constituents().front().family().mother_1().Id));
    return WKids;
}

int analysis::WSemiTagger::WSemiId(const Jets &jets)
{
    if (jets.empty()) return WId;
    else return jets.at(0).user_info<analysis::JetInfo>().constituents().front().family().mother_1().Id;
}

