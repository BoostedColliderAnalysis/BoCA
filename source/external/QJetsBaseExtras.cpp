#include "boca/external/QJetsBaseExtras.hh"

namespace qjets
{

QJetsBaseExtras::QJetsBaseExtras() :
    _wij(-1.)
{}

QJetsBaseExtras::~QJetsBaseExtras()
{}

double QJetsBaseExtras::weight() const
{
    return _wij;
}

void QJetsBaseExtras::SetWeight(double weight)
{
    _wij = weight;
}

}
