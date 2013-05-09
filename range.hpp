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

#ifndef RANGE_H
#define RANGE_H

namespace tuple
{

template <class T, class ... REST>
class Tuple;

template <unsigned int ... INDICES>
class Indices
{
public:
		template <class T, class ... REST>
		using SubTupleType = Tuple<typename Tuple<T, REST ...>::template MemberTypeIndexed<INDICES> ...>;

protected:
private:
};

template <unsigned int A, unsigned int B>
class Range
{
public:
		using RangeLesser = Range<A, B + (A < B ? - 1 : 1)>;
		template <unsigned int ... INDICES>
		using IndicesExtendable = typename RangeLesser::template IndicesExtendable<B, INDICES ...>;
		using Indices = IndicesExtendable<>;

protected:
private:
};

template <unsigned int INDEX>
class Range<INDEX, INDEX>
{
public:
		template <unsigned int ... INDICES>
		using IndicesExtendable = tuple::Indices<INDEX, INDICES ...>;
		using Indices = IndicesExtendable<>;

protected:
private:
};

} // namespace tuple

#endif // RANGE_H
