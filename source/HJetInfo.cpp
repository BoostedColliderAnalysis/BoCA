# include "HJetInfo.hh"
// # include "HTagPrivate.hh"
//
// class hanalysis::HJetInfoPrivate : public HTagPrivate {
//
// public:
//
//   HJetInfoPrivate() {}
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

void hanalysis::HJetInfo::AddParticle(const int ConstituentId, const float Weight)
{
    Print(HDebug, "Add Constituent", ConstituentId, Weight);
    IdFractions[ConstituentId] += Weight;
    Print(HDetailed, "Saved Weight", IdFractions[ConstituentId]);
}

void hanalysis::HJetInfo::AddFamily(const HFamily &Family, const float Weight)
{
    Print(HDebug, "Add Constituent", Family.ParticleId, Family.Mother1Id, Weight);
    FamilyFractions[Family] += Weight;
//   Print(HDetailed, "Saved Weight", IdFractions[Family]);
}

void hanalysis::HJetInfo::ExtractFamilyFraction() {

    Print(HInformation, "Extract Family Fraction");

    for (const auto &Constituent : Constituents()) {
        FamilyFractions[Constituent.Family()] = Constituent.Momentum().Pt();
    }
}

// void hanalysis::HJetInfo::AddFamily(const HFamily Family, const float Weight)
// {
//     Print(HDebug, "Add Constituent", Family.ParticleId, Family.Mother1Id, Weight);
//     JetFamily[Family] += Weight;
// //   Print(HDetailed, "Saved Weight", JetFamily[Family].ParticleId, JetFamily[Family].Mother1Id);
// }
//
// void hanalysis::HJetInfo::CalculateJetFamily()
// {
//   for(const auto Vertex : ConstituentsM){
//     AddFamily(Vertex.Family(),Vertex.Momentum().Pt());
//   }
//
// }

float hanalysis::HJetInfo::GetWeightSum() const
{
    Print(HDebug, "Get Weight Sum", IdFractions.size());
    float WeightSum = std::accumulate(begin(IdFractions), end(IdFractions), 0.0, [](const float Previous, const std::pair<int, float> &Pair) {
        return (Previous + Pair.second);
    });
    Print(HDetailed, "Weight Sum", WeightSum);
    return WeightSum;
}

// float hanalysis::HJetInfo::GetFamilyWeightSum() const
// {
//     Print(HDebug, "Get Weight Sum", JetFamily.size());
//     float WeightSum = std::accumulate(begin(JetFamily), end(JetFamily), 0.0, [](const float Previous, const std::pair<HFamily, float> &Pair) {
//         return (Previous + Pair.second);
//     });
//     Print(HDetailed, "Weight Sum", WeightSum);
//     return WeightSum;
// }

float hanalysis::HJetInfo::Fraction(const int ParticleId) const
{
    Print(HInformation, "Get Fraction", ParticleId);
    if (!IdFractions.count(ParticleId)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (IdFractions.at(ParticleId) / GetWeightSum());
}

// float hanalysis::HJetInfo::AbsFraction(const int ParticleId) const
// {
//   Print(HInformation, "Get Fraction", ParticleId);
//   if (!IdFractions.count(std::abs(ParticleId))) return 0;
//   if (GetWeightSum() == 0)   return 0;
//   return (IdFractions.at(std::abs(ParticleId)) / GetWeightSum());
// }

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId)
{
    Print(HInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractions.begin(); Pair != FamilyFractions.end(); ++Pair) {

        if ((*Pair).first.ParticleId == ParticleId || (*Pair).first.Mother1Id == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else if ((*Pair).first.ParticleId == -ParticleId || (*Pair).first.Mother1Id == -ParticleId) AddParticle(-ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

void hanalysis::HJetInfo::ExtractAbsFraction(const int ParticleId)
{
  Print(HInformation, "Extract Fraction", ParticleId);
  ExtractFamilyFraction();
  for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractions.begin(); Pair != FamilyFractions.end(); ++Pair) {

    if (std::abs((*Pair).first.ParticleId) == ParticleId || std::abs((*Pair).first.Mother1Id) == ParticleId) AddParticle(ParticleId, (*Pair).second);

    else AddParticle((*Pair).first.ParticleId, (*Pair).second);
  }
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId, const int MotherId)
{
    Print(HInformation, "Extract Fraction", ParticleId, MotherId);

    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractions.begin(); Pair != FamilyFractions.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId && std::abs((*Pair).first.Mother1Id) == MotherId) AddParticle((*Pair).first.ParticleId, (*Pair).second);

        else AddParticle(IsrId, (*Pair).second);

    }
}

// float hanalysis::HJetInfo::GetFamily(const HFamily Family) const
// {
//     Print(HInformation, "Get Fraction", Family.ParticleId);
//     if (!JetFamily.count(Family)) return 0;
//     if (GetWeightSum() == 0)   return 0;
//     return (JetFamily.at(Family) / GetWeightSum());
// }

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

// float hanalysis::HJetInfo::MaximalAbsFraction() const
// {
//   Print(HInformation, "Get Maximal Fraction");
//   std::pair<int, float> MaximalWeight = *std::max_element(IdFractions.begin(), IdFractions.end(), SortAbsPairs());
//   if (GetWeightSum() == 0) {
//     return 0;
//   } else {
//     return (MaximalWeight.second / GetWeightSum());
//   }
// }

// bool hanalysis::HJetInfo::HasParticle(const int ParticleId) const
// {
//     Print(HInformation, "Has Particle", ParticleId);
//     if (JetFractions.find(ParticleId) == JetFractions.end()) return 0;
//     return 1;
// }

int hanalysis::HJetInfo::MaximalId() const
{
    Print(HDebug, "Get Maximal Id");
    std::pair<int, float> Max = *std::max_element(IdFractions.begin(), IdFractions.end(), SortPairs());
    return Max.first;
}

// struct SortAbsPairs {
//   inline bool operator()(const std::pair<int, float> &Pair1,const std::pair<int, float> &Pair2) {
//     return (std::abs(Pair1.second) < std::abs(Pair2.second));
//   }
// };
//
//
// int hanalysis::HJetInfo::MaximalAbsId() const
// {
//   Print(HDebug, "Get Maximal Id");
//   std::pair<int, float> Max = *std::max_element(IdFractions.begin(), IdFractions.end(), SortAbsPairs());
//   return Max.first;
// }

// void hanalysis::HJetInfo::Clear()
// {
//     Print(HInformation, "Clear");
//     JetFractions.clear();
// }

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

// void hanalysis::HJetInfo::PrintAllFamilyInfos(const HSeverity Severity) const
// {
//     Print(HDebug, "Print All Infos");
//     int Counter = 1;
//     for (std::unordered_map<HFamily, float>::const_iterator Pair = JetFamily.begin(); Pair != JetFamily.end(); ++Pair) {
//         if (GetFamilyWeightSum() == 0) {
//             Print(Severity, "Jet Family Fraction", GetParticleName((*Pair).first.ParticleId), GetParticleName((*Pair).first.Mother1Id), 0);
//         } else {
//             Print(Severity, "Jet Family Fraction", Counter, GetParticleName((*Pair).first.ParticleId), GetParticleName((*Pair).first.Mother1Id), (*Pair).second / GetFamilyWeightSum());
//         }
//         ++Counter;
//     }
// }

// struct Accu0 {
//     fastjet::PseudoJet operator()(fastjet::PseudoJet result, const HConstituent &obj) {
//         hanalysis::HFourVector Object;
//         return (result + Object.GetPseudoJet(obj.Momentum()));
//     }
//
// };

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
        return (result + obj.Position().Vect().Mag());
    }

};

float hanalysis::HJetInfo::SumDisplacement() const
{
    Print(HDebug, "Get Jet Displacement"); // TODO is there a way to get rid of the const?
    if (ConstituentsM.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = ConstituentsM;
    TempVertices.erase(std::remove_if(TempVertices.begin(), TempVertices.end(), [](HConstituent & Constituent) {
        return Constituent.Position().Vect().Mag() < 0.1;
    }), TempVertices.end());

    return std::accumulate(TempVertices.rbegin(), TempVertices.rend(), 0, Accu());
}

float hanalysis::HJetInfo::MeanDisplacement() const
{
    Print(HDebug, "Get Jet Displacement"); // TODO is there a way to get rid of the const?
    if (ConstituentsM.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = ConstituentsM;
    TempVertices.erase(std::remove_if(TempVertices.begin(), TempVertices.end(), [](const HConstituent & Constituent) {
        return Constituent.Position().Vect().Mag() < 0.1;
    }), TempVertices.end());

    if (TempVertices.size() < 1) return 0;
    float Sum = std::accumulate(TempVertices.rbegin(), TempVertices.rend(), 0, Accu());

    return Sum / TempVertices.size();
}

float hanalysis::HJetInfo::MaxDisplacement() const
{
    Print(HDebug, "Get Jet Displacement"); // TODO is there a way to get rid of the const?
    if (ConstituentsM.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = ConstituentsM;
    std::sort(TempVertices.begin(), TempVertices.end(), SortByDistance());
    if (TempVertices.front().Position().Vect().Mag() > SecondaryVertexResolution) return TempVertices.front().Position().Vect().Mag();
    return 0;
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
    for (const auto & Vertex : ConstituentsM) if (Vertex.Position().Vect().Mag() > SecondaryVertexResolution) NewVertexEnergy += Vertex.Momentum().E();
    return NewVertexEnergy;
}

std::vector<HConstituent> hanalysis::HJetInfo::ApplyVertexResolution() const
{
    Print(HDebug, "Apply Vertex Resolution");
    std::vector <HConstituent > RealVertices;
    Print(HDebug,"Vertex Number",ConstituentsM.size());
    if (ConstituentsM.size() == 0) return RealVertices;
    for (std::vector <HConstituent >::const_iterator Constituent = ConstituentsM.begin(); Constituent != ConstituentsM.end(); ++Constituent) {
//         Print(HError,"dist",(*Constituent).Position().Vect().Mag());
//         Print(HError,"pt",(*Constituent).Momentum().Pt());
        if ((*Constituent).Position().Vect().Mag() > SecondaryVertexResolution) {
            RealVertices.push_back(*Constituent);
        }
    }
    Print(HDebug,"Real Vertex Number",RealVertices.size());
    return RealVertices;
}

