# include "HTopTagger.hh"

Analysis::HTopTagger::HTopTagger()
{


    Print(1, "Constructor");

}

Analysis::HTopTagger::~HTopTagger()
{

    Print(1, "Destructor");

}

vector<PseudoJet> Analysis::HTopTagger::GetTops(vector< PseudoJet > EFlowJets)
{

    Print(2, "Tagging Top");

//     float CellEta = 0.1;
//     vector<PseudoJet> hadrons;

//     ifstream fin("sample_event.dat", ifstream::in);
//     ReadEvent(fin, hadrons);
//     ofstream fout("sample_event_display.dat", ifstream::out);
//     ofstream fout2("sample_event_out.dat", ifstream::out);
//     output_vec_pseudojet(fout2, hadrons);

    //  jet definition
    const float ConeSize = 1.5;
    const fastjet::JetDefinition JetDefinition(fastjet::cambridge_algorithm, ConeSize);

    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaEta = 0.1;
    const float CellDeltaPhi = 0.1;
    const float PtCutOff = 0.5;
    vector<PseudoJet> GranulatedJets = GetGranulatedJets(EFlowJets, CellDeltaEta, CellDeltaPhi, PtCutOff);

    // run the jet finding; find the hardest jet
    const fastjet::ClusterSequence ClusterSequence(GranulatedJets, JetDefinition);
    const float PtMin = 200.;
    vector<PseudoJet> Jets = sorted_by_pt(ClusterSequence.inclusive_jets(PtMin));

//     unsigned candsizesum = 0;

    vector<PseudoJet> TopJets;

    for (const auto & Jet : Jets) {

        const float topmass = 172.3;
        const float wmass = 80.4;
        HEPTopTagger TopTagger(ClusterSequence, Jet, topmass, wmass);

        TopTagger.set_top_range(150., 200.);
        cout << "========= Top Tagger ============" << endl;
        TopTagger.run_tagger();
//         cout << "-------- setting  --------" << endl;
//         TopTagger.get_setting();
//         cout << "-------- resutls  --------" << endl;
//         TopTagger.get_info();

        if (TopTagger.is_masscut_passed()) {

            cout << "### masscut_passed ###" << endl;

            PseudoJet top = TopTagger.top_candidate();
//             PseudoJet b = TopTagger.top_subjets().at(0);
//             PseudoJet W1 = TopTagger.top_subjets().at(1);
//             PseudoJet W2 = TopTagger.top_subjets().at(2);
            cout << "top mass: " << top.m() << endl;
//             cout << "bottom mass: " << b.m() << endl;
//             cout << "W mass: " << (W1 + W2).m() << endl;

            TopJets.push_back(top);

        }

    }

    return TopJets;

}

vector<PseudoJet> Analysis::HTopTagger::GetGranulatedJets(vector<PseudoJet> &EFlowJets,const float &CellDeltaEta, const float &CellDeltaPhi, const float &PtCutOff)
{

    float pi = 3.142592654;
    vector<PseudoJet> GranulatedJets;
    GranulatedJets.clear();

    EFlowJets = sorted_by_pt(EFlowJets);
    GranulatedJets.push_back(EFlowJets[0]);
    for (unsigned i = 1; i < EFlowJets.size(); i++) {
        int new_jet = 0;
        for (unsigned j = 0; j < GranulatedJets.size(); j++) {
            float eta_cell_diff = abs(EFlowJets[i].pseudorapidity() -
                                       GranulatedJets[j].pseudorapidity()) / CellDeltaEta;
            float phi_cell_diff = abs(EFlowJets[i].phi() -
                                       GranulatedJets[j].phi());
            if (phi_cell_diff > pi)     phi_cell_diff = 2 * pi - phi_cell_diff;
            phi_cell_diff = phi_cell_diff / CellDeltaPhi;

            if (eta_cell_diff < 1 && phi_cell_diff < 1) {
                new_jet = 1;

                float total_energy  = EFlowJets[i].e() + GranulatedJets[j].e();
                float rescale_factor = sqrt(pow(EFlowJets[i].px() + GranulatedJets[j].px(), 2) +
                                             pow(EFlowJets[i].py() + GranulatedJets[j].py(), 2) +
                                             pow(EFlowJets[i].pz() + GranulatedJets[j].pz(), 2));
                float rescaled_px = total_energy * (EFlowJets[i].px() + GranulatedJets[j].px()) / rescale_factor ;
                float rescaled_py = total_energy * (EFlowJets[i].py() + GranulatedJets[j].py()) / rescale_factor ;
                float rescaled_pz = total_energy * (EFlowJets[i].pz() + GranulatedJets[j].pz()) / rescale_factor ;

                PseudoJet comb_jet(rescaled_px, rescaled_py, rescaled_pz, total_energy);

                comb_jet.set_user_index(EFlowJets[i].user_index() + GranulatedJets[j].user_index());

                GranulatedJets.erase(GranulatedJets.begin() + j);
                GranulatedJets.push_back(comb_jet);
                break;
            }
        }
        if (new_jet != 1) {
            GranulatedJets.push_back(EFlowJets[i]);
            GranulatedJets = sorted_by_pt(GranulatedJets);
        }
    }


    for (unsigned ii = 0; ii < GranulatedJets.size(); ii++) {

        if ((GranulatedJets[ii].perp() < PtCutOff)) {
            GranulatedJets.erase(GranulatedJets.begin() + ii);
            ii--;
        }
    }

    return (GranulatedJets);

}
