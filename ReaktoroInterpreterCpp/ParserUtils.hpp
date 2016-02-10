// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2015 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <istream>
#include <string>
#include <tuple>
#include <vector>

// yaml-cpp includes
#include <yaml-cpp/yaml.h>

namespace iReaktoro {

/// A type used to represent a pair (value, units).
struct ValueUnits
{
    /// The value
    double value;

    /// The units
    std::string units;
};

/// A type used to represent a triplet (entity, value, units).
struct EntityValueUnits : ValueUnits
{
    /// The entity name
    std::string entity;
};

/// A type used to represent a triplet (value, units, entity) used in a Mixture node.
struct MixtureCompound : EntityValueUnits
{
    MixtureCompound();
    MixtureCompound(std::string str);
};

/// A type used to represent a mixture of compounds, with their names, amounts, and units.
using Mixture = std::vector<MixtureCompound>;

/// A type used to represent an equilibrium constraint.
struct EquilibriumConstraint
{
    struct Base : EntityValueUnits
    {
        /// The titrant name used to control the constraint.
        std::string titrant1;

        /// The additional titrant name used to control the constraint.
        /// If titrant1 and titrant2 are non-empty, then they are mutually exclusive.
        std::string titrant2;
    };

    struct pH              : Base {};
    struct SpeciesAmount   : Base {};
    struct SpeciesActivity : Base {};
    struct PhaseAmount     : Base {};
    struct PhaseVolume     : Base {};
};

/// A type used to represent an equilibrium calculation.
struct Equilibrium
{
    /// The name of the chemical state where this equilibrium calculation is saved.
    std::string stateid;

    /// The temperature for the equilibrium calculation.
    ValueUnits temperature = {25.0, "celsius"};

    /// The pressure for the equilibrium calculation.
    ValueUnits pressure = {1.0, "bar"};

    /// The mixture definition for the equilibrium calculation.
    Mixture mixture;

    /// The pH constraints (only the last one used)
    std::vector<EquilibriumConstraint::pH> pH;

    /// The species amount constraints
    std::vector<EquilibriumConstraint::SpeciesAmount> species_amounts;

    /// The species activity constraints
    std::vector<EquilibriumConstraint::SpeciesActivity> species_activities;

    /// The phase amount constraints
    std::vector<EquilibriumConstraint::PhaseAmount> phase_amounts;

    /// The phase volume constraints
    std::vector<EquilibriumConstraint::PhaseVolume> phase_volumes;

    /// The list of inert species in the equilibrium calculation.
    std::vector<EntityValueUnits> inert_species;

    /// The list of inert phases in the equilibrium calculation.
    std::vector<std::string> inert_phases;
};

struct Universe
{
    /// The list of equilibrium problems to be executed
    std::vector<Equilibrium> equilibrium_problems;
};

/// Return a Reaktoro sript file as string with preprocessed lines.
auto preprocess(std::string script) -> std::string;

/// Return a Reaktoro sript file as string with preprocessed lines.
auto preprocess(std::istream& stream) -> std::string;

using Node = YAML::Node;

auto str(const Node& node) -> std::string;
auto keynode(const Node& node) -> Node;
auto valnode(const Node& node) -> Node;
auto keyword(const Node& node) -> std::string;
auto identifier(const Node& node) -> std::string;

auto operator>>(const Node& node, ValueUnits& x) -> void;
auto operator>>(const Node& node, EntityValueUnits& x) -> void;
auto operator>>(const Node& node, MixtureCompound& x) -> void;
auto operator>>(const Node& node, Mixture& x) -> void;
auto operator>>(const Node& node, EquilibriumConstraint::pH& x) -> void;
auto operator>>(const Node& node, EquilibriumConstraint::SpeciesAmount& x) -> void;
auto operator>>(const Node& node, EquilibriumConstraint::SpeciesActivity& x) -> void;
auto operator>>(const Node& node, EquilibriumConstraint::PhaseAmount& x) -> void;
auto operator>>(const Node& node, EquilibriumConstraint::PhaseVolume& x) -> void;
auto operator>>(const Node& node, Equilibrium& x) -> void;

} // namespace iReaktoro
