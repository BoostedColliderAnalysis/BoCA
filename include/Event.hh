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

    /**
    * @brief constructor
    *
    */
    Event();

    virtual void Newevent(const ClonesArrays &) = 0;

    HJet &Hadrons() const {
        return *jets;
    }

    HLepton &Leptons() const {
        return *Lepton;
    }

    HParticle &Partons() const {
        return *Particles;
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
    };

    /**
     * @brief Particles
     *
     */
    HParticle *Particles;

    /**
     * @brief Leptons
     *
     */
    HLepton *Lepton;

    /**
     * @brief Jets
     *
     */
    HJet *jets;

private:

    float mass_;

};
