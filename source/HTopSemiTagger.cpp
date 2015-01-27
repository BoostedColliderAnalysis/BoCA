# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    SetTaggerName("TopSemi");
    DefineVariables();
}

hanalysis::HTopSemiTagger::~HTopSemiTagger()
{
    Print(HNotification, "Destructor");
}

void hanalysis::HTopSemiTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger)
{
    Print(HNotification, "SetTagger");

    SetTaggerName("TopSemi");
    DefineVariables();

    BottomTagger = NewBottomTagger;
    BottomTagger.SetTagger();
    BottomReader.SetMva(BottomTagger);

    WSemiTagger = NewWSemiTagger;
    WSemiTagger.SetTagger();
    WSemiReader.SetMva(WSemiTagger);

    TopWindow = 50;

}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.clear();
    Spectators.clear();

    Observables.push_back(NewObservable(&Branch.Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch.Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch.Phi, "Phi"));
    Observables.push_back(NewObservable(&Branch.Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch.Ht, "Ht"));

    Observables.push_back(NewObservable(&Branch.BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch.WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch.DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch.DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch.DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch.DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch.Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch.Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

HTopSemiBranch hanalysis::HTopSemiTagger::GetBranch(const hanalysis::HTriplet &Triplet) const
{
    Print(HInformation, "Fill Top Tagger", Triplet.Bdt());

    HTopSemiBranch TopSemiBranch;
    TopSemiBranch.Mass = Triplet.Jet().m();
    TopSemiBranch.Rap = Triplet.Jet().rap();
    TopSemiBranch.Phi = Triplet.Jet().phi();
    TopSemiBranch.Pt = Triplet.Jet().pt();
    TopSemiBranch.Ht = Triplet.Ht();

    TopSemiBranch.BottomPt = Triplet.Singlet().pt();
    TopSemiBranch.WPt = Triplet.DoubletJet().pt();

    TopSemiBranch.DeltaPt = Triplet.DeltaPt();
    TopSemiBranch.DeltaR = Triplet.DeltaR();
    TopSemiBranch.DeltaRap = Triplet.DeltaRap();
    TopSemiBranch.DeltaPhi = Triplet.DeltaPhi();

    TopSemiBranch.Bdt = Triplet.Bdt();
    TopSemiBranch.Tag = Triplet.Tag();

    return TopSemiBranch;
}

std::vector< HTopSemiBranch > hanalysis::HTopSemiTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag State)
{

    Print(HInformation, "Get Top Tags");

    JetTag.HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
        std::vector<HTriplet> PreTriplets;
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.Tag() != State) continue;
            if (State == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
//             if (Tag == HSignal && Triplet.DeltaR() > 1.5) continue; // FIXME assumption of boost larger 400
            PreTriplets.push_back(Triplet);
        }
        if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByMass<HTriplet>(TopMass));
        if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
    }

    if (State == HSignal && Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end(), SortByMass<HTriplet>(TopMass));
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    Print(HInformation, "Number Triplets", Triplets.size());

    std::vector<HTopSemiBranch> TopSemiBranches;
    for (const auto & Triplet : Triplets) TopSemiBranches.push_back(GetBranch(Triplet));

    return TopSemiBranches;
}

hanalysis::HObject::HTag hanalysis::HTopSemiTagger::GetTag(const hanalysis::HTriplet &Triplet) const
{
    Print(HInformation, "Get Triple Tag");

    HJetInfo BJetInfo = Triplet.Singlet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    BJetInfo.PrintAllInfos(HInformation);
    HJetInfo W1JetInfo = Triplet.Doublet().Singlet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(WId);
    W1JetInfo.PrintAllInfos(HInformation);

    if (std::abs(W1JetInfo.MaximalId()) != WId) return HBackground;
    if (std::abs(BJetInfo.MaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.MaximalId()) != sgn(W1JetInfo.MaximalId())) return HBackground;
    return HSignal;
}


std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader &Reader)
{

    Print(HInformation, "Get Bdt");

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
        std::vector<HTriplet> PreTriplets;
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            if (std::abs(Triplet.DeltaRap()) > 100) continue;
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(Reader.Bdt());
            PreTriplets.push_back(Triplet);
        }
        if (PreTriplets.size() > 1) std::sort(PreTriplets.begin(), PreTriplets.end(), SortByMass<HTriplet>(TopMass));
        if (PreTriplets.size() > 0) Triplets.push_back(PreTriplets.front());
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());

    return Triplets;
}

