# include "TopHadronicTagger.hh"
# include "HEPTopTagger.hh"

hanalysis::TopHadronicTagger::TopHadronicTagger()
{


    Print(HNotification, "Constructor");

}

hanalysis::TopHadronicTagger::~TopHadronicTagger()
{

    Print(HNotification, "Destructor");

}

HJets hanalysis::TopHadronicTagger::GetTops(std::vector< fastjet::PseudoJet > &EFlowJets)
{

    Print(HInformation, "Tagging Top");

//     float CellRap = 0.1;
//     HJets hadrons;

//     ifstream fin("sample_event.dat", ifstream::in);
//     ReadEvent(fin, hadrons);
//     ofstream fout("sample_event_display.dat", ifstream::out);
//     ofstream fout2("sample_event_out.dat", ifstream::out);
//     output_vec_pseudojet(fout2, hadrons);

    //  jet definition
    const float ConeSize = 1.5;
    const fastjet::JetDefinition JetDefinition(fastjet::cambridge_algorithm, ConeSize);

    HJets GranulatedJets = GetGranulatedJets(EFlowJets);

    // run the jet finding; find the hardest jet
    const fastjet::ClusterSequence ClusterSequence(GranulatedJets, JetDefinition);
    const float PtMin = 200.;
    HJets Jets = sorted_by_pt(ClusterSequence.inclusive_jets(PtMin));

//     unsigned candsizesum = 0;

    HJets TopJets;

    for (const auto & Jet : Jets) {

//         const float topmass = 172.3;
//         const float wmass = 80.4;
//         HEPTopTagger TopTagger(ClusterSequence, Jet, topmass, wmass);
        HEPTopTagger TopTagger(ClusterSequence, Jet);

        TopTagger.set_top_range(150., 200.);
        std::cout << "========= Top Tagger ============" << std::endl;
        TopTagger.run_tagger();
//         cout << "-------- setting  --------" << endl;
//         TopTagger.get_setting();
//         cout << "-------- resutls  --------" << endl;
//         TopTagger.get_info();

//         if (TopTagger.is_masscut_passed())
        {

            std::cout << "### masscut_passed ###" << std::endl;

            fastjet::PseudoJet top = TopTagger.top_candidate();
//             fastjet::PseudoJet b = TopTagger.top_subjets().at(0);
//             fastjet::PseudoJet W1 = TopTagger.top_subjets().at(1);
//             fastjet::PseudoJet W2 = TopTagger.top_subjets().at(2);
//             std::cout << "top mass: " << top.m() << std::endl;
//             cout << "bottom mass: " << b.m() << endl;
//             cout << "W mass: " << (W1 + W2).m() << endl;

            TopJets.push_back(top);

        }

    }

    return TopJets;

}

HJets hanalysis::TopHadronicTagger::GetGranulatedJets(HJets &EFlowJets)
{


    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaRap = 0.1;
    const float CellDeltaPhi = 0.1;
    const float PtCutOff = 0.5;

//     float pi = 3.142592654;
    HJets GranulatedJets;
    GranulatedJets.clear();

    EFlowJets = sorted_by_pt(EFlowJets);
    GranulatedJets.push_back(EFlowJets[0]);

    for (unsigned i = 1; i < EFlowJets.size(); ++i) {
        int NewJet = 0;

        for (unsigned j = 0; j < GranulatedJets.size(); ++j) {

            const float CellDiffRap = std::abs(EFlowJets[i].pseudorapidity() - GranulatedJets[j].pseudorapidity()) / CellDeltaRap;
            float CellDiffPhi = std::abs(EFlowJets[i].phi() - GranulatedJets[j].phi());
            if (CellDiffPhi > Pi) CellDiffPhi = TwoPi - CellDiffPhi;
            CellDiffPhi = CellDiffPhi / CellDeltaPhi;

            if (CellDiffRap < 1 && CellDiffPhi < 1) {

                NewJet = 1;

                const float TotalEnergy  = EFlowJets[i].e() + GranulatedJets[j].e();
                const float RescaleFactor = sqrt(pow(EFlowJets[i].px() + GranulatedJets[j].px(), 2) + pow(EFlowJets[i].py() + GranulatedJets[j].py(), 2) + pow(EFlowJets[i].pz() + GranulatedJets[j].pz(), 2));
                const float RescaledPx = TotalEnergy * (EFlowJets[i].px() + GranulatedJets[j].px()) / RescaleFactor;
                const float RescaledPy = TotalEnergy * (EFlowJets[i].py() + GranulatedJets[j].py()) / RescaleFactor;
                const float RescaledPz = TotalEnergy * (EFlowJets[i].pz() + GranulatedJets[j].pz()) / RescaleFactor;

                fastjet::PseudoJet CombinedJet(RescaledPx, RescaledPy, RescaledPz, TotalEnergy);

                CombinedJet.set_user_index(EFlowJets[i].user_index() + GranulatedJets[j].user_index());

                GranulatedJets.erase(GranulatedJets.begin() + j);
                GranulatedJets.push_back(CombinedJet);
                break;

            }
        }

        if (NewJet != 1) {
            GranulatedJets.push_back(EFlowJets[i]);
            GranulatedJets = sorted_by_pt(GranulatedJets);
        }
    }


    for (unsigned ii = 0; ii < GranulatedJets.size(); ++ii) {

        if ((GranulatedJets[ii].perp() < PtCutOff)) {
            GranulatedJets.erase(GranulatedJets.begin() + ii);
            --ii;
        }
    }

    return GranulatedJets;

}
