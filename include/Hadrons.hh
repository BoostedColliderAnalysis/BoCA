/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Types.hh"
#include "FourVector.hh"
#include "Flag.hh"
#include "Jet.hh"

namespace boca
{

/**
 * @brief flags defining to which level of detail jets should be analyzed
 *
 */
enum class JetDetail
{
    none = 0,
    plain = 1 << 0,
    structure = 1 << 1,
    isolation = 1 << 2,
};

template<>
struct Flag<JetDetail> {
    static const bool enable = true;
};

std::string Name(JetDetail jet_detail);

/**
 * @brief Base class for jets
 *
 */
class Hadrons : public FourVector
{

public:

    Hadrons(boca::TreeReader const& tree_reader);

    virtual ~Hadrons() {};

    virtual std::vector<Jet> Jets() const = 0;

    virtual Momentum ScalarHt() const;

    virtual boca::MissingEt MissingEt() const;

protected:

};

}
