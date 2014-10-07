# include "HEPTopTagger.hh"

float HEPTopTagger::cos_theta_h() const
{
    return CheckCosTheta(TopJetCandidate, TopSubJetVector[1], TopSubJetVector[2]); // m23 is closest to mW
}

float HEPTopTagger::dr_bjj() const
{
    if (TopSubJetVector.size() != 3) {
        return -1;
    }
    return MaximalCylinderDistance(TopSubJetVector[0], TopSubJetVector[1], TopSubJetVector[2]);
}

vector<float> HEPTopTagger::dr_values() const
{
    vector<float> CylinderDistanceVector;
    CylinderDistanceVector.push_back(sqrt(TopSubJetVector[1].squared_distance(TopSubJetVector[2])));
    CylinderDistanceVector.push_back(sqrt(TopSubJetVector[0].squared_distance(TopSubJetVector[2])));
    CylinderDistanceVector.push_back(sqrt(TopSubJetVector[0].squared_distance(TopSubJetVector[1])));
    return (CylinderDistanceVector);
}


float HEPTopTagger::MaximalCylinderDistance(const PseudoJet &Jet1, const PseudoJet &Jet2, const PseudoJet &Jet3) const
{
    PseudoJet Jet12, Jet13, Jet23;
    Jet12 = Jet1 + Jet2;
    Jet13 = Jet1 + Jet3;
    Jet23 = Jet2 + Jet3;

    float CylinderDistance12 = sqrt(Jet1.squared_distance(Jet2));
    float CylinderDistance23 = sqrt(Jet2.squared_distance(Jet3));
    float CylinderDistance31 = sqrt(Jet3.squared_distance(Jet1));
    float CylinderDistance1 = CylinderDistance12, CylinderDistance2 = CylinderDistance12;

    if (CylinderDistance12 <= CylinderDistance23 && CylinderDistance12 <= CylinderDistance31) {
        CylinderDistance1 = CylinderDistance12;
        CylinderDistance2 = sqrt(Jet12.squared_distance(Jet3));
    };
    if (CylinderDistance23 < CylinderDistance12 && CylinderDistance23 <= CylinderDistance31) {
        CylinderDistance1 = CylinderDistance23;
        CylinderDistance2 = sqrt(Jet23.squared_distance(Jet1));
    };
    if (CylinderDistance31 < CylinderDistance12 && CylinderDistance31 < CylinderDistance23) {
        CylinderDistance1 = CylinderDistance31;
        CylinderDistance2 = sqrt(Jet13.squared_distance(Jet2));
    };
    return max(CylinderDistance1, CylinderDistance2);
}

float HEPTopTagger::CheckCosTheta(const PseudoJet &Jet, const PseudoJet &SubJet1, const PseudoJet &SubJet2) const
{
    // the two jets of interest: top and lower-pt prong of W
    PseudoJet SoftWJet;
    PseudoJet TopJet = Jet;

    if (SubJet1.perp2() < SubJet2.perp2()) {
        SoftWJet = SubJet1;
    } else {
        SoftWJet = SubJet2;
    }

    // transform these jets into jets in the rest frame of the W
    SoftWJet.unboost(SubJet1 + SubJet2);
    TopJet.unboost(SubJet1 + SubJet2);

    float CosTheta = (SoftWJet.px() * TopJet.px() + SoftWJet.py() * TopJet.py() + SoftWJet.pz() * TopJet.pz()) / sqrt(SoftWJet.modp2() * TopJet.modp2());
    return (CosTheta);
}

void HEPTopTagger::FindHardSubstructure(const PseudoJet &JetWithSubStructure, vector<PseudoJet> &JetSubStructureVector)
{
    PseudoJet Parent1(0, 0, 0, 0), Parent2(0, 0, 0, 0);
    if (JetWithSubStructure.m() < SubJetMassMax || !TopClusterSequence->has_parents(JetWithSubStructure, Parent1, Parent2)) {

        JetSubStructureVector.push_back(JetWithSubStructure);

    } else {

        if (Parent1.m() < Parent2.m()) swap(Parent1, Parent2);
        FindHardSubstructure(Parent1, JetSubStructureVector);
        if (Parent1.m() < MassDropThreshold * JetWithSubStructure.m()) FindHardSubstructure(Parent2, JetSubStructureVector);

    }

}

void HEPTopTagger::StoreTopSubJets(const vector<PseudoJet> &SubTopVector)
{
    TopSubJetVector.resize(0);
    float m12 = (SubTopVector[0] + SubTopVector[1]).m();
    float m13 = (SubTopVector[0] + SubTopVector[2]).m();
    float m23 = (SubTopVector[1] + SubTopVector[2]).m();
    //     float m123 = (SubTopVector[0] + SubTopVector[1] + SubTopVector[2]).m();
    float dm12 = fabs(m12 - WMass);
    float dm13 = fabs(m13 - WMass);
    float dm23 = fabs(m23 - WMass);
    //float dm_min=min(dm12,min(dm13,dm23));
    if (dm23 <= dm12 && dm23 <= dm13) {
        TopSubJetVector.push_back(SubTopVector[0]); //supposed to be b
        TopSubJetVector.push_back(SubTopVector[1]); //W-jet 1
        TopSubJetVector.push_back(SubTopVector[2]); //W-jet 2
    } else if (dm13 <= dm12 && dm13 < dm23) {
        TopSubJetVector.push_back(SubTopVector[1]); //supposed to be b
        TopSubJetVector.push_back(SubTopVector[0]); //W-jet 1
        TopSubJetVector.push_back(SubTopVector[2]); //W-jet 2
    } else if (dm12 < dm23 && dm12 < dm13) {
        TopSubJetVector.push_back(SubTopVector[2]); //supposed to be b
        TopSubJetVector.push_back(SubTopVector[0]); //W-jet 1
        TopSubJetVector.push_back(SubTopVector[1]); //W-jet 2
    }
    return;
}

bool HEPTopTagger::CheckMassCriteria(const vector<PseudoJet> &TopCandidateSubJetVector) const
{
    bool MassCheckBool = false;
    float m12 = (TopCandidateSubJetVector[0] + TopCandidateSubJetVector[1]).m();
    float m13 = (TopCandidateSubJetVector[0] + TopCandidateSubJetVector[2]).m();
    float m23 = (TopCandidateSubJetVector[1] + TopCandidateSubJetVector[2]).m();
    float m123 = (TopCandidateSubJetVector[0] + TopCandidateSubJetVector[1] + TopCandidateSubJetVector[2]).m();

    float Norm = m23 / m123;
    float Ratio32 = m13 / m12;
    float Ratio23 = m12 / m13;

    if ((atan(Ratio32) > M13CutMin
            && M13CutMax > atan(Ratio32)
            && (Norm > MassRatioMin && MassRatioMax > Norm))
            || ((pow(Norm, 2) < 1 - pow(MassRatioMin, 2) * (1 + pow(Ratio32, 2)))
                && (pow(Norm, 2) > 1 - pow(MassRatioMax, 2) * (1 + pow(Ratio32, 2)))
                && (Norm > M23Cut))
            || ((pow(Norm, 2)  < 1 - pow(MassRatioMin, 2) * (1 + pow(Ratio23, 2)))
                && (pow(Norm, 2) > 1 - pow(MassRatioMax, 2) * (1 + pow(Ratio23, 2)))
                && (Norm > M23Cut))) MassCheckBool = true;

    return MassCheckBool;


}

HEPTopTagger::HEPTopTagger(const ClusterSequence &cs
                           , const PseudoJet &jet)
    :  debugg(false)
    , TopClusterSequence(&cs)
    , TopCandidateJet(jet)
    , TopMass(173.5)
    , WMass(80.39)
    , MassDropThreshold(0.8)
    , SubJetMassMax(30.)
    , TopMassMin(173.5 - 25.)
    , TopMassMax(173.5 + 25.)
    , MassRatioMin(0.85 * 80.39 / 173.5)
    , MassRatioMax(1.15 * 80.39 / 173.5)
    , M23Cut(0.35)
    , M13CutMin(0.2)
    , M13CutMax(1.3)
    , NFilterMax(5)
    , FilterJetAlgorithm(cambridge_algorithm)
    , ReclusterJetAlgorithm(cambridge_algorithm)
{}

HEPTopTagger::HEPTopTagger(const ClusterSequence &cs,
                           const PseudoJet &jet,
                           float topmass,
                           float wmass)
    : debugg(false)
    , TopClusterSequence(&cs)
    , TopCandidateJet(jet)
    , TopMass(topmass)
    , WMass(wmass)
    , MassDropThreshold(0.8)
    , SubJetMassMax(30.)
    , TopMassMin(topmass - 25.)
    , TopMassMax(topmass + 25.)
    , MassRatioMin(0.85 * wmass / topmass)
    , MassRatioMax(1.15 * wmass / topmass)
    , M23Cut(0.35)
    , M13CutMin(0.2)
    , M13CutMax(1.3)
    , NFilterMax(5)
    , FilterJetAlgorithm(cambridge_algorithm)
    , ReclusterJetAlgorithm(cambridge_algorithm)
{}

HEPTopTagger::HEPTopTagger(const ClusterSequence &cs,
                           const PseudoJet &jet,
                           float topmass,
                           float wmass,
                           bool Debug)
    : debugg(Debug)
    , TopClusterSequence(&cs)
    , TopCandidateJet(jet)
    , TopMass(topmass)
    , WMass(wmass)
    , MassDropThreshold(0.8)
    , SubJetMassMax(30.)
    , TopMassMin(topmass - 25.)
    , TopMassMax(topmass + 25.)
    , MassRatioMin(0.85 * wmass / topmass)
    , MassRatioMax(1.15 * wmass / topmass)
    , M23Cut(0.35)
    , M13CutMin(0.2)
    , M13CutMax(1.3)
    , NFilterMax(5)
    , FilterJetAlgorithm(cambridge_algorithm)
    , ReclusterJetAlgorithm(cambridge_algorithm)
{}

void HEPTopTagger::run_tagger()
{
    TopMassDelta = 1000000000000.0;
    TopJetCandidate.reset(0., 0., 0., 0.);
    TopCount = 0;
    TopSubStructureSum = 0;
    MightBeTop = MasscutPassed = false;

    TopSubJetVector.clear();
    TopHadronVector.clear();

    if (debugg) {
        cout << "topmass in top_tagger: " << TopMass << endl;
        cout << "wmass in top_tagger: " << WMass << endl;
        cout << "jet input HEPTopTagger: " << endl;
        //printjet(_jet);
    }

    // input this_jet, output TopPartVector
    // store hard substructure of the top candidate
    TopHardSubstructureVector.clear();
    FindHardSubstructure(TopCandidateJet, TopHardSubstructureVector);
    TopSubStructureSum = TopHardSubstructureVector.size();

    // these events are not interesting
    if (TopSubStructureSum < 3) {
        return;
    }

    /// Loop over First Top Part
    for (int TopSubStructureNumber1 = 0; TopSubStructureNumber1 < TopSubStructureSum; TopSubStructureNumber1++) {

        /// Loop over Second Top Part
        for (int TopSubStructureNumber2 = TopSubStructureNumber1 + 1; TopSubStructureNumber2 < TopSubStructureSum; TopSubStructureNumber2++) {

            /// Loop over Third Top Part
            for (int TopSubStructureNumber3 = TopSubStructureNumber2 + 1; TopSubStructureNumber3 < TopSubStructureSum; TopSubStructureNumber3++) {

                /// define top_constituents candidate before filtering
                vector<PseudoJet> TopConstituentsVector = TopClusterSequence -> constituents(TopHardSubstructureVector[TopSubStructureNumber1]);
                TopClusterSequence->add_constituents(TopHardSubstructureVector[TopSubStructureNumber2], TopConstituentsVector);
                TopClusterSequence->add_constituents(TopHardSubstructureVector[TopSubStructureNumber3], TopConstituentsVector);

                /// define Filtering: FilterTopR and jetdefinition
                float FilterTopR = min(0.3, 0.5 * sqrt(min(TopHardSubstructureVector[TopSubStructureNumber3].squared_distance(TopHardSubstructureVector[TopSubStructureNumber2]), min(TopHardSubstructureVector[TopSubStructureNumber1].squared_distance(TopHardSubstructureVector[TopSubStructureNumber2]), TopHardSubstructureVector[TopSubStructureNumber3].squared_distance(TopHardSubstructureVector[TopSubStructureNumber1])))));
                JetDefinition FilterJetDefinition(FilterJetAlgorithm, FilterTopR);
                vector<PseudoJet> FilteredTopConstituentsVector = Filtering(TopConstituentsVector, FilterJetDefinition);
                PseudoJet TopCandidate = SumJetsOfJetVector(FilteredTopConstituentsVector);
                if (TopCandidate.m() < TopMassMin || TopMassMax < TopCandidate.m()) continue;
                TopCount++;

                // obtain 3 subjets
                JetDefinition ReclusterJetDefinition(ReclusterJetAlgorithm, 3.14 / 2);
                ClusterSequence SubTopClusterSequence(FilteredTopConstituentsVector, ReclusterJetDefinition);
                vector <PseudoJet> SubTopVector = sorted_by_pt(SubTopClusterSequence.exclusive_jets(3));
                CandidateVectorVector.push_back(SubTopVector); //

                // transfer infos of the positively identified top to the outer world
                float TopCandidateMassDelta = fabs(TopCandidate.m() - TopMass);
                if (TopCandidateMassDelta < TopMassDelta) {

                    TopMassDelta = TopCandidateMassDelta;
                    MightBeTop = true;
                    TopJetCandidate = TopCandidate;
                    StoreTopSubJets(SubTopVector);
                    TopHadronVector = FilteredTopConstituentsVector;
                    MasscutPassed = CheckMassCriteria(SubTopVector);

                } // end TopCandidateMassDelta < TopMassDelta

            } // end ThirdTopPartNumber

        } // end SecondTopPartNumber

    } // end FirstTopPartNumber

    return;

}

vector<PseudoJet> HEPTopTagger::Filtering(const vector<PseudoJet> &TopConstituentsVector, const JetDefinition &FilterJetDefinition)
{

    ClusterSequence TopFilterClusterSequence(TopConstituentsVector, FilterJetDefinition);
    /// Contiants the inclusive Jets sorted by Pt
    vector<PseudoJet> InclusiveJetVector = sorted_by_pt(TopFilterClusterSequence.inclusive_jets());

    vector<PseudoJet> FilteredTopConstituentsVector;
    int TopSubJetSum = InclusiveJetVector.size();
    int TopsubJetMax = min(NFilterMax, TopSubJetSum);
    for (int TopSubJetNumber = 0; TopSubJetNumber < TopsubJetMax ; TopSubJetNumber++) {

        /// adds InclusiveJetVector Constituents onto returnvector
        TopFilterClusterSequence.add_constituents(InclusiveJetVector[TopSubJetNumber], FilteredTopConstituentsVector);

    }

    return FilteredTopConstituentsVector;

}

PseudoJet HEPTopTagger::SumJetsOfJetVector(const vector<PseudoJet> &JetVector)
{
    int JetSum = JetVector.size();
    PseudoJet TotalJet;
    TotalJet.reset(0., 0., 0., 0.);
    for (int JetNumber = 0; JetNumber < JetSum; JetNumber++) {
        TotalJet += JetVector.at(JetNumber);
    }
    return TotalJet;
}

void HEPTopTagger::get_info() const
{
    cout << "maybe_top: " <<  MightBeTop << endl;
    cout << "mascut_passed: " <<  MasscutPassed << endl;
    cout << "top candidate mass:" <<  TopJetCandidate.m() << endl;
    cout << "top candidate (pt, eta, phi): (" <<  TopJetCandidate.perp() << "," <<  TopJetCandidate.eta() << "," << TopJetCandidate.phi_std() << ")" << endl;
    cout << "hadrons size: " <<  TopHadronVector.size() << endl;
    cout << "topcount: " <<  TopCount << endl;
    cout << "parts size: " <<  TopSubStructureSum << endl;
    cout << "delta_top: " <<  TopMassDelta << endl;
    return;
}


void HEPTopTagger::get_setting() const
{
    cout << "top mass: " <<  TopMass << endl;
    cout << "W mass: " <<  WMass << endl;
    cout << "top mass range: [" << TopMassMin << ", " << TopMassMax << "]" << endl;
    cout << "W mass ratio range: [" << MassRatioMin << ", " << MassRatioMax << "] ([" << MassRatioMin *TopMass / WMass << "%, " << MassRatioMax *TopMass / WMass << "%])" << endl;
    cout << "mass ratio cut: (m23cut, m13min, m13max)=(" << M23Cut << ", " << M13CutMin << ", " << M13CutMax << ")" << endl;
    cout << "mass_drop_threshold: " << MassDropThreshold << endl;
    cout << "max_subjet_mass: " << SubJetMassMax << endl;
    cout << "n_filtering: " << NFilterMax << endl;
    cout << "JetAlgorithm for filtering: " << FilterJetAlgorithm << endl;
    cout << "JetAlgorithm for reclustering: " << ReclusterJetAlgorithm << endl;
    return;
}
