/*!
 * \file linear_solvers_structure_b.cpp
 * \brief Routines for the linear solver used in the reverse sweep of AD.
 * \author T. Albring
 * \version 7.0.0 "Blackbird"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2019, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../../include/linear_algebra/CSysSolve_b.hpp"
#include "../../include/linear_algebra/CSysSolve.hpp"
#include "../../include/linear_algebra/CSysMatrix.hpp"
#include "../../include/linear_algebra/CSysVector.hpp"

#ifdef CODI_REVERSE_TYPE
template<class ScalarType>
void CSysSolve_b<ScalarType>::Solve_b(const codi::RealReverse::Real* x, codi::RealReverse::Real* x_b, size_t m,
                                      const codi::RealReverse::Real* y, const codi::RealReverse::Real* y_b, size_t n,
                                      codi::DataStore* d) {

  CSysVector<su2double>* LinSysRes_b = NULL;
  d->getData(LinSysRes_b);

  CSysVector<su2double>* LinSysSol_b = NULL;
  d->getData(LinSysSol_b);

  CSysMatrix<ScalarType>* Jacobian = NULL;
  d->getData(Jacobian);

  CGeometry* geometry  = NULL;
  d->getData(geometry);

  CConfig* config      = NULL;
  d->getData(config);

  CSysSolve<ScalarType>* solver = NULL;
  d->getData(solver);

  /*--- Initialize the right-hand side with the gradient of the solution of the primal linear system ---*/

  for (unsigned long i = 0; i < n; i ++) {
    (*LinSysRes_b)[i] = y_b[i];
    (*LinSysSol_b)[i] = 0.0;
  }

  solver->Solve_b(*Jacobian, *LinSysRes_b, *LinSysSol_b, geometry, config);

  for (unsigned long i = 0; i < n; i ++) {
    x_b[i] = SU2_TYPE::GetValue(LinSysSol_b->operator [](i));
  }

}

template class CSysSolve_b<su2double>;
template class CSysSolve_b<passivedouble>;

#endif
