# include "HTopSemiTagger.hh"

hanalysis::HTopSemiTagger::HTopSemiTagger()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    DefineVariables();
}

void hanalysis::HTopSemiTagger::SetTagger(const hanalysis::HBottomTagger &NewBottomTagger, const hanalysis::HWSemiTagger &NewWSemiTagger)
{
    Print(HNotification, "SetTagger");
    DefineVariables();
    BottomTagger = NewBottomTagger;
    WSemiTagger = NewWSemiTagger;
}

void hanalysis::HTopSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");
    SetTaggerName("TopSemi");
    TopWindow = (TopMass - WMass) / 2;
    ClearVectors();


    AddObservable(Branch.Mass, "Mass");
    AddObservable(Branch.Rap, "Rap");
    AddObservable(Branch.Phi, "Phi");
    AddObservable(Branch.Pt, "Pt");
    AddObservable(Branch.Ht, "Ht");

    AddObservable(Branch.BottomPt, "BottomPt");
    AddObservable(Branch.WPt, "WPt");

    AddObservable(Branch.DeltaPt, "DeltaPt");
    AddObservable(Branch.DeltaM, "DeltaM");
    AddObservable(Branch.DeltaHt, "DeltaHt");
    AddObservable(Branch.DeltaPhi, "DeltaPhi");
    AddObservable(Branch.DeltaRap, "DeltaRap");
    AddObservable(Branch.DeltaR, "DeltaR");

    AddObservable(Branch.Bdt, "Bdt");
    AddSpectator(Branch.Tag, "Tag");

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
    TopSemiBranch.DeltaM = Triplet.DeltaM();
    TopSemiBranch.DeltaHt = Triplet.DeltaHt();
    TopSemiBranch.DeltaR = Triplet.DeltaR();
    TopSemiBranch.DeltaRap = Triplet.DeltaRap();
    TopSemiBranch.DeltaPhi = Triplet.DeltaPhi();

    TopSemiBranch.Bdt = Triplet.Bdt();
    TopSemiBranch.Tag = Triplet.Tag();

    return TopSemiBranch;
}

std::vector< HTopSemiBranch > hanalysis::HTopSemiTagger::GetBranches(hanalysis::HEvent &Event, const hanalysis::HObject::HTag Tag, float pre_cut)
{
    Print(HInformation, "Get Top Tags");

    int WSemiId = WSemiTagger.GetWSemiId(Event);
    HJets TopParticles = Event.GetParticles()->Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(HError, "Where is the Top?", TopParticles.size());


    HJets Jets = GetJets(Event);
    Print(HInformation, "Jet Number", Jets.size());
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    Print(HInformation, "Number Doublets", Doublets.size());

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // should be enabled again
            if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
            if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
            if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
            Triplet.SetTag(Tag);
            Triplets.push_back(Triplet);
        }
    }

    for (const auto & Jet : Jets) {
      for (const auto & Lepton : Leptons) {
        HDoublet Doublet(Lepton);
        HTriplet Triplet(Doublet, Jet);
        if (Tag == HSignal && std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue; // should be enabled again
        if (Tag == HSignal && Triplet.Jet().pt() <  pre_cut / 2) continue;
        if (Tag == HSignal && Triplet.Jet().delta_R(TopQuark) > DetectorGeometry.JetConeSize) continue;
        if (Tag == HBackground && Triplet.Jet().delta_R(TopQuark) < DetectorGeometry.JetConeSize) continue;
        Triplet.SetTag(Tag);
        Triplets.push_back(Triplet);
      }
    }

    std::vector<HTopSemiBranch> TopSemiBranches;
    int SemiLeptonicTopNumber = 1; // Must be 1 for the analysis!!;
    if (Tag == HSignal &&
            Triplets.size() > SemiLeptonicTopNumber) {
        std::sort(Triplets.begin(), Triplets.end(), SortByMass(TopMass));
        Triplets.erase(Triplets.begin() + SemiLeptonicTopNumber, Triplets.end());
    }
    Print(HInformation, "Number Triplets", Triplets.size());

    for (const auto & Triplet : Triplets) TopSemiBranches.push_back(GetBranch(Triplet));

    return TopSemiBranches;
}



std::vector<hanalysis::HTriplet>  hanalysis::HTopSemiTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader &Reader)
{

    Print(HInformation, "Get Bdt");

    std::vector<HTriplet> Triplets;
    for (const auto & Jet : Jets) {
        for (const auto & Doublet : Doublets) {
            HTriplet Triplet(Doublet, Jet);
            if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
            Branch = GetBranch(Triplet);
            Triplet.SetBdt(Reader.Bdt());
            Triplets.push_back(Triplet);
        }
    }

    for (const auto & Jet : Jets) {
      for (const auto & PreDoublet : Doublets) {
        HDoublet Doublet(PreDoublet.Singlet1());
        HTriplet Triplet(Doublet, Jet);
        if (std::abs(Triplet.Jet().m() - TopMass) > TopWindow) continue;
        Branch = GetBranch(Triplet);
        Triplet.SetBdt(Reader.Bdt());
        Triplets.push_back(Triplet);
      }
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(max_combi(), int(Triplets.size())), Triplets.end());

    return Triplets;
}

