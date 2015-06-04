# include "HeavyHiggsTauTagger.hh"

analysis::HeavyHiggsTauTagger::HeavyHiggsTauTagger()
{
//     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("HeavyHiggsTau");
    tau_reader_.set_tagger(tau_tagger_);
    DefineVariables();
}

void analysis::HeavyHiggsTauTagger::DefineVariables()
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

int analysis::HeavyHiggsTauTagger::Train(analysis::Event &event, const analysis::Object::Tag tag)
{

    Print(kInformation, "Top Tags");

    Jets jets = tau_reader_.Multiplets<TauTagger>(event);
    Print(kInformation, "Number Jet", jets.size());

    const fastjet::PseudoJet MissingEt = event.hadrons().MissingEt();

    Jets TauParticles = event.partons().GenParticles();
    TauParticles = RemoveIfWrongAbsParticle(TauParticles, TauId);
//     TauParticles.erase(std::remove_if(TauParticles.begin(), TauParticles.end(), WrongAbsId(TauId)), TauParticles.end());
    if (TauParticles.size() != 1) Print(kError, "Where is the Tau?", TauParticles.size());

    Jets HiggsParticles = event.partons().GenParticles();
    HiggsParticles = RemoveIfWrongAbsParticle(HiggsParticles, ChargedHiggsId);
//     HiggsParticles.erase(std::remove_if(HiggsParticles.begin(), HiggsParticles.end(), WrongAbsId(ChargedHiggsId)), HiggsParticles.end());
    if (HiggsParticles.size() != 1) Print(kError, "Where is the Higgs?", HiggsParticles.size());

    for (const auto & Particle : TauParticles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }
    Jets NewCleanJets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) continue;
        if (Jet.user_info<JetInfo>().Tag() != tag) continue;
        NewCleanJets.emplace_back(Jet);
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
    return SaveEntries<HeavyHiggsTauBranch>(doublets);
}

std::vector<analysis::Doublet>  analysis::HeavyHiggsTauTagger::Multiplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Multiplets");
    Jets jets = tau_reader_.Multiplets<TauTagger>(event);
    Print(kInformation, "Number Jet", jets.size());
    const fastjet::PseudoJet missing_et = event.hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (const auto & jet : jets)  {
        Doublet Predoublet(jet, missing_et);
//         std::vector<Doublet> Postdoublets = GetNeutrinos(Predoublet);
//         for (auto & Postdoublet : Postdoublets) {
//             if (Postdoublet.Jet().m() < 10) continue;
        branch_ = branch<HeavyHiggsTauBranch>(Predoublet);
        Predoublet.SetBdt(Bdt(reader));
        doublets.emplace_back(Predoublet);
//         }
    }

    return ReduceResult(doublets);
}
