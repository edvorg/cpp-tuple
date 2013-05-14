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

#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

namespace tuple
{

template <class T, class ... REST>
class Tuple;

template <unsigned int INDEX, class T, class ... REST>
class Accessor
{
public:
		inline static void Set(Tuple<T, REST ...> & _tuple, const typename Tuple<T, REST ...>::template MemberTypeIndexed<INDEX> & _val)
		{
				Accessor<INDEX - 1, REST ...>::Set(*_tuple.Next(), _val);
		}

		inline static const typename Tuple<T, REST ...>::template MemberTypeIndexed<INDEX> & Get(const Tuple<T, REST ...> & _tuple)
		{
				return Accessor<INDEX - 1, REST ...>::Get(*_tuple.Next());
		}

		inline static const typename Tuple<T, REST ...>::template SubTupleTypeIndexed<INDEX> & GetSubTuple(const Tuple<T, REST ...> & _tuple)
		{
				return Accessor<INDEX - 1, REST ...>::GetSubTuple(*_tuple.Next());
		}

		inline static typename Tuple<T, REST ...>::template SubTupleTypeIndexed<INDEX> & GetSubTuple(Tuple<T, REST ...> & _tuple)
		{
				return Accessor<INDEX - 1, REST ...>::GetSubTuple(*_tuple.Next());
		}
};

template <class T, class ... REST>
class Accessor<0, T, REST ...>
{
public:
		inline static void Set(Tuple<T, REST ...> & _tuple, const typename Tuple<T, REST ...>::template MemberTypeIndexed<0> & _val)
		{
				_tuple.Set(_val);
		}

		inline static const typename Tuple<T, REST ...>::template MemberTypeIndexed<0> & Get(const Tuple<T, REST ...> & _tuple)
		{
				return _tuple.Get();
		}

		inline static const typename Tuple<T, REST ...>::template SubTupleTypeIndexed<0> & GetSubTuple(const Tuple<T, REST ...> & _tuple)
		{
				return _tuple;
		}

		inline static typename Tuple<T, REST ...>::template SubTupleTypeIndexed<0> & GetSubTuple(Tuple<T, REST ...> & _tuple)
		{
				return _tuple;
		}
};

} // namespace tuple

#endif // ACCESSOR_HPP
