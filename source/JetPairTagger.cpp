#include "JetPairTagger.hh"
#include "Event.hh"
#include "Sort.hh"
#include "Debug.hh"

namespace analysis
{

JetPairTagger::JetPairTagger()
{
    Info();
    DefineVariables();
}

int JetPairTagger::Train(const Event &event, const PreCuts &, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    if (jets.size() < 2) return 0;
    if (jets.empty()) return 0;
    Debug(jets.size());
    Jets bottoms = PairBottomQuarks(event, tag);
    Jets higgs = HiggsParticle(event, tag);
    Jets bottom_jets;
    Jets bad_bottom_jets;
    switch (tag) {
    case Tag::signal :
        if (bottoms.size() == 2) {
            for (const auto & bottom : bottoms) {
                jets = SortedByMinDeltaRTo(jets, bottom);
                if (Close(jets.at(1))(bottom))continue;
                if (Close(jets.at(0))(bottom))bottom_jets.emplace_back(jets.front());
            }
        } else Error(bottoms.size());
        break;
    case Tag::background :
        bottom_jets = jets;
        break;
    }

    std::vector<Doublet> doublets;
    for (auto jet1 = bottom_jets.begin(); jet1 != bottom_jets.end(); ++jet1)
        for (auto jet2 = jet1 + 1; jet2 != bottom_jets.end(); ++jet2) {
            Doublet doublet;
            if (std::abs((*jet1).rap()) > std::abs((*jet2).rap())) doublet.SetMultiplets(*jet1, *jet2);
            else doublet.SetMultiplets(*jet2, *jet1);

            if (bottoms.size() == 2 && higgs.size() > 0 && tag == Tag::background) {
                if (CheckIfBadBottom(doublet, bottoms)) continue;
            }

            if (doublet.Overlap())continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
        
//     static int notusefulbottom = 0;
//     if (bottoms.size() == 2 && (bottoms.at(0).pt() < 50 || bottoms.at(1).pt() < 50)) {
//         notusefulbottom++;
//     }
// 
//     static int lessthantwo = 0;
//     if (tag == Tag::signal && bottom_jets.size() < 2) {
//         ++lessthantwo;
//     }
//     static int zerodoublet=0;
//     if(tag==Tag::signal&&doublets.size()==0){
//       zerodoublet++;
//     }

    if (tag == Tag::signal && doublets.size() > 1) {
        doublets = SortedByMaxDeltaRap(doublets);
        if (doublets.size() > 1) doublets.erase(doublets.begin() + 1, doublets.end());  //FIXME  sorted by what?
    }
//     static int doubletsize=0;
//     if(tag==Tag::signal&&doublets.size()!=0){
//       doubletsize++;
//       Error(notusefulbottom, lessthantwo, zerodoublet, doubletsize);
//     }
    return SaveEntries(doublets);
}

Jets JetPairTagger::PairBottomQuarks(const Event &event, Tag tag) const
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets bottom_not_from_even = RemoveIfGrandFamily(particles, Id::bottom, Id::heavy_higgs);
    Jets bottom_not_from_higgs = RemoveIfGrandFamily(bottom_not_from_even, Id::bottom, Id::CP_odd_higgs);
    return bottom_not_from_higgs;
}

std::vector<Doublet> JetPairTagger::Multiplets(const Event &event, const analysis::PreCuts &, const TMVA::Reader &reader) const
{
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet>  doublets;
    for (auto jet_1 = jets.begin(); jet_1 != jets.end(); ++jet_1)
        for (auto jet_2 = jet_1 + 1; jet_2 != jets.end(); ++jet_2) {
            Doublet doublet;
            if (std::abs((*jet_1).rap()) > std::abs((*jet_2).rap()))
                doublet.SetMultiplets(*jet_1, *jet_2);
            else
                doublet.SetMultiplets(*jet_2, *jet_1);
            if (doublet.Overlap())continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    return ReduceResult(doublets, 6);
}

bool JetPairTagger::CheckIfBadBottom(const analysis::Doublet &doublet, const Jets &jets)const
{
    if ((Close(jets.at(0))(doublet.Singlet1().Jet()) && Close(jets.at(1))(doublet.Singlet2().Jet())) || (Close(jets.at(1))(doublet.Singlet1().Jet()) && Close(jets.at(0))(doublet.Singlet2().Jet())))return true;
    else return false;

}

Jets JetPairTagger::HiggsParticle(const Event &event, Tag tag) const
{
    if (tag == Tag::background) return Jets {};
    Jets particles = event.Partons().GenParticles();
    Jets even = CopyIfFamily(particles, Id::heavy_higgs, Id::gluon);
    Jets odd = CopyIfFamily(particles, Id::CP_odd_higgs, Id::gluon);
    return Join(even, odd);
}


}
