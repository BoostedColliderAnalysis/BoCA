# include "HeavyHiggsTauTagger.hh"

namespace analysis
{

namespace heavyhiggs
{

HeavyHiggsTauTagger::HeavyHiggsTauTagger()
{
//     DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsTau");
    tau_reader_.SetTagger(tau_tagger_);
    DefineVariables();
}

int HeavyHiggsTauTagger::Train(Event &event, const Object::Tag tag)
{

    Print(kInformation, "Top Tags");

    Jets jets = tau_reader_.Multiplets<TauTagger>(event);
    Print(kInformation, "Number Jet", jets.size());

    const fastjet::PseudoJet MissingEt = event.Hadrons().MissingEt();

    Jets TauParticles = event.Partons().GenParticles();
    TauParticles = RemoveIfWrongAbsParticle(TauParticles, TauId);
//     TauParticles.erase(std::remove_if(TauParticles.begin(), TauParticles.end(), WrongAbsId(TauId)), TauParticles.end());
    if (TauParticles.size() != 1) Print(kError, "Where is the Tau?", TauParticles.size());

    Jets HiggsParticles = event.Partons().GenParticles();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
//     HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?", HiggsParticles.size());

    for (const auto & Particle : TauParticles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }
    Jets NewCleanJets;
    for (const auto & jet : jets) {
        if (!jet.has_user_info<JetInfo>()) continue;
        if (jet.user_info<JetInfo>().Tag() != tag) continue;
        NewCleanJets.emplace_back(jet);
    }

    std::vector<Doublet> doublets;
    for (const auto & Jet : NewCleanJets) {
        Doublet Predoublet(Jet, MissingEt);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);

//         std::sort(Postdoublets.begin(), Postdoublets.end(), MinDeltaR(HiggsParticles.front()));
//         if (Tag == kSignal && Postdoublets.size() > 1) Postdoublets.erase(Postdoublets.begin() + 1, Postdoublets.end());
//         if (Tag == HBackground && Postdoublets.size() > 0) Postdoublets.erase(Postdoublets.begin());
//         for (auto & Postdoublet : Postdoublets) {
        Predoublet.SetTag(tag);
        doublets.emplace_back(Predoublet);
//         }
    }
    Print(kInformation, "Number doublets", doublets.size());
    return SaveEntries(doublets);
}

std::vector<Doublet>  HeavyHiggsTauTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Multiplets");
    Jets jets = tau_reader_.Multiplets<TauTagger>(event);
    Print(kInformation, "Number Jet", jets.size());
    const fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (const auto & jet : jets)  {
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
