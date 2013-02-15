function nfields = gd_nmfields_by_type(D, parent, type)
% GD_NMFIELDS_BY_TYPE  Retrieve a count of fields
%
%   GD_NMFIELDS_BY_TYPE(DIRFILE,PARENT,TYPE)
%             is equivalent to calling GD_NENTRIES(DIRFILE,PARENT,TYPE,0)
%
%   See also GD_NENTRIES

  nfields = gd_nentries(D, parent, type, 0);
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
