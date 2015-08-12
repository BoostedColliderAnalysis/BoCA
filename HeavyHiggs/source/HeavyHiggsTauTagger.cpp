#include "HeavyHiggsTauTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

HeavyHiggsTauTagger::HeavyHiggsTauTagger()
{
  Info();
    DefineVariables();
}

int HeavyHiggsTauTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    Jets jets = tau_reader_.Multiplets(event);
    Info(jets.size());
    fastjet::PseudoJet MissingEt = event.Hadrons().MissingEt();
    Jets TauParticles = event.Partons().GenParticles();
    TauParticles = CopyIfParticle(TauParticles, Id::tau);
//     TauParticles.erase(std::remove_if(TauParticles.begin(), TauParticles.end(), WrongAbsId(Id::tau)), TauParticles.end());
    Check(TauParticles.size() == 1, TauParticles.size());
    Jets HiggsParticles = event.Partons().GenParticles();
    HiggsParticles = CopyIfParticle(HiggsParticles, Id::charged_higgs);
//     HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(Id::charged_higgs)), HiggsParticles.end());
    Check(HiggsParticles.size() == 1, HiggsParticles.size());
    for (auto const& Particle : TauParticles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4)
            static_cast<JetInfo&>(*jets.front().user_info_shared_ptr().get()).SetTag(Tag::signal);
    }
    Jets NewCleanJets;
    for (auto const& jet : jets) {
        if (!jet.has_user_info<JetInfo>())
            continue;
        if (jet.user_info<JetInfo>().Tag() != tag)
            continue;
        NewCleanJets.emplace_back(jet);
    }
    std::vector<Doublet> doublets;
    for (auto const& Jet : NewCleanJets) {
        Doublet Predoublet(Jet, MissingEt);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
//         std::sort(Postdoublets.begin(), Postdoublets.end(), MinDeltaR(HiggsParticles.front()));
//         if (Tag == Tag::signal && Postdoublets.size() > 1) Postdoublets.erase(Postdoublets.begin() + 1, Postdoublets.end());
//         if (Tag == HBackground && Postdoublets.size() > 0) Postdoublets.erase(Postdoublets.begin());
//         for (auto & Postdoublet : Postdoublets) {
        Predoublet.SetTag(tag);
        doublets.emplace_back(Predoublet);
//         }
    }
    Info("Number doublets", doublets.size());
    return SaveEntries(doublets);
}

std::vector<Doublet>  HeavyHiggsTauTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    Jets jets = tau_reader_.Multiplets(event);
    Info(jets.size());
    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (auto const& jet : jets)  {
        Doublet pre_doublet(jet, missing_et);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
//         for (auto & Postdoublet : Postdoublets) {
//             if (Postdoublet.Jet().m() < 10) continue;
        pre_doublet.SetBdt(Bdt(pre_doublet, reader));
        doublets.emplace_back(pre_doublet);
//         }
    }
    return ReduceResult(doublets);
}

}

}
