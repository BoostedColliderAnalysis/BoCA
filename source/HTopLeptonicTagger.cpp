# include "HTopLeptonicTagger.hh"

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
  set_tagger_name("TopLeptonic");


}

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger(const BottomTagger &NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    bottom_tagger_ = NewBottomTagger;
    BottomReader.set_tagger(bottom_tagger_);
    set_tagger_name("TopLeptonic");
    DefineVariables();
}

hanalysis::HTopLeptonicTagger::~HTopLeptonicTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HTopLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddVariable(Branch.Mass, "Mass");
    AddVariable(Branch.Pt, "Pt");
    AddVariable(Branch.Rap, "Rap");
    AddVariable(Branch.Phi, "Phi");

    AddVariable(Branch.BottomPt, "BottomPt");
    AddVariable(Branch.LeptonPt, "LeptonPt");

    AddVariable(Branch.DeltaPhi, "DeltaPhi");
    AddVariable(Branch.DeltaRap, "DeltaRap");
    AddVariable(Branch.DeltaR, "DeltaR");

    AddVariable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

    Print(HNotification, "Variables defined");

}

HTopLeptonicBranch hanalysis::HTopLeptonicTagger::GetBranch(const hanalysis::HDoublet &Doublet)
{
    Print(HInformation, "Fill Top Tagger", Doublet.Bdt());

    HTopLeptonicBranch TopLeptonicBranch;
    TopLeptonicBranch.Mass = Doublet.Jet().m();
    TopLeptonicBranch.Pt = Doublet.Jet().pt();
    TopLeptonicBranch.Rap = Doublet.Jet().rap();
    TopLeptonicBranch.Phi = Doublet.Jet().phi();

    TopLeptonicBranch.BottomPt = Doublet.Singlet1().pt();
    TopLeptonicBranch.LeptonPt = Doublet.Singlet2().pt();

    TopLeptonicBranch.DeltaR = Doublet.DeltaR();
    TopLeptonicBranch.DeltaRap = Doublet.DeltaRap();
    TopLeptonicBranch.DeltaPhi = Doublet.DeltaPhi();

    TopLeptonicBranch.Bdt = Doublet.Bdt();
    TopLeptonicBranch.Tag = Doublet.Tag();
    return TopLeptonicBranch;

}

std::vector<HTopLeptonicBranch> hanalysis::HTopLeptonicTagger::GetBranches(HEvent &Event, const HObject::Tag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag.HeavyParticles = {TopId};
    Jets jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader); // TODO reenable this
    Print(HInformation, "Jet Number", jets.size());

    Jets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons)
        for (const auto & Jet : jets) {
            HDoublet Doublet(Jet, Lepton);
            Doublet.SetTag(GetTag(Doublet));
            if (Doublet.Tag() != Tag) continue;
            if (Tag == kSignal && Doublet.Jet().m() > TopMass) continue;
            Doublets.emplace_back(Doublet);
        }


    Print(HInformation, "Number JetPairs", Doublets.size());

    if (Tag == kSignal && Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end(), SortByMass(TopMass));
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    std::vector<HTopLeptonicBranch> TopLeptonicBranches;
    for (const auto & Doublet : Doublets) TopLeptonicBranches.emplace_back(GetBranch(Doublet));

    return TopLeptonicBranches;

}

hanalysis::HObject::Tag hanalysis::HTopLeptonicTagger::GetTag(const HDoublet &Doublet)
{
    Print(HInformation, "Get Triple Tag", GetParticleName(Doublet.Singlet1().user_index()), GetParticleName(Doublet.Singlet2().user_index()));

    HJetInfo BJetInfo = Doublet.Singlet1().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    HJetInfo LJetInfo = Doublet.Singlet2().user_info<HJetInfo>();
    LJetInfo.ExtractFraction(WId);

    if (std::abs(LJetInfo.MaximalId()) != WId) return kBackground;
    if (std::abs(BJetInfo.MaximalId()) != BottomId) return kBackground;
    if (sgn(BJetInfo.MaximalId()) != sgn(LJetInfo.MaximalId())) return kBackground;

    return kSignal;
}

std::vector<hanalysis::HDoublet>  hanalysis::HTopLeptonicTagger::GetBdt(const Jets &jets, Jets &Leptons, const hanalysis::Reader & Reader)
{

    Print(HInformation, "Get Bdt");
    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        for (const auto & Jet : jets) {
            HDoublet Doublet(Jet, Lepton);
            Branch = GetBranch(Doublet);
            Doublet.SetBdt(Reader.Bdt());
            Doublets.emplace_back(Doublet);
        }
    }

    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + std::min(max_combi(), int(Doublets.size())), Doublets.end());

    return Doublets;

}
