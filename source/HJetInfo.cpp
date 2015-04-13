# include "HJetInfo.hh"
# include "HTagPrivate.hh"

// class hanalysis::HJetInfoPrivate : public HTagPrivate {
//
// public:
//
//   HJetInfoPrivate() {}
//
//   void SetBTag(const int NewBTag);
//
//   std::vector<HConstituent> ApplyVertexResolution() const;
//
//   float SecondaryVertexResolution = 0.1;
//
//   float GetWeightSum() const;
//
//   float GetFamilyWeightSum() const;
//
//   std::map<int, float> JetFractions;
//
//   std::unordered_map<HFamily, float> JetFamily;
//
//   std::vector<HConstituent> Vertices;
//
//   int BTag;
//
// };
//
// void hanalysis::HJetInfoPrivate::SetBTag(const int NewBTag) {
//   BTag = NewBTag;
// }




hanalysis::HJetInfo::HJetInfo()
// : hanalysis::HTag(* new HJetInfoPrivate)
{
//     Debug = 4;
    Print(HDebug, "Constructor");
    BTagM = 0;
}

hanalysis::HJetInfo::HJetInfo(const int NewBTag)
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    BTagM = NewBTag;
}

hanalysis::HJetInfo::HJetInfo(const HConstituent &NewConstituent)
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    constituents_.push_back(NewConstituent);
    BTagM = 0;
}

hanalysis::HJetInfo::HJetInfo(const std::vector<HConstituent> &NewConstituents)
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    constituents_ = NewConstituents;
    BTagM = 0;
}

hanalysis::HJetInfo::HJetInfo(const std::vector<HConstituent> &NewConstituents, const int NewBTag)
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    constituents_ = NewConstituents;
    BTagM = NewBTag;
}

void hanalysis::HJetInfo::AddFamily(const HFamily &Family, const float Weight)
{
    Print(HDebug, "Add Constituent", Family.ParticleId, Family.Mother1Id, Weight);
    FamilyFractionsM[Family] += Weight;
//   Print(HDetailed, "Saved Weight", IdFractions[Family]);
}

void hanalysis::HJetInfo::ExtractFamilyFraction()
{

    Print(HInformation, "Extract Family Fraction");

    for (const auto & Constituent : Constituents()) {
        FamilyFractionsM[Constituent.Family()] += Constituent.Momentum().Pt();
    }
}

hanalysis::HFamily hanalysis::HJetInfo::MaximalFamily()
{

    Print(HDebug, "Get Maximal Id");
    std::pair<HFamily, float> Max = *std::max_element(FamilyFractionsM.begin(), FamilyFractionsM.end(), SortPairs());
    return Max.first;
}

void hanalysis::HJetInfo::AddParticle(const int ConstituentId, const float Weight)
{
    Print(HDebug, "Add Constituent", ConstituentId, Weight);
    IdFractions[ConstituentId] += Weight;
    Print(HDetailed, "Saved Weight", IdFractions[ConstituentId]);
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId)
{
    Print(HInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractionsM.begin(); Pair != FamilyFractionsM.end(); ++Pair) {

        if ((*Pair).first.ParticleId == ParticleId || (*Pair).first.Mother1Id == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else if ((*Pair).first.ParticleId == -ParticleId || (*Pair).first.Mother1Id == -ParticleId) AddParticle(-ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId, const int MotherId)
{
    Print(HInformation, "Extract Fraction", ParticleId, MotherId);

    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractionsM.begin(); Pair != FamilyFractionsM.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId && std::abs((*Pair).first.Mother1Id) == MotherId) AddParticle((*Pair).first.ParticleId, (*Pair).second);

        else AddParticle(IsrId, (*Pair).second);

    }
}

void hanalysis::HJetInfo::ExtractAbsFraction(const int ParticleId)
{
    Print(HInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractionsM.begin(); Pair != FamilyFractionsM.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId || std::abs((*Pair).first.Mother1Id) == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

float hanalysis::HJetInfo::GetWeightSum() const
{
    Print(HDebug, "Get Weight Sum", IdFractions.size());
    float WeightSum = std::accumulate(begin(IdFractions), end(IdFractions), 0.0, [](const float Previous, const std::pair<int, float> &Pair) {
        return (Previous + Pair.second);
    });
    Print(HDetailed, "Weight Sum", WeightSum);
    return WeightSum;
}

float hanalysis::HJetInfo::Fraction(const int ParticleId) const
{
    Print(HInformation, "Get Fraction", ParticleId);
    if (!IdFractions.count(ParticleId)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (IdFractions.at(ParticleId) / GetWeightSum());
}

float hanalysis::HJetInfo::MaximalFraction() const
{
    Print(HInformation, "Get Maximal Fraction");
    std::pair<int, float> MaximalWeight = *std::max_element(IdFractions.begin(), IdFractions.end(), SortPairs());
    if (GetWeightSum() == 0) {
        return 0;
    } else {
        return (MaximalWeight.second / GetWeightSum());
    }
}

int hanalysis::HJetInfo::MaximalId() const
{
    Print(HDebug, "Get Maximal Id");
    std::pair<int, float> Max = *std::max_element(IdFractions.begin(), IdFractions.end(), SortPairs());
    return Max.first;
}

void hanalysis::HJetInfo::PrintAllInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Infos");
    for (std::map<int, float>::const_iterator Pair = IdFractions.begin(); Pair != IdFractions.end(); ++Pair) {
        if (GetWeightSum() == 0) {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), 0);
        } else {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), (*Pair).second / GetWeightSum());
        }
    }
}


void hanalysis::HJetInfo::PrintAllConstituentInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Family Infos");
    for (const auto Constituent : Constituents()) {
        Print(Severity, "Jet Fraction", GetParticleName(Constituent.Family().ParticleId), GetParticleName(Constituent.Family().Mother1Id), Constituent.Family().ParticleVector.Pt(), Constituent.Family().MotherVector.Pt());
    }
}
void hanalysis::HJetInfo::PrintAllFamInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Family Infos");
    for (const auto Family : FamilyFractionsM) {
        Print(Severity, "Family Fraction", GetParticleName(Family.first.ParticleId), GetParticleName(Family.first.Mother1Id), Family.first.ParticleVector.Pt(), Family.first.MotherVector.Pt());
    }
}

fastjet::PseudoJet hanalysis::HJetInfo::VertexJet() const
{
    std::vector <HConstituent > RealVertices = ApplyVertexResolution();
    hanalysis::HFourVector Object;
    fastjet::PseudoJet Jet;
    for (const auto Vertex : RealVertices) {
//       Print(HError,"JetPt",Object.GetPseudoJet(Vertex.Momentum).pt());
        Jet = fastjet::join(Jet, Object.PseudoJet(Vertex.Momentum()));
    }
    return Jet;
//     return std::accumulate(RealVertices.rbegin(), RealVertices.rend(), Jet, Accu0());
}

struct Accu {
    float operator()(float result, const HConstituent &obj) {
        return (result + obj.Position().Vect().Pt());
    }

};

float hanalysis::HJetInfo::SumDisplacement() const
{
    Print(HDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = constituents_;
    TempVertices.erase(std::remove_if(TempVertices.begin(), TempVertices.end(), [&](HConstituent & Constituent) {
        return (Constituent.Position().Vect().Pt() < detector_geometry_.MinTrackerDistance || Constituent.Position().Vect().Pt() > detector_geometry_.MaxTrackerDistance || std::abs(Constituent.Momentum().Rapidity()) > detector_geometry_.MaxTrackerEta);
    }), TempVertices.end());

    return std::accumulate(TempVertices.rbegin(), TempVertices.rend(), 0, Accu());
}

float hanalysis::HJetInfo::MeanDisplacement() const
{
    Print(HDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = constituents_;
    TempVertices.erase(std::remove_if(TempVertices.begin(), TempVertices.end(), [&](const HConstituent & Constituent) {
        return (Constituent.Position().Vect().Pt() < detector_geometry_.MinTrackerDistance || Constituent.Position().Vect().Pt() > detector_geometry_.MaxTrackerDistance || std::abs(Constituent.Momentum().Rapidity()) > detector_geometry_.MaxTrackerEta);
    }), TempVertices.end());

    if (TempVertices.size() < 1) return 0;
    float Sum = std::accumulate(TempVertices.rbegin(), TempVertices.rend(), 0, Accu());

    return Sum / TempVertices.size();
}

float hanalysis::HJetInfo::MaxDisplacement() const
{
    Print(HDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = constituents_;
    TempVertices.erase(std::remove_if(TempVertices.begin(), TempVertices.end(), [&](const HConstituent & Constituent) {
        return (Constituent.Position().Vect().Pt() < detector_geometry_.MinTrackerDistance || Constituent.Position().Vect().Pt() > detector_geometry_.MaxTrackerDistance || std::abs(Constituent.Momentum().Rapidity()) > detector_geometry_.MaxTrackerEta);
    }), TempVertices.end());
    if (TempVertices.size() < 1) return 0;
    std::sort(TempVertices.begin(), TempVertices.end(), MaxDistance());
    return TempVertices.front().Position().Vect().Pt();
}


float hanalysis::HJetInfo::VertexMass() const
{
    Print(HDebug, "Get Vertex Mass");
    std::vector <HConstituent > RealVertices = ApplyVertexResolution();
//     TLorentzVector NewMomentum;
//     const float NewVertexMass = std::accumulate(RealVertices.begin(), RealVertices.end(), NewMomentum, [](TLorentzVector Momentum, stuff_value_t const& Constituent) { return Momentum + Constituent.Momentum(); });

    HConstituent Vertex;
    const float NewVertexMass = std::accumulate(RealVertices.begin(), RealVertices.end(), Vertex).Momentum().M();
    if (NewVertexMass < .1) return 0;
    return NewVertexMass;
}

float hanalysis::HJetInfo::VertexEnergy() const
{
    Print(HDebug, "Get Energy Fraction");
    float NewVertexEnergy = 0;
    for (const auto & Vertex : constituents_) if (Vertex.Position().Vect().Pt() > detector_geometry_.MinTrackerDistance && Vertex.Position().Vect().Pt() < detector_geometry_.MaxTrackerDistance && std::abs(Vertex.Momentum().Rapidity()) < detector_geometry_.MaxTrackerEta) NewVertexEnergy += Vertex.Momentum().E();
    return NewVertexEnergy;
}

std::vector<HConstituent> hanalysis::HJetInfo::ApplyVertexResolution() const
{
    Print(HDebug, "Apply Vertex Resolution");
    std::vector <HConstituent > RealVertices;
    Print(HDebug, "Vertex Number", constituents_.size());
    if (constituents_.size() == 0) return RealVertices;
    for (std::vector <HConstituent >::const_iterator Constituent = constituents_.begin(); Constituent != constituents_.end(); ++Constituent) {
        //         Print(HError,"dist",(*Constituent).Position().Vect().Pt());
//         Print(HError,"pt",(*Constituent).Momentum().Pt());
        if ((*Constituent).Position().Vect().Pt() > detector_geometry_.MinTrackerDistance && (*Constituent).Position().Vect().Pt() < detector_geometry_.MaxTrackerDistance  && std::abs((*Constituent).Momentum().Rapidity()) < detector_geometry_.MaxTrackerEta) {
            RealVertices.push_back(*Constituent);
        }
    }
    Print(HDebug, "Real Vertex Number", RealVertices.size());
    return RealVertices;
}

float hanalysis::HJetInfo::ElectroMagneticRadius(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float Weight = 0;
    for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HPhoton) {
            Energy += Constituent.Momentum().Et();
            Weight += Constituent.Momentum().Et() * Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum()));
        }
    if (Energy == 0) return 0;
    else return Weight / Energy;
}

float hanalysis::HJetInfo::TrackRadius(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float Weight = 0;
    for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HTrack) {
            Energy += Constituent.Momentum().Et();
            Weight += Constituent.Momentum().Et() * Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum()));
        }
    if (Energy == 0) return 0;
    else return Weight / Energy;
}


struct WrongDetector {
    WrongDetector(const HConstituent::SubDetector Detector) {
        this->Detector = Detector;
    }
    bool operator()(const HConstituent &Constituent) {
        return (Constituent.sub_detector() != Detector);
    }
    HConstituent::SubDetector Detector;
};

struct MaxPt {
    bool operator()(const HConstituent &Constituent1, const HConstituent &Constituent2) {
        return (Constituent1.Momentum().Pt() > Constituent2.Momentum().Pt());
    }
};


struct Accu2 {
    float operator()(float result, const HConstituent &obj) {
        return (result + obj.Momentum().Pt());
    }

};

float hanalysis::HJetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<HConstituent> Const = Constituents();
    Const.erase(std::remove_if(Const.begin(), Const.end(), WrongDetector(HConstituent::HTrack)), Const.end());
    std::sort(Const.begin(), Const.end(), MaxPt());
    float Sum = std::accumulate(Const.rbegin(), Const.rend(), 0, Accu2());
    return Const.front().Momentum().Pt() / Sum;
}

float hanalysis::HJetInfo::CoreEnergyFraction(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float CoreEnergy = 0;
    for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HPhoton) {
            Energy += Constituent.Momentum().Et();
            if (Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum())) < 0.2) CoreEnergy += Constituent.Momentum().Et();
        }
    if (Energy == 0) return 0;
    else return CoreEnergy / Energy;

}

// float hanalysis::HJetInfo::CoreEnergyFraction(const fastjet::PseudoJet &Jet)
// {
//   float Energy = 0;
//   float CoreEnergy = 0;
//   for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HPhoton) {
//     Energy += Constituent.Momentum().Et();
//     if(Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum()))<0.2) CoreEnergy += Constituent.Momentum().Et();
//   }
//   return CoreEnergy / Energy;
//
// }

float hanalysis::HJetInfo::ElectroMagneticFraction() const
{
    float EMEnergy = 0;
    float Energy = 0;
    for (const auto & Constituent : Constituents()) {
        Energy += Constituent.Momentum().Et();
        if (Constituent.sub_detector() == HConstituent::HPhoton) EMEnergy += Constituent.Momentum().Et();
    }
    if (Energy == 0) return 0;
    else  EMEnergy / Energy;

}

float hanalysis::HJetInfo::ClusterMass() const
{
    fastjet::PseudoJet Jet;
    for (const auto & Constituent : Constituents()) {
        if (Constituent.sub_detector() == HConstituent::HPhoton) Jet += Constituent.Momentum();
    }
    return Jet.m();

}

float hanalysis::HJetInfo::TrackMass() const
{
    fastjet::PseudoJet Jet;
    for (const auto & Constituent : Constituents()) {
        if (Constituent.sub_detector() == HConstituent::HTrack) Jet += Constituent.Momentum();
    }
    return Jet.m();

}



