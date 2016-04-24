#pragma once

#include "fastjet/ClusterSequence.hh"

namespace qjets {

class QJetsBaseExtras : public fastjet::ClusterSequence::Extras
{
public:
    QJetsBaseExtras(): _wij(-1.) {}
    virtual ~QJetsBaseExtras() {};
    virtual double weight() const {
        return _wij;
    };
    void SetWeight(double weight){
      _wij = weight;
    }
protected:
    double _wij;
};

}
