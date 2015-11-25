#include "Event.hh"
#include "delphes/Partons.hh"
#include "delphes/Leptons.hh"
#include "delphes/Hadrons.hh"
#include "exroot/Leptons.hh"
#include "exroot/Hadrons.hh"
#include "exroot/Partons.hh"
#include "Vector.hh"
// #define INFORMATION
#include "Debug.hh"

namespace analysis
{

Event::Event() : isolation_(*this)
{
    Info();
}

Event::Event(const Source source) : isolation_(*this)
{
    Info();
    source_ = source;
    switch (source_) {
    case Source::delphes :
        partons_ = new delphes::Partons();
        hadrons_ = new delphes::Hadrons();
        leptons_ = new delphes::Leptons();
        break;
    case Source::pgs :
        leptons_ = new exroot::Leptons();
        hadrons_ = new exroot::Hadrons();
        break;
    case Source::parton :
        partons_ = new exroot::Partons();
        break;
    }
}

Event::~Event()
{
    Info();
    switch (source_) {
    case Source::delphes :
        delete partons_;
        delete leptons_;
        delete hadrons_;
        break;
    case Source::pgs :
        delete leptons_;
        delete hadrons_;
        break;
    case Source::parton:
        delete partons_;
        break;
    }
}

void Event::NewEvent(const ClonesArrays &clones_arrays)
{
    Info();
    switch (source_) {
    case Source::delphes :
        partons_->NewEvent(clones_arrays);
        hadrons_->NewEvent(clones_arrays);
        leptons_->NewEvent(clones_arrays);
        break;
    case Source::pgs :
        hadrons_->NewEvent(clones_arrays);
        leptons_->NewEvent(clones_arrays);
        break;
    case Source::parton:
        partons_->NewEvent(clones_arrays);
        break;
    }
}

Jets Event::IsolatedLeptons()
{
    Info();
    Jets leptons;
    for (auto const & lepton : leptons_->leptons()) {
      if(lepton.pt() > DetectorGeometry::HardLeptonMomentum()){
        leptons.emplace_back(lepton);
        continue;
      }
        bool isolated = true;
        for (auto const & jet : hadrons_->Jets()) 
          if (Close(lepton)(jet, DetectorGeometry::IsolationConeSize()) && jet.pt() / lepton.pt() > DetectorGeometry::IsolationFraction()) {          
                isolated = false;
                break;
            }
        if (isolated) leptons.emplace_back(lepton);
    }
    return leptons;
}

analysis::Partons const &Event:: Partons() const
{
    Info();
    return *partons_;
}

analysis::Hadrons const &Event::Hadrons() const
{
    Info();
    return *hadrons_;
}

analysis::Leptons const &Event::Leptons() const
{
    Info(Name(DetectorGeometry::detector_type()));
    switch (DetectorGeometry::detector_type()) {
    case DetectorType::CMS :
        Info("CMS");
//       return *leptons_;
        return isolation_;
    case DetectorType::Spp :
        Info("Spp");
//         return *leptons_;
        return isolation_;
    }
}

void Event::SetMass(float mass)
{
    Info();
    mass_ = mass;
}

float Event::mass() const
{
    Info();
    return mass_;
}

}
