# include "GlobalObservables.hh"

namespace analysis
{

GlobalObservables::GlobalObservables()
{
//     debug_level_ = Severity::debug;
    Print(Severity::information, "Constructor");
}

void GlobalObservables::SetEvent(Event &event, const analysis::Jets &jets)
{
    leptons_ = event.Leptons().leptons();
    scalar_ht_ = event.Hadrons().ScalarHt();
    missing_et_ = event.Hadrons().MissingEt().pt();
    jets_ = jets;
}

int GlobalObservables::LeptonNumber() const
{
    Print(Severity::information, "Lepton Number");
    return leptons_.size();
}

int GlobalObservables::JetNumber() const
{
    Print(Severity::information, "Jet Number");
    return Jets().size();
}

int GlobalObservables::BottomNumber() const
{
    Print(Severity::information, "Bottom Number");
    analysis::Jets bottoms;
    for (const auto jet : Jets()) if (jet.user_info<JetInfo>().Bdt() > 1) bottoms.emplace_back(jet);
    return bottoms.size();
}

float GlobalObservables::BottomBdt() const
{
    Print(Severity::information, "Bottom Bdt");
    if (Jets().empty()) return 0;
    return std::accumulate(jets_.begin(), jets_.end(), 0., [](float bdt, const fastjet::PseudoJet & jet) {
        return bdt + jet.user_info<JetInfo>().Bdt();
    }) / JetNumber();
}

float GlobalObservables::BottomBdt(const int number) const
{
    Print(Severity::information, "Bottom Bdt");
    if (number > JetNumber()) return 0;
    return Jets().at(number - 1).user_info<JetInfo>().Bdt();
}

float GlobalObservables::BottomBdt(const int number_1, const int number_2) const
{
    Print(Severity::information, "Bottom Bdt");
    if (number_1 > JetNumber()) return 0;
    if (number_2 > JetNumber()) return 0;
    return (Jets().at(number_1 - 1).user_info<JetInfo>().Bdt() + Jets().at(number_2 - 1).user_info<JetInfo>().Bdt()) / 2;
}

float GlobalObservables::ScalarHt() const
{
    Print(Severity::information, "Scalar Ht");
    return scalar_ht_;
}

float GlobalObservables::LeptonHt() const
{
    Print(Severity::information, "Lepton Ht");
    if (leptons_.empty()) return 0;
    return std::accumulate(leptons_.begin(), leptons_.end(), 0., [](float ht, const fastjet::PseudoJet & lepton) {
        return ht + lepton.pt();
    });
}

float GlobalObservables::JetHt() const
{
    Print(Severity::information, "Jet Ht");
    if (Jets().empty()) return 0;
    return std::accumulate(jets_.begin(), jets_.end(), 0., [](float ht, const fastjet::PseudoJet & jet) {
        return ht + jet.pt();
    });
}

float GlobalObservables::MissingEt() const
{
    Print(Severity::information, "Mising et");
    return missing_et_;
}

Singlet GlobalObservables::Singlet() const
{
    Print(Severity::information, "Singlet");
    fastjet::PseudoJet jet(fastjet::join(Jets()));
    jet.set_user_info(new JetInfo(BottomBdt()));
    return analysis::Singlet(jet);
}

Jets GlobalObservables::Jets() const
{
    Print(Severity::information, "Jets");
    return jets_;
}

void GlobalObservables::SetJets(const analysis::Jets jets)
{
    Print(Severity::information, "Set Jets");
    jets_ = jets;
}

}
