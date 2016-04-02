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

#include <Reaktoro/Reaktoro.hpp>
using namespace Reaktoro;

int main()
{
    Database database("supcrt98.xml");

    ChemicalEditor editor(database);
//    editor.addAqueousPhase("H2O");
    editor.addAqueousPhase("H2O NaCl CO2");
    editor.addGaseousPhase("H2O(g) CO2(g)");
    editor.addMineralPhase("Halite");

    ChemicalSystem system(editor);

    EquilibriumProblem problem(system);
    problem.setTemperature(60, "celsius");
    problem.setPressure(300, "bar");
    problem.add("H2O", 1, "kg");
    problem.add("CO2", 100, "g");
    problem.add("NaCl", 0.1, "mol");

    EquilibriumOptions options;
    options.epsilon = 1e-50;

    ChemicalState state = equilibrate(problem, options);

    std::cout << state << std::endl;

    std::cout << state.properties().Eh() << std::endl;
    std::cout << state.properties().pe() << std::endl;
    std::cout << state.properties().pe("H2(aq) = 2*H+ + 2*e-") << std::endl;
    std::cout << state.properties().pe("0.5*O2(aq) + 2*H+ + 2*e- = H2O(l)") << std::endl;
}
