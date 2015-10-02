#pragma once

#include "Leptons.hh"


namespace analysis
{
  
class Event;

class Isolation : public analysis::Leptons
{
public:
    Isolation(Event &event);
    Jets leptons() const;
    Jets Electrons() const;
    Jets Muons() const;
    Event &event_;
};

}
