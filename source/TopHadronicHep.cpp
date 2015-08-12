#include "TopHadronicHep.hh"

#include "fastjet/ClusterSequence.hh"
#include "HEPTopTagger.hh"
#include "Debug.hh"

namespace analysis {

Jets TopHadronicHep::Tops(Jets& e_flows)
{
    Info();
//     float CellRap = 0.1;
//     Jets hadrons;
//     ifstream fin("sample_event.dat", ifstream::in);
//     Readevent(fin, hadrons);
//     ofstream fout("sample_event_display.dat", ifstream::out);
//     ofstream fout2("sample_event_out.dat", ifstream::out);
//     output_vec_pseudojet(fout2, hadrons);
    //  jet definition
    float cone_size = 1.5;
    // run the jet finding; find the hardest jet
    const fastjet::ClusterSequence cluster_sequence(GranulatedJets(e_flows), fastjet::JetDefinition(fastjet::cambridge_algorithm, cone_size));
    float pt_min = 200.;
    Jets jets = sorted_by_pt(cluster_sequence.inclusive_jets(pt_min));
//     unsigned candsizesum = 0;
    Jets tops;
    for (auto const& jet : jets) {
//         float topmass = 172.3;
//         float wmass = 80.4;
//         HEPTopTagger TopTagger(ClusterSequence, Jet, topmass, wmass);
        HEPTopTagger top_tagger(cluster_sequence, jet);
        top_tagger.set_top_range(150., 200.);
        std::cout << "========= Top Tagger ============" << std::endl;
        top_tagger.run_tagger();
//         cout << "-------- setting  --------" << endl;
//         TopTagger.get_setting();
//         cout << "-------- resutls  --------" << endl;
//         TopTagger.get_info();
//         if (TopTagger.is_masscut_passed())
        {
            std::cout << "###masscut_passed ###" << std::endl;
            fastjet::PseudoJet top = top_tagger.top_candidate();
//             fastjet::PseudoJet b = TopTagger.top_subjets().at(0);
//             fastjet::PseudoJet W1 = TopTagger.top_subjets().at(1);
//             fastjet::PseudoJet W2 = TopTagger.top_subjets().at(2);
//             std::cout << "top mass: " << top.m() << std::endl;
//             cout << "bottom mass: " << b.m() << endl;
//             cout << "W mass: " << (W1 + W2).m() << endl;
            tops.emplace_back(top);
        }
    }
    return tops;
}

Jets TopHadronicHep::GranulatedJets(Jets& e_flows)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    float CellDeltaRap = 0.1;
    float CellDeltaPhi = 0.1;
    float PtCutOff = 0.5;
//     float pi = 3.142592654;
    Jets granulated_jets;
    granulated_jets.clear();
    e_flows = sorted_by_pt(e_flows);
    granulated_jets.emplace_back(e_flows[0]);
    for (size_t i = 1; i < e_flows.size(); ++i) {
        int jet = 0;
        for (unsigned j = 0; j < granulated_jets.size(); ++j) {
            float CellDiffRap = std::abs(e_flows[i].pseudorapidity() - granulated_jets[j].pseudorapidity()) / CellDeltaRap;
            float CellDiffPhi = std::abs(e_flows[i].phi() - granulated_jets[j].phi());
            if (CellDiffPhi > M_PI)
                CellDiffPhi = 2 * M_PI - CellDiffPhi;
            CellDiffPhi = CellDiffPhi / CellDeltaPhi;
            if (CellDiffRap < 1 && CellDiffPhi < 1) {
                jet = 1;
                float TotalEnergy  = e_flows[i].e() + granulated_jets[j].e();
                float RescaleFactor = sqrt(pow(e_flows[i].px() + granulated_jets[j].px(), 2) + pow(e_flows[i].py() + granulated_jets[j].py(), 2) + pow(e_flows[i].pz() + granulated_jets[j].pz(), 2));
                float RescaledPx = TotalEnergy * (e_flows[i].px() + granulated_jets[j].px()) / RescaleFactor;
                float RescaledPy = TotalEnergy * (e_flows[i].py() + granulated_jets[j].py()) / RescaleFactor;
                float RescaledPz = TotalEnergy * (e_flows[i].pz() + granulated_jets[j].pz()) / RescaleFactor;
                fastjet::PseudoJet CombinedJet(RescaledPx, RescaledPy, RescaledPz, TotalEnergy);
                CombinedJet.set_user_index(e_flows[i].user_index() + granulated_jets[j].user_index());
                granulated_jets.erase(granulated_jets.begin() + j);
                granulated_jets.emplace_back(CombinedJet);
                break;
            }
        }
        if (jet != 1) {
            granulated_jets.emplace_back(e_flows[i]);
            granulated_jets = sorted_by_pt(granulated_jets);
        }
    }
    for (unsigned ii = 0; ii < granulated_jets.size(); ++ii) {
        if ((granulated_jets[ii].perp() < PtCutOff)) {
            granulated_jets.erase(granulated_jets.begin() + ii);
            --ii;
        }
    }
    return granulated_jets;
}

}
