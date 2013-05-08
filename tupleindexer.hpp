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

#ifndef TUPLEINDEXER_H
#define TUPLEINDEXER_H

namespace tuple
{

template <class T, class ... REST>
class Tuple;

template <unsigned int INDEX, class T, class ... REST>
class TupleIndexer
{
public:
		using TupleIndexerDeeper = TupleIndexer<INDEX - 1, REST...>;

		using TupleType = typename TupleIndexerDeeper::TupleType;
};

template <class T, class ... REST>
class TupleIndexer<0, T, REST...>
{
public:
		using TupleType = Tuple<T, REST...>;
};

} // namespace tuple

#endif // TUPLEINDEXER_H
