/* Copyright (C) 2013 D. V. Wiebe
 *
 ***************************************************************************
 *
 * This file is part of the GetData project.
 *
 * GetData is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * GetData is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with GetData; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "gd_matlab.h"

/*
 % GD_ALTER_SPEC  Modify field metadata
 %
 %   GD_ALTER_SPEC(DIRFILE,SPEC[,RECODE])
 %             modifies the metadata of a field in the dirfile DIRFILE
 %             according to the field specification line SPEC.  If
 %             RECODE is given and non-zero, other data will be updated to
 %             reflect metadata changes.
 %
 %   The DIRFILE object should have previously been created with GD_OPEN.
 %
 %   See the documentation on the C API function gd_alter_spec(3) in
 %   section 3 of the UNIX manual for more details.
 %
 %   See also GD_MALTER_SPEC, GD_OPEN
 */

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  DIRFILE *D;
  char *spec;
  int recode = 0;

  GDMX_NO_LHS;
  GDMX_CHECK_RHS2(2,3);

  D = gdmx_to_dirfile(prhs[0]);
  spec = gdmx_to_string(prhs, 1, 0);
  if (nrhs > 2)
    recode = gdmx_to_int(prhs, 2);

  gd_alter_spec(D, spec, recode);

  mxFree(spec);
  gdmx_err(D, 0);
}
