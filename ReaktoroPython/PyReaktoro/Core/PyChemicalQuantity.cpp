// Reaktoro is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
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

#include "PyChemicalQuantity.hpp"

// Boost includes
#include <boost/python.hpp>
namespace py = boost::python;

// Reaktoro includes
#include <Reaktoro/Core/ChemicalQuantity.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Core/ChemicalState.hpp>
#include <Reaktoro/Core/ReactionSystem.hpp>

namespace Reaktoro {

auto export_ChemicalQuantity() -> void
{
    auto update1 = static_cast<void(ChemicalQuantity::*)(const ChemicalState&)>(&ChemicalQuantity::update);
    auto update2 = static_cast<void(ChemicalQuantity::*)(const ChemicalState&,double)>(&ChemicalQuantity::update);

    py::class_<ChemicalQuantity>("ChemicalQuantity")
        .def(py::init<>())
        .def(py::init<const ChemicalSystem&>())
        .def(py::init<const ReactionSystem&>())
        .def("update", update1)
        .def("update", update2)
        .def("value", &ChemicalQuantity::value)
        .def("__getitem__", &ChemicalQuantity::value)
        ;
}

} // namespace Reaktoro