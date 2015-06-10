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
}

int analysis::WSemiTagger::Train(analysis::Event &event, const analysis::Object::Tag tag)
{
    Print(kInformation, "Train");
    Jets Particles = event.Partons().GenParticles();
    int w_semi_id = WSemiId(event);
    Jets w_bosons = copy_if_particle(Particles, w_semi_id);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (leptons.size() > w_bosons.size()) leptons.erase(leptons.begin() + w_bosons.size(), leptons.end());
    const fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        Doublet pre_doublet(lepton, missing_et);
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto & doublet : post_doublets) {
            if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) continue;
            bool in_cone = false;
            for(const auto w_boson : w_bosons) if (doublet.Jet().delta_R(w_boson) < detector_geometry().JetConeSize) in_cone = true;
            switch(tag) {
            case kSignal :
              if (!in_cone) continue;
              break;
            case (kBackground) :
                if (in_cone) continue;
                break;
            }
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    return SaveEntries<WSemiBranch>(doublets);
}

std::vector<analysis::Doublet>  analysis::WSemiTagger::Multiplets(analysis::Event &event, const TMVA::Reader &reader)
{
  Print(kInformation, "Triple Bdt");
  Jets Particles = event.Partons().GenParticles();
  int w_semi_id = WSemiId(event);
  Jets w_bosons = copy_if_particle(Particles, w_semi_id);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (leptons.size() > w_bosons.size()) leptons.erase(leptons.begin() + w_bosons.size(), leptons.end());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        Doublet pre_doublet(lepton, event.Hadrons().MissingEt());
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto & doublet : post_doublets) {
            if (std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) continue;
            branch_ = branch<WSemiBranch>(doublet);
            doublet.SetBdt(Bdt(reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

std::vector<analysis::Doublet> analysis::WSemiTagger::ReconstructNeutrino(const Doublet &doublet)const
{

    Print(kInformation, "Neutrinos");
    const fastjet::PseudoJet lepton = doublet.SingletJet1();
    const fastjet::PseudoJet missing_et = doublet.SingletJet2();

    const float linear_term = (std::pow(Mass(WId), 2) - lepton.m2()) / 2 + missing_et.px() * lepton.px() + missing_et.py() * lepton.py();

    const float lepton_square = std::pow(lepton.e(), 2) - std::pow(lepton.pz(), 2);
    const float missing_et_square = std::pow(missing_et.px(), 2) + std::pow(missing_et.py(), 2);

    const double radicant = std::pow(lepton.pz(), 2) * (std::pow(linear_term, 2) -  lepton_square * missing_et_square);

    if (radicant < 0) {
        Print(kInformation, "Imaginary root", "move missing et towards lepton");
        Doublet mod_doublet(lepton, missing_et + 0.1 * (lepton - missing_et));
        mod_doublet.SetFlag(true);
        mod_doublet.SetTag(doublet.Tag());
        return ReconstructNeutrino(mod_doublet);
    }

    if (radicant == 0) Print(kError, "Radicant exactly zero", "implement this case!");

    const float sqrt = std::sqrt(radicant);

    const float neutrino_1_e = (lepton.e() * linear_term - sqrt) / lepton_square;
    const float neutrino_1_pz = (std::pow(lepton.pz(), 2) * linear_term - lepton.e() * sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet neutrino_1(missing_et.px(), missing_et.py(), neutrino_1_pz, neutrino_1_e);
    Print(kDebug, "Neutrnio 1", neutrino_1);
    Doublet doublet1(lepton, neutrino_1);
    doublet1.SetTag(doublet.Tag());
    doublet1.SetFlag(doublet.Flag());

    const float neutrino_2_e = (lepton.e() * linear_term + sqrt) / lepton_square;
    const float neutrino_2_pz = (std::pow(lepton.pz(), 2) * linear_term + lepton.e() * sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet neutrino_2(missing_et.px(), missing_et.py(), neutrino_2_pz, neutrino_2_e);
    Print(kDebug, "Neutrino 2", neutrino_2);
    Doublet doublet2(lepton, neutrino_2);
    doublet2.SetTag(doublet.Tag());
    doublet2.SetFlag(doublet.Flag());

    std::vector<Doublet> doublets;
    doublets.emplace_back(doublet1);
    doublets.emplace_back(doublet2);

    return doublets;

}

analysis::Jets analysis::WSemiTagger::WSemiDaughters(Event &event)
{
    Jets w_daughters = event.Partons().GenParticles();
    w_daughters = RemoveIfWrongAbsMother(w_daughters, WId);
    if (w_daughters.size() != 4) Print(kError, "Where is the W 1?", w_daughters.size());

    w_daughters = RemoveIfQuark(w_daughters);
    if (w_daughters.size() != 2) Print(kError, "Where is the W 2?", w_daughters.size());
    else Print(kInformation, "W Daughters", Name(w_daughters.at(0).user_info<analysis::JetInfo>().constituents().front().family().particle().Id), Name(w_daughters.at(1).user_info<analysis::JetInfo>().constituents().front().family().particle().Id), Name(w_daughters.at(0).user_info<analysis::JetInfo>().constituents().front().family().mother_1().Id), Name(w_daughters.at(1).user_info<analysis::JetInfo>().constituents().front().family().mother_1().Id));
    return w_daughters;
}

int analysis::WSemiTagger::WSemiId(const Jets &jets)
{
    if (jets.empty()) return WId;
    else return jets.front().user_info<JetInfo>().constituents().front().family().mother_1().Id;
}

