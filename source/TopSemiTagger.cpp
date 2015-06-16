# include "TopSemiTagger.hh"

namespace analysis {

TopSemiTagger::TopSemiTagger()
{
    //     DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (Mass(TopId) - Mass(WId)) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

int TopSemiTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Top Tags");

    Jets top_particles = event.Partons().GenParticles();
    top_particles = copy_if_particle(top_particles, TopSemiId(event));

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    Jets leptons = event.Leptons().leptons();
    Print(kInformation, "Lepton Number", leptons.size());

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, jet);
                triplet.SetTag(tag);
                std::vector<Triplet> pre_triplets = CleanTriplets(triplet,top_particles,pre_cuts,tag);
                if(!pre_triplets.empty()) triplets.emplace_back(pre_triplets.front());
            }
        }
    } else {
        for (const auto & jet : jets) {
            for (const auto & lepton : leptons) {
                Doublet doublet(lepton);
                Triplet triplet(doublet, jet);
                triplet.SetTag(tag);
                std::vector<Triplet> pre_triplets = CleanTriplets(triplet,top_particles,pre_cuts,tag);
                if(!pre_triplets.empty()) triplets.emplace_back(pre_triplets.front());
            }
        }
    }

    if (tag == kSignal && triplets.size() > top_particles.size()) {
        triplets = SortedByMassTo(triplets, Mass(TopId));
        triplets.erase(triplets.begin() + top_particles.size(), triplets.end());
    }
    Print(kInformation, "Number triplets", triplets.size());

    return SaveEntries(triplets);
}

std::vector<Triplet> TopSemiTagger::CleanTriplets(const Triplet &triplet, Jets TopQuarks, PreCuts &pre_cuts, const Tag tag) {
    std::vector<Triplet> triplets;
    for(const auto particle : TopQuarks) Join(triplets,CleanTriplet(triplet,particle,pre_cuts,tag));
    return triplets;
}

std::vector<Triplet> TopSemiTagger::CleanTriplet(const Triplet &triplet, fastjet::PseudoJet TopQuark, PreCuts& pre_cuts, const Tag tag) {
    std::vector<Triplet> triplets;
    if (tag == kSignal && std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) return triplets ; // should be enabled again
    if (tag == kSignal && triplet.Jet().pt() <  pre_cuts.PtLowerCut(TopId)) return triplets;
    if (tag == kSignal && triplet.Jet().pt() >  pre_cuts.PtUpperCut(TopId)) return triplets;
    if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) return triplets;
    if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) return triplets;
    triplets.push_back(triplet);
    return triplets;
}

std::vector<Triplet>  TopSemiTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    std::vector<Doublet> doublets = w_semi_reader_.Multiplets<WSemiTagger>(event);

    std::vector<Triplet> triplets;
    if (!boost_) {
        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (std::abs(triplet.Jet().m() - Mass(TopId)) > top_mass_window_) continue;
                triplet.SetBdt(Bdt(triplet,reader));
                triplets.emplace_back(triplet);
            }
        }
    } else {
        for (const auto & Jet : jets) {
            for (const auto & Predoublet : doublets) {
                Doublet doublet(Predoublet.SingletJet1());
                Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - Mass(TopId)) > TopWindow) continue; // reactivate this check
                triplet.SetBdt(Bdt(triplet,reader));
                triplets.emplace_back(triplet);
            }
        }
    }
    return ReduceResult(triplets);
}

}
