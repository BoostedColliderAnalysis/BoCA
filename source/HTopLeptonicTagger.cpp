# include "HTopLeptonicTagger.hh"

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger()
{
  //     DebugLevel = hanalysis::HObject::HDebug;

  Print(HNotification, "Constructor");
  SetTaggerName("TopLeptonic");


}

hanalysis::HTopLeptonicTagger::HTopLeptonicTagger(const HBottomTagger &NewBottomTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader.set_tagger(BottomTagger);
    SetTaggerName("TopLeptonic");
    DefineVariables();
}

hanalysis::HTopLeptonicTagger::~HTopLeptonicTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HTopLeptonicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");

    AddObservable(Branch.BottomPt, "BottomPt");
    AddObservable(Branch.LeptonPt, "LeptonPt");

    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.Bdt, "Bdt");
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
    HJets Jets = Event.GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    Print(HInformation, "Jet Number", Jets.size());

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons)
        for (const auto & Jet : Jets) {
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

std::vector<hanalysis::HDoublet>  hanalysis::HTopLeptonicTagger::GetBdt(const HJets &Jets, HJets &Leptons, const hanalysis::Reader & Reader)
{

    Print(HInformation, "Get Bdt");
    std::vector<HDoublet> Doublets;
    for (const auto & Lepton : Leptons) {
        for (const auto & Jet : Jets) {
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
