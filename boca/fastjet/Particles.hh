/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/Particle.hh"
#include "boca/identification/Id.hh"

namespace boca
{

std::vector<Particle> CopyIfRelativeIs(std::vector<Particle> const& particles, Relative relative, Id id);

std::vector<Particle> CopyIfRelativeIs(const std::vector<boca::Particle>& particles, boca::Relative relative, std::vector<Id> const& ids);

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& particles, Id id);

std::vector<Particle> CopyIfParticles(std::vector<Particle> const& particles, std::vector<Id> const& ids);

std::vector<Particle> CopyIfNeutrino(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfLepton(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfExactParticle(std::vector<Particle> const& particles, int id);

std::vector<Particle> RemoveIfExactParticle(std::vector<Particle> particles, int id);

std::vector<Particle> CopyIfFamily(std::vector<Particle> const& particles, Id id, Id mother_id);

/**
 * @brief returns only particles with the correct id and non fitting grand mother id
 *
 */
std::vector<Particle> RemoveIfGrandFamily(std::vector<Particle> const& particles, Id id, Id grand_mother_id);

std::vector<Particle> CopyIfParticle(std::vector<Particle> const& particles, Id id);

std::vector<Particle> RemoveIfParticle(std::vector<Particle> particles, Id id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Id mother_id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, std::vector<Id> const& mother_id);

std::vector<Particle> CopyIfMother(std::vector<Particle> const& particles, Particle mother);

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Id grand_mother_id);

std::vector<Particle> CopyIfGrandMother(std::vector<Particle> const& particles, Particle grand_mother);

std::vector<Particle> CopyIfGreatGrandMother(std::vector<Particle> const& particles, Id grand_grand_mother_id);

std::vector<Particle> CopyIfAncestor(std::vector<Particle> const& particles, Id ancestor);

std::vector<Particle> RemoveIfMother(std::vector<Particle> const& particles, Id mother_id);

std::vector<Particle> RemoveIfMother(std::vector<Particle> const& particles, std::vector<Id> const& mother_ids);

std::vector<Particle> RemoveIfSingleMother(std::vector<Particle> const& particles);

std::vector<Particle> RemoveIfOnlyMother(std::vector<Particle> const& particles, Id mother_id);

std::vector<Particle> RemoveIfLetpon(std::vector<Particle> const& particles);

std::vector<Particle> RemoveIfQuark(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfQuark(std::vector<Particle> const& particles);

std::vector<Particle> CopyIf5Quark(std::vector<Particle> const& particles);

std::vector<Particle> CopyIfDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters);

std::vector<Particle> RemoveIfDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters);

std::vector<Particle> CopyIfGrandDaughter(std::vector<Particle> const& particles, std::vector<Particle> const& daughters);

std::vector<Particle> CopyIfPosition(std::vector<Particle> const& particles, int position);

std::vector<Particle> CopyIfPosition(std::vector<Particle> const& particles, int position_1, int position_2);

std::vector<Particle> CopyFirst(std::vector<Particle> particles, std::size_t number);

/**
 * @brief Copy the two particles which are on the DY position
 *
 * here we assume that the DY particle are always on position 6 and 7
 */
std::vector<Particle> CopyIfDrellYan(std::vector<Particle> const& particles);

void PrintParticles(std::vector<Particle> const& particles);

}
