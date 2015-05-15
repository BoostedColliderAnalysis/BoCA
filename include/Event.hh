# pragma once

# include "HObject.hh"
# include "HParticle.hh"
# include "HLepton.hh"
# include "HJet.hh"
# include "TopHadronicHep.hh"
# include "HHiggsTagger.hh"
# include "HDiscriminator.hh"
# include "HJetTag.hh"

/**
 * @brief Base class for the event Topology
 *
 */
class hanalysis::Event : public HObject
{

public:

    Event(const ClonesArrays::Source source);

    ~Event();

    void Newevent(const ClonesArrays &);

    HJet &Hadrons() const {
        return *hadrons_;
    }

    HLepton &Leptons() const {
        return *leptons_;
    }

    HParticle &Partons() const {
        return *partons_;
    }

    float mass() const {
        return mass_;
    }

    void SetMass(const float mass) {
        mass_ = mass;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Event";
    }

    /**
     * @brief Particles
     *
     */
    HParticle *partons_ = NULL;

    /**
     * @brief Leptons
     *
     */
    HLepton *leptons_ = NULL;

    /**
     * @brief Jets
     *
     */
    HJet *hadrons_ = NULL;

private:

  ClonesArrays::Source source_;

    float mass_;

};
