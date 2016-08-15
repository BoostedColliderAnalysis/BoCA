#pragma once

#include "fastjet/ClusterSequence.hh"

namespace qjets {

class QJetsBaseExtras : public fastjet::ClusterSequence::Extras
{
public:
    QJetsBaseExtras();
    virtual ~QJetsBaseExtras();
    virtual double weight() const;
    void SetWeight(double weight);
protected:
    double _wij;
};

}
