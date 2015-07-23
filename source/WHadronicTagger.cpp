#include "WHadronicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

WHadronicTagger::WHadronicTagger()
{
    Note();
    DefineVariables();
}

int WHadronicTagger::Train(const Event& event, const analysis::PreCuts& pre_cuts, const analysis::Tag Tag) const
{
    Info("W Tags");
    Jets jets = bottom_reader_.Multiplets(event);
    Info("Bottom Tagger Number", jets.size());
    std::vector<Doublet> doublets;
    Info("2 jets form one W");
    for (auto jet1 = jets.begin(); jet1 != jets.end(); ++jet1) {
        for (auto jet2 = jet1 + 1; jet2 != jets.end(); ++jet2) {
            Doublet doublet(*jet1, *jet2);
            if (Problematic(doublet, pre_cuts, Tag))
                continue;
            doublets.emplace_back(doublet);
        }
    }
    Info("2 of 2 sub jets form one W");
    for (const auto& jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number)
            continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts, Tag))
            continue;
        doublets.emplace_back(doublet);
    }
    Info("2 of 3 sub jets forms one W");
    for (const auto& jet : jets) {
        const int sub_jet_number = 3;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number)
            continue;
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            for (auto piece2 = piece1 + 1; piece2 != pieces.end(); ++piece2) {
                Doublet doublet(*piece1, *piece2);
                if (Problematic(doublet, pre_cuts, Tag))
                    continue;
                doublets.emplace_back(doublet);
            }
        }
    }
    // FIXME this one seems to cause problems!!!
    Info("1 of 2 sub jets forms one W");
    for (const auto& jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number)
            continue;
        for (const auto& piece : pieces) {
            Doublet doublet(piece);
            if (Problematic(doublet, pre_cuts, Tag))
                continue;
            doublets.emplace_back(doublet);
        }
    }
    Info("1 jet forms one W");
    for (const auto& jet : jets) {
        Doublet doublet(jet);
        if (Problematic(doublet, pre_cuts, Tag))
            continue;
        doublets.emplace_back(doublet);
    }
    int w_hadronic_id = WHadronicId(event);
    Jets particles = event.Partons().Particles();
    Jets w_particles;
    if (w_hadronic_id != 0)
        w_particles = CopyIfExactParticle(particles, w_hadronic_id);
    else
        w_particles = CopyIfParticle(particles, Id::W);
    w_particles = RemoveIfSoft(w_particles, DetectorGeometry::JetMinPt());
    return SaveEntries(BestMatches(doublets, w_particles, Tag));
}


Jets WHadronicTagger::WDaughters(const analysis::Event& event) const
{
    Jets w_daughters = event.Partons().GenParticles();
    w_daughters = CopyIfMother(w_daughters, Id::W);
    Info(w_daughters.size());
    w_daughters = CopyIfQuark(w_daughters);
    Info(w_daughters.size());
    return w_daughters;
}

int WHadronicTagger::WHadronicId(const Jets& jets) const
{
    if (jets.empty())
        return 0;
    int sign;
    bool first = true;
    bool just_one = true;
    for (const auto jet : jets) {
        int id = jet.user_info<JetInfo>().constituents().front().family().mother_1().id();
        if (first)
            sign = sgn(id);
        else if (sign != sgn(id))
            just_one = false;
        first = false;
    }
    if (just_one)
        return sign * to_int(Id::W);
    return 0;
}

bool WHadronicTagger::Problematic(const Doublet& doublet, const PreCuts& pre_cuts, const Tag tag) const
{
    if (Problematic(doublet, pre_cuts))
        return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(doublet.Jet().m() - Mass(Id::W)) > w_mass_window_)
            return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0)
            return true;
        if (doublet.Singlet1().Bdt() > 1)
            return true;
        if (doublet.Singlet2().Bdt() > 1)
            return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool WHadronicTagger::Problematic(const Doublet& doublet, const PreCuts& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::W) > 0 && pre_cuts.PtLowerCut(Id::W) > doublet.Jet().pt())
        return true;
    if (pre_cuts.PtUpperCut(Id::W) > 0 && pre_cuts.PtUpperCut(Id::W) < doublet.Jet().pt())
        return true;
    if (pre_cuts.MassUpperCut(Id::W) > 0 && pre_cuts.MassUpperCut(Id::W) < doublet.Jet().m())
        return true;
    if (doublet.DeltaR() < DetectorGeometry::MinCellResolution() && doublet.DeltaR() > 0)
        return true;
    return false;
}

std::vector<Doublet> WHadronicTagger::Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets;
    Info("2 jets form one W");
    doublets = Join(doublets, Multiplets(jets, pre_cuts, reader));
    Info("2 of 2 sub jets form one W");
    doublets = Join(doublets, SubMultiplets(jets, pre_cuts, reader, 2));
    Info("2 of 3 sub jets forms one W");
    doublets = Join(doublets, SubMultiplets(jets, pre_cuts, reader, 3));
    Info("1 of 2 sub jets form one W");
    doublets = Join(doublets, SubMultiplets2(jets, pre_cuts, reader));
    Info("1 jets form one W");
    doublets = Join(doublets, Multiplets3(jets, pre_cuts, reader));
    return ReduceResult(doublets);
}

std::vector<Doublet> WHadronicTagger::Multiplets(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1) {
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            try {
                doublets.emplace_back(Multiplet(*Jet1, *Jet2, pre_cuts, reader));
            } catch (const char* message) {
                continue;
            }
        }
    }
    return doublets;
}

std::vector<Doublet> WHadronicTagger::Multiplets3(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1) {
        try {
            doublets.emplace_back(Multiplet(*Jet1, pre_cuts, reader));
        } catch (const char* message) {
            continue;
        }
    }
    return doublets;
}

std::vector<Doublet> WHadronicTagger::SubMultiplets(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader, const std::size_t sub_jet_number) const
{
    Info();
    std::vector<Doublet>  doublets;
    for (const auto& jet : jets) {
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number)
            continue;
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            for (auto piece2 = piece1 + 1; piece2 != pieces.end(); ++piece2) {
                try {
                    doublets.emplace_back(Multiplet(*piece1, *piece2, pre_cuts, reader));
                }  catch (const char* message) {
                    continue;
                }
            }
        }
    }
    return doublets;
}

std::vector<Doublet> WHadronicTagger::SubMultiplets2(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    int sub_jet_number = 2;
    std::vector<Doublet>  doublets;
    for (const auto& jet : jets) {
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            try {
                doublets.emplace_back(Multiplet(*piece1, pre_cuts, reader));
            }  catch (const char* message) {
                continue;
            }
        }
    }
    return doublets;
}

Doublet WHadronicTagger::SubMultiplet(const fastjet::PseudoJet& jet, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
    Doublet doublet;
    if (pieces.empty())
        return doublet;
    if (pieces.size() == 1)
        doublet.SetJet(jet);
    else
        doublet.SetMultiplets(pieces.at(0), pieces.at(1));
    try {
        return Multiplet(doublet, pre_cuts, reader);
    } catch (const char* message) {
        throw message;
    }
}

Doublet WHadronicTagger::Multiplet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    Doublet doublet(jet_1, jet_2);
    try {
        return Multiplet(doublet, pre_cuts, reader);
    } catch (const char* message) {
        throw message;
    }
}

Doublet WHadronicTagger::Multiplet(const fastjet::PseudoJet& jet, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    Doublet doublet(jet);
    try {
        return Multiplet(doublet, pre_cuts, reader);
    } catch (const char* message) {
        throw message;
    }
}

Doublet WHadronicTagger::Multiplet(Doublet& doublet, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    if (Problematic(doublet, pre_cuts))
        throw "W hadronic doublet problem";
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

Doublet WHadronicTagger::Multiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const
{
    PreCuts pre_cuts;
    try {
        return Multiplet(jet, pre_cuts, reader);
    } catch (const char* message) {
        throw message;
    }
}

int WHadronicTagger::WHadronicId(const analysis::Event& event) const
{
    return WHadronicId(WDaughters(event));
}

Doublet WHadronicTagger::SubMultiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const
{
    PreCuts pre_cuts;
    try {
        return SubMultiplet(jet, pre_cuts, reader);
    } catch (const char* message) {
        throw message;
    }
}

Doublet WHadronicTagger::Multiplet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, const TMVA::Reader& reader) const
{
    PreCuts pre_cuts;
    try {
        return Multiplet(jet_1, jet_2, pre_cuts, reader);
    } catch (const char* message) {
        throw message;
    }
}

int WHadronicTagger::GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
}

}
