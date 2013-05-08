/*

  tuple GPL Source Code
  Copyright (C) 2013 Edward Knyshov

  This file is part of the tuple GPL Source Code (tuple Source Code).

  tuple Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  tuple Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with tuple Source Code. If not, see <http://www.gnu.org/licenses/>

*/

#ifndef TUPLEHELPERS_H
#define TUPLEHELPERS_H

#include "tupleimpl.hpp"

namespace tuple
{

// some usefull functions

template <class ... REST>
Tuple<REST ...> MakeTuple(REST ... _rest)
{
		return Tuple<REST ...>(_rest ...);
}

} // namespace tuple

#endif // TUPLEHELPERS_H
