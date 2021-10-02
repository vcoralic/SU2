/*!
 * \file CPassiveScalarVariable.cpp
 * \brief Definition of the variable fields for the passive scalar class.
 * \author D. Mayer, T. Economon
 * \version 7.1.1 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
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


#include "../../include/variables/CPassiveScalarVariable.hpp"

CPassiveScalarVariable::CPassiveScalarVariable(su2double *val_scalar_inf, unsigned long npoint, unsigned long ndim, unsigned long nvar,
                                               CConfig *config) : CScalarLegacyVariable(npoint, ndim, nvar, config) {

  for(unsigned long iPoint=0; iPoint<nPoint; ++iPoint)
  {
    for (unsigned long iVar = 0; iVar < nVar; iVar++) {
      Solution(iPoint,iVar) = val_scalar_inf[iVar];
    }
  }

  Solution_Old = Solution;
  
  /*--- Allocate and initialize solution for the dual time strategy ---*/
  bool dual_time = ((config->GetTime_Marching() == TIME_MARCHING::DT_STEPPING_1ST) ||
                    (config->GetTime_Marching() == TIME_MARCHING::DT_STEPPING_2ND));

  if (dual_time) {
    Solution_time_n  = Solution;
    Solution_time_n1 = Solution;
  }

}