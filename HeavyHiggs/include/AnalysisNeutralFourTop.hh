#pragma once

#include "AnalysisHeavyHiggs.hh"

#include "JetPairTagger.hh"
#include "Doublet.hh"
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

template<typename Tagger>
class AnalysisNeutralFourTop : public AnalysisHeavyHiggs<Tagger>
{

public:

    AnalysisNeutralFourTop() {
        DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::Htt);
            this->NewFile(tag, Process::Htwb);
            break;
        case Tag::background :
            if (this->template TaggerIs<JetPairTagger>()) this->NewFile(tag, Process::Htt);
            if (this->template TaggerIs<JetPairTagger>()) this->NewFile(tag, Process::Htwb);
            this->NewFile(tag, Process::ttwwbb);
            this->NewFile(tag, Process::ttwbb);
            break;
        }
    }

    std::string AnalysisName() const final {
        return  "NeutralFourTop-" + Name(this->collider_type()) + "-" + boca::Name(this->Mass()) + "-4b";
    }

    boca::Crosssection Crosssection(Process process) const {
        switch (this->collider_type()) {
        case Collider::LHC:
            switch (process) {
            case Process::Htt:
                switch (Int(this->Mass())) {
                case 500 : return 0.911648 * fb;
                case 700 : return 0.346647 * fb;
                case 800 : return 0.225386 * fb;
                case 1000 : return 0.10028 * fb;
                case 1500 : return 0.0168305 * fb;
                case 2000 : return 0.00345315 * fb;
                    Default("Mass", fb)
                }
            case Process::Htwb:
                switch (Int(this->Mass())) {
                case 500 : return 0.471031 * fb;
                case 700 : return 0.216664 * fb;
                case 800 : return 0.150792 * fb;
                case 1000 : return 0.0758434 * fb;
                case 1500 : return 0.0159789 * fb;
                case 2000 : return 0.00384621 * fb;
                    Default("Mass", fb)
                }
            case Process::ttwwbb : return 2.126 * fb;
            case Process::ttwbb : return  0.13588 * fb;
                Default("Process", fb)
            };
        case Collider::FHC:
        case Collider::LE:
            switch (process) {
            case Process::Htt:
                switch (Int(this->Mass())) {
                case 500 : return 152.154 * fb;
                case 700 : return 79.3982 * fb;
                case 800 : return 60.9656 * fb;
                case 1000 : return 36.5579 * fb;
                case 1500 : return 12.4039 * fb;
                case 2000 : return 5.09533 * fb;
                case 3000 : return 1.21763 * fb;
                case 4000 : return 0.385975 * fb;
                case 5000 : return 0.14659 * fb;
                case 6000 : return 0.062513 * fb;
                case 7000 : return 0.026579 * fb;
                case 8000 : return 0.0132781 * fb;
                case 10000 : return 0.00380676 * fb;
                    Default("Mass", fb)
                }
            case Process::Htwb:
                switch (Int(this->Mass())) {
                case 500 : return 117.041 * fb;
                case 700 : return 79.5743 * fb;
                case 800 : return 66.4861 * fb;
                case 1000 : return 47.8374 * fb;
                case 1500 : return 23.1449 * fb;
                case 2000 : return 12.5153 * fb;
                case 3000 : return 4.60995 * fb;
                case 4000 : return 2.01434 * fb;
                case 5000 : return 0.975944 * fb;
                case 6000 : return 0.509747 * fb;
                case 7000 : return 0.256938 * fb;
                case 8000 : return 0.148312 * fb;
                case 10000 : return 0.0539546 * fb;
                    Default("Mass", fb)
                }
            case Process::ttwwbb : return 396. * fb;
            case Process::ttwbb : return 1.3204 * fb;
                Default("Process", fb)
            }
            Default("Collider", fb)
        }
    }

private:

    int PassPreCut(Event const&, Tag) const override {
//         std::vector<Particle> Particles = event.Partons().GenParticles();
//
//         std::vector<Particle> Tops = CopyIfParticle(Particles, Id::top);
//         std::vector<Particle> Bottoms = CopyIfParticle(Particles, Id::bottom);
//
//         if (event.Hadrons().MissingEt().Pt() < this->MissingEt()) return 0;
//         std::vector<Jet> Leptons = SortedByPt(event.Leptons().leptons());
//         if (Leptons.size() < 2) return 0;
//         int positive_lepton = 0;
//         int negative_lepton = 0;
//         for (auto const & lepton : Leptons) {
//             if (lepton.Pt() > this->LeptonPt() && lepton.Info().Charge() > 0) ++positive_lepton;
//             if (lepton.Pt() > this->LeptonPt() && lepton.Info().Charge() < 0) ++negative_lepton;
//         }
//
//         if (positive_lepton < 2 && negative_lepton < 2) return 0;
//         if ((positive_lepton + negative_lepton) > 2) return 0;
//
//         std::vector<Jet> jets = event.Hadrons().Jets();
//         if (jets.size() < 4) return 0;
        return 1;
    }

};

}

}
