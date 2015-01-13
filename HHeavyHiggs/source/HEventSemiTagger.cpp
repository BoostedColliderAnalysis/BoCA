# include "HEventSemiTagger.hh"

hheavyhiggs::HEventSemiTagger::HEventSemiTagger(
    hanalysis::HBottomTagger *const NewBottomTagger,
    hanalysis::HJetPairTagger *const NewJetPairTagger,
    hanalysis::HWSemiTagger *const NewWSemiTagger,
    hanalysis::HWTagger *const NewWTagger,
    hanalysis::HTopSemiTagger *const NewTopSemiTagger,
    hanalysis::HTopHadronicTagger *const NewTopHadronicTagger, hanalysis::HHeavyHiggsSemiTagger *const NewHeavyHiggsMixedTagger)
{
//   DebugLevel = HDebug;

    Print(HNotification , "Constructor");

    BottomTagger = NewBottomTagger;
    BottomReader = new hanalysis::HReader(BottomTagger);
    WSemiTagger = NewWSemiTagger;
    WSemiReader = new hanalysis::HReader(WSemiTagger);
    WTagger = NewWTagger;
    WReader = new hanalysis::HReader(WTagger);
    TopHadronicTagger = NewTopHadronicTagger;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
    TopSemiTagger = NewTopSemiTagger;
    TopSemiReader = new hanalysis::HReader(TopSemiTagger);
    HeavyHiggsSemiTagger = NewHeavyHiggsMixedTagger;
    HeavyHiggsSemiReader = new hanalysis::HReader(HeavyHiggsSemiTagger);
    JetPairTagger = NewJetPairTagger;
    JetPairReader = new hanalysis::HReader(JetPairTagger);

    SetTaggerName("EventSemi");

    Branch = new hheavyhiggs::HEventSemiBranch();
    JetTag = new hanalysis::HJetTag();

    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::HEventSemiTagger()
{
    //   DebugLevel = HDebug;

    Print(HNotification , "Constructor");

    SetTaggerName("EventSemi");
    Branch = new hheavyhiggs::HEventSemiBranch();

    DefineVariables();

}

hheavyhiggs::HEventSemiTagger::~HEventSemiTagger()
{

    Print(HNotification , "Constructor");

    delete Branch;
    delete JetTag;
    delete WSemiReader;
    delete WReader;
    delete BottomReader;
    delete TopHadronicReader;
    delete TopSemiReader;
    delete HeavyHiggsSemiReader;
    delete JetPairReader;

}

void hheavyhiggs::HEventSemiTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Spectators.push_back(NewObservable(&Branch->LeptonNumber, "LeptonNumber"));
    Observables.push_back(NewObservable(&Branch->JetNumber, "JetNumber"));
    Observables.push_back(NewObservable(&Branch->BottomNumber, "BottomNumber"));
    Observables.push_back(NewObservable(&Branch->ScalarHt, "ScalarHt"));

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->DeltaPt, "DeltaPt"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->HiggsMass, "HiggsMass"));
    Observables.push_back(NewObservable(&Branch->PairRap, "PairRap"));

    Observables.push_back(NewObservable(&Branch->RestM, "RestM"));
    Observables.push_back(NewObservable(&Branch->RestPt, "RestPt"));
    Observables.push_back(NewObservable(&Branch->RestHt, "RestHt"));
    Observables.push_back(NewObservable(&Branch->RestPhi, "RestPhi"));
    Observables.push_back(NewObservable(&Branch->RestRap, "RestRap"));
    Observables.push_back(NewObservable(&Branch->RestBTag, "RestBTag"));
    Observables.push_back(NewObservable(&Branch->RestBBdt, "RestBBdt"));

    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));


    Print(HNotification, "Variables defined");

}

void hheavyhiggs::HEventSemiTagger::FillBranch(hheavyhiggs::HEventSemiBranch *EventSemiBranch, const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger", Octet.GetBdt());

    EventSemiBranch->LeptonNumber = Octet.GetLeptonNumber();
    EventSemiBranch->JetNumber = Octet.GetJetNumber();
    EventSemiBranch->BottomNumber = Octet.GetBottomNumber();
    EventSemiBranch->ScalarHt = Octet.GetScalarHt();

    EventSemiBranch->Mass = Octet.GetOctetJet().m();
    EventSemiBranch->Rap = Octet.GetOctetJet().rap();
    EventSemiBranch->Phi = Octet.GetOctetJet().phi();
    EventSemiBranch->Pt = Octet.GetOctetJet().pt();

    EventSemiBranch->DeltaPt = Octet.GetDeltaPt();
    EventSemiBranch->DeltaRap = Octet.GetDeltaRap();
    EventSemiBranch->DeltaPhi = Octet.GetDeltaPhi();
    EventSemiBranch->DeltaR = Octet.GetDeltaR();

    EventSemiBranch->Bdt = Octet.GetBdt();
    EventSemiBranch->Tag = Octet.GetTag();

    EventSemiBranch->HiggsMass = Octet.GetSextet().GetSextetJet().m();
    EventSemiBranch->PairRap = Octet.GetDoublet().GetDeltaRap();

    EventSemiBranch->RestM = Octet.GetEventStruct().RestM;
    EventSemiBranch->RestPt = Octet.GetEventStruct().RestPt;
    EventSemiBranch->RestHt = Octet.GetEventStruct().RestHt;
    EventSemiBranch->RestRap = Octet.GetEventStruct().RestRap;
    EventSemiBranch->RestPhi = Octet.GetEventStruct().RestPhi;
    EventSemiBranch->RestBTag = Octet.GetEventStruct().RestBTag;
    EventSemiBranch->RestBBdt = Octet.GetEventStruct().RestBBdt;

}

void hheavyhiggs::HEventSemiTagger::FillBranch(const HOctet &Octet)
{
    Print(HInformation, "FillPairTagger");
    FillBranch(Branch, Octet);
}


std::vector<hheavyhiggs::HEventSemiBranch * > hheavyhiggs::HEventSemiTagger::GetBranches(hanalysis::HEvent *const Event, const HObject::HTag Tag)
{
    Print(HInformation, "Get Event Tags");

    JetTag->HeavyParticles = {GluonId, TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger->GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger->GetBdt(Jets, JetPairReader);

    std::vector<HOctet> Octets;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet1() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet1() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet2() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet2() == Doublet.GetJet2()) continue;
            HOctet Octet(Sextet, Doublet);
//             Octet.SetTag(GetTag(Octet));
//             if (Octet.GetTag() == HBackground && Tag == HSignal) continue; TODO why is this here?
//             if (Octet.GetTag() != Tag) continue;
            Octets.push_back(Octet);
        }
    }

    if (Tag == HSignal && Octets.size() > 1) {
        Print(HInformation, "more than one event", Octets.size());
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }


//     if (Jets.size() > 5) {
        for (auto & Octet : Octets) {
            HEventStruct EventStruct;
            EventStruct.LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
            EventStruct.JetNumber = Event->GetJets()->GetJets().size();
            EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
            EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
            EventStruct.RestBBdt = 1;
            fastjet::PseudoJet RestJet(0., 0., 0., 0.);
            for (const auto & Jet : Jets) {
                if (Octet.GetSextet().GetTriplet1().GetSinglet() == Jet) continue;
                if (Octet.GetSextet().GetTriplet2().GetSinglet() == Jet) continue;
                if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1() == Jet) continue;
                if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2() == Jet) continue;
                if (Octet.GetDoublet().GetJet1() == Jet) continue;
                if (Octet.GetDoublet().GetJet2() == Jet) continue;
                EventStruct.RestHt += Jet.pt();
                EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
                EventStruct.RestBBdt *= Jet.user_info<hanalysis::HJetInfo>().GetBdt();
                RestJet += Jet;
            }
            if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
                EventStruct.RestM = RestJet.m();
                EventStruct.RestPt = RestJet.pt();
                EventStruct.RestRap = RestJet.rap();
                EventStruct.RestPhi = RestJet.phi();
            }
            Octet.SetEventStruct(EventStruct);
        }
//     }

    std::vector<hheavyhiggs::HEventSemiBranch *> EventSemiBranches;
    for (auto & Octet : Octets) {
        Octet.SetTag(Tag);
        hheavyhiggs::HEventSemiBranch *EventSemiBranch = new hheavyhiggs::HEventSemiBranch();
        FillBranch(EventSemiBranch, Octet);
        EventSemiBranches.push_back(EventSemiBranch);
    }

    return EventSemiBranches;

}


hanalysis::HObject::HTag hheavyhiggs::HEventSemiTagger::GetTag(const HOctet &Octet)
{
    Print(HInformation, "Get Sextet Tag");

    hanalysis::HJetInfo JetInfoB1 = Octet.GetSextet().GetTriplet1().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB1.ExtractFraction(BottomId, TopId);
    if (std::abs(JetInfoB1.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoL = Octet.GetSextet().GetTriplet1().GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoL.ExtractFraction(WId);
    if (std::abs(JetInfoL.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoL.GetMaximalId()) != sgn(JetInfoB1.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoB2 = Octet.GetSextet().GetTriplet2().GetSinglet().user_info<hanalysis::HJetInfo>();
    JetInfoB2.ExtractFraction(BottomId, TopId);
    if (JetInfoB1.GetMaximalId() != -JetInfoB2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoW1 = Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoW1.ExtractFraction(WId, TopId);
    if (std::abs(JetInfoW1.GetMaximalId()) != WId) return HBackground;
    if (sgn(JetInfoW1.GetMaximalId()) != sgn(JetInfoB2.GetMaximalId())) return HBackground;

    hanalysis::HJetInfo JetInfoW2 = Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2().user_info<hanalysis::HJetInfo>();
    JetInfoW2.ExtractFraction(WId, TopId);
    if (JetInfoW1.GetMaximalId() != JetInfoW2.GetMaximalId()) return HBackground;

    hanalysis::HJetInfo JetInfoB3 = Octet.GetDoublet().GetJet1().user_info<hanalysis::HJetInfo>();
    JetInfoB3.ExtractFraction(BottomId, GluonId);
    if (std::abs(JetInfoB3.GetMaximalId()) != BottomId) return HBackground;

    hanalysis::HJetInfo JetInfoB4 = Octet.GetDoublet().GetJet2().user_info<hanalysis::HJetInfo>();
    JetInfoB4.ExtractFraction(BottomId, GluonId);
    if (JetInfoB3.GetMaximalId() != -JetInfoB4.GetMaximalId()) return HBackground;

    return HSignal;
}




std::vector<HOctet> hheavyhiggs::HEventSemiTagger::GetBdt(const std::vector< hanalysis::HSextet > &Sextets, const std::vector< hanalysis::HDoublet > &Doublets, const std::vector<fastjet::PseudoJet> Jets, HEventStruct &EventStruct, const hanalysis::HReader *const EventSemiReader)
{
    Print(HInformation, "Get Event Tags");

    std::vector<HOctet> Octets;
//     std::map<float, HOctet> OctetMap;
    for (const auto & Doublet : Doublets) {
        for (const auto & Sextet : Sextets) {
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet1().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetSinglet() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet1() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet1() == Doublet.GetJet2()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet2() == Doublet.GetJet1()) continue;
            if (Sextet.GetTriplet2().GetDoublet().GetJet2() == Doublet.GetJet2()) continue;
            HOctet Octet(Sextet, Doublet, EventStruct);
            FillBranch(Octet);
            Octet.SetBdt(EventSemiReader->GetBdt());
//             OctetMap.insert(std::pair<float, HOctet>(Octet.GetBdt(), Octet));
            Octets.push_back(Octet);
        }
    }
//     Print(HError, "EventSize", OctetMap.size());
    std::vector<HOctet> FinalOctets;

    if (Octets.size() > 0) FinalOctets.push_back(*std::min_element(Octets.begin(), Octets.end()));

    if (Jets.size() > 6) {
        for (auto & Octet : FinalOctets) {
            Octet.EventStruct.RestBBdt = 1;
            fastjet::PseudoJet RestJet(0., 0., 0., 0.);
            for (const auto & Jet : Jets) {
                if (Octet.GetSextet().GetTriplet1().GetSinglet() == Jet) continue;
                if (Octet.GetSextet().GetTriplet2().GetSinglet() == Jet) continue;
                if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet1() == Jet) continue;
                if (Octet.GetSextet().GetTriplet2().GetDoublet().GetJet2() == Jet) continue;
                if (Octet.GetDoublet().GetJet1() == Jet) continue;
                if (Octet.GetDoublet().GetJet2() == Jet) continue;
                Octet.EventStruct.RestHt += Jet.pt();
                Octet.EventStruct.RestBTag += Jet.user_info<hanalysis::HJetInfo>().GetBTag();
                Octet.EventStruct.RestBBdt *= Jet.user_info<hanalysis::HJetInfo>().GetBdt();
                RestJet += Jet;
            }
            if (RestJet != fastjet::PseudoJet(0, 0, 0, 0)) {
                Octet.EventStruct.RestM = RestJet.m();
                Octet.EventStruct.RestPt = RestJet.pt();
                Octet.EventStruct.RestRap = RestJet.rap();
                Octet.EventStruct.RestPhi = RestJet.phi();
            }
        }
    }

    return FinalOctets;
}




std::vector<int> hheavyhiggs::HEventSemiTagger::ApplyBdt2(const ExRootTreeReader *const TreeReader, const std::string TreeName, const TFile *const ExportFile, TMVA::Reader *Reader)
{
    Print(HNotification, "Apply Bdt", EventBranchName);
    std::string Temp = EventBranchName; // TODO remove this dirty trick
    EventBranchName += "Reader";

    const int Steps = 20;
    std::vector<int> EventNumbers(Steps);

    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(EventBranchName.c_str());

    ExRootTreeWriter *TreeWriter = new ExRootTreeWriter(const_cast<TFile *>(ExportFile), TreeName.c_str());
    ExRootTreeBranch *ResultBranch = TreeWriter->NewBranch(EventBranchName.c_str(), HResultBranch::Class());

    for (const int EventNumber : HRange(const_cast<ExRootTreeReader *>(TreeReader)->GetEntries())) {

        const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(EventNumber);

        for (const int Entry : HRange(EventClonesArray->GetEntriesFast())) {


            HEventSemiBranch *Test = (HEventSemiBranch *) EventClonesArray->At(Entry);
            const float Bdt = Test->Bdt;

            HResultBranch *Export = static_cast<HResultBranch *>(ResultBranch->NewEntry());
            Export->Bdt = Bdt;


            for (int Step = 0; Step < Steps; ++Step) {
                const float Cut = float(2 * Step) / Steps;
                if (Bdt > Cut) ++EventNumbers.at(Step);
            }


        }

        TreeWriter->Fill();
        TreeWriter->Clear();
    }

    TreeWriter->Write();
    delete TreeWriter;
    EventBranchName = Temp;

    return EventNumbers;

}
