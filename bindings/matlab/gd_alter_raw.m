function gd_alter_raw(D, field_code, data_type, spf, recode)
% GD_ALTER_RAW  Modify the metadata of a RAW field
%
%   GD_ALTER_RAW(DIRFILE,NAME,TYPE,SPF,RECODE)
%             modifies the metadata of the RAW field called NAME in the
%             dirfile specified by DIRFILE.  The data type is set to TYPE, if
%             not GD.NULL, and the samples-per-frame to SPF, if not zero.  If
%             RECODE is non-zero, the binary file associated with the field will
%             be rewritten to reflect the changes; otherwise the binary file is
%             not modified.
%
%   The DIRFILE object should have previously been created with GD_OPEN.
%
%   See the documentation on the C API function gd_alter_raw(3) in section 3
%   of the UNIX manual for more details.
%
%   See also GD_ALTER_ENTRY, GD_OPEN

  GD = getdata_constants();
  gd_alter_entry(D, field_code, struct('field_type', GD.RAW_ENTRY, ...
  'data_type', data_type, 'spf', spf), recode);
end

% Copyright (C) 2013 D. V. Wiebe
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This file is part of the GetData project.
%
% GetData is free software; you can redistribute it and/or modify it under
% the terms of the GNU Lesser General Public License as published by the
% Free Software Foundation; either version 2.1 of the License, or (at your
% option) any later version.
%
% GetData is distributed in the hope that it will be useful, but WITHOUT
% ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
% FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
% License for more details.
%
% You should have received a copy of the GNU Lesser General Public License
% along with GetData; if not, write to the Free Software Foundation, Inc.,
% 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA