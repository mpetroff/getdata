// (C) 2008, 2009 D. V. Wiebe
//
///////////////////////////////////////////////////////////////////////////
//
// This file is part of the GetData project.
//
// GetData is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// GetData is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with GetData; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
#include "getdata/rawentry.h"
#include "getdata/entry.h"
#include "getdata/dirfile.h"

#include <cstring>
#include <stdlib.h>
#include <stdint.h>

using namespace GetData;

RawEntry::RawEntry(const char* field_code, DataType data_type, unsigned int spf,
      int fragment_index) : Entry::Entry()
{
  E.field = strdup(field_code);
  E.field_type = GD_RAW_ENTRY;
  E.spf = spf;
  E.data_type = (gd_type_t)data_type;
  E.fragment_index = fragment_index;
}

int RawEntry::SetSamplesPerFrame(unsigned int spf, int recode)
{
  E.spf = spf;

  if (D != NULL)
    return dirfile_alter_entry(D->D, E.field, &E, recode);
  
  return 0;
}

int RawEntry::SetSamplesPerFrame(const char *spf, int recode)
{
  int r = 0;
  uint16_t u16;

  free(E.scalar[0]);
  if (spf == NULL)
    E.scalar[0] = NULL;
  else
    E.scalar[0] = strdup(spf);

  if (D != NULL) {
    r = dirfile_alter_entry(D->D, E.field, &E, recode);

    if (!r) {
      r = get_constant(D->D, spf, GD_UINT16, &u16);
      E.spf = (unsigned int)u16;
    }
  }
  
  return r;
}

int RawEntry::SetType(DataType type, int recode)
{
  E.data_type = (gd_type_t)type;

  if (D != NULL)
    return dirfile_alter_entry(D->D, E.field, &E, recode);
  
  return 0;
}

const char* RawEntry::FileName()
{
  return get_raw_filename(D->D, E.field);
}
