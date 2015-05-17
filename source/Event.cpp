# include "Event.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"
# include "HJetDelphes.hh"
# include "HLeptonPgs.hh"
# include "HJetPgs.hh"
# include "HParticleParton.hh"


analysis::Event::Event(const ClonesArrays::Source source)
{
    Print(kNotification, "Constructor");
    source_ = source;
    switch (source_) {
    case ClonesArrays::kDelphes :
        partons_ = new hdelphes::HParticle();
        hadrons_ = new hdelphes::HJet();
        leptons_ = new hdelphes::HLepton();
        break;
    case ClonesArrays::kPgs :
        leptons_ = new hpgs::HLepton();
        hadrons_ = new hpgs::HJet();
        break;
    case ClonesArrays::kParton :
        partons_ = new hparton::HParticle();
        break;
    }
}

analysis::Event::~Event()
{
    Print(kNotification, "Destructor");
    switch (source_) {
    case ClonesArrays::kDelphes :
        delete partons_;
        delete leptons_;
        delete hadrons_;
        break;
    case ClonesArrays::kPgs :
        delete leptons_;
        delete hadrons_;
        break;
    case ClonesArrays::kParton:
        delete partons_;
        break;
    }
}

void analysis::Event::Newevent(const analysis::ClonesArrays &ClonesArrays)
{
    Print(kInformation, "New event");
    switch (source_) {
    case ClonesArrays::kDelphes :
        partons_->Newevent(ClonesArrays);
        hadrons_->Newevent(ClonesArrays);
        leptons_->Newevent(ClonesArrays);
        break;
    case ClonesArrays::kPgs :
        hadrons_->Newevent(ClonesArrays);
        leptons_->Newevent(ClonesArrays);
        break;
    case ClonesArrays::kParton:
        partons_->Newevent(ClonesArrays);
        break;
    }
}
