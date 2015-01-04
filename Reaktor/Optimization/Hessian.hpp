// Reaktor is a C++ library for computational reaction modelling.
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

#pragma once

// Reaktor includes
#include <Reaktor/Common/Matrix.hpp>

namespace Reaktor {

/// A type to describe the Hessian of an objective function
struct Hessian
{
    /// An enumeration of possible modes for an Hessian representation
    enum Mode { Dense, Diagonal, Inverse };

    /// The mode of the Hessian.
    /// It is the responsibility of the user to set the appropriate `mode`
    /// of the Hessian matrix for its subsequent proper usage.
    /// ~~~
    /// Hessian hessian;
    /// hessian.mode = Hessian::Diagonal;
    /// hessian.diagonal = diag(1/x);
    /// ~~~
    Mode mode;

    /// The Hessian matrix represented through its inverse
    Matrix inverse;

    /// The Hessian matrix represented as a dense matrix
    Matrix dense;

    /// The Hessian matrix represented as a diagonal matrix
    Vector diagonal;
};

} // namespace Reaktor
