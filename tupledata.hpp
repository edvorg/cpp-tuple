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

#ifndef TUPLEDATA_H
#define TUPLEDATA_H

// declaration

// backbone for Tuple<class ... REST> class

template <class T, class ... REST>
class TupleData : public TupleData<REST...>
{
public:
		TupleData();
		TupleData(const T & _p1, const REST & ... _rest);

		void Get(T & _p1, REST & ... _rest);

private:
		T mMember;
};

// dummy type. used to specialize the TupleData template
// this type must be last in template args list
// for exmaple TupleData<int, char, TupleDummyType>

using TupleDummyType = int;

// this specialization is needed to avoid inheritance,
// when the last type expanded from template args list

template <>
class TupleData<TupleDummyType>
{
public:
		TupleData();
		TupleData(const TupleDummyType & _p1);

		void Get(TupleDummyType & _p1);
};

// implementation

TupleData<TupleDummyType>::TupleData()
{
}

TupleData<TupleDummyType>::TupleData(const TupleDummyType & _p1)
{
}

void TupleData<TupleDummyType>::Get(TupleDummyType & _p1)
{
}

template <class T, class ... REST>
TupleData<T, REST...>::TupleData()
{
}

template <class T, class ... REST>
TupleData<T, REST...>::TupleData(const T & _p1, const REST & ... _rest):
		mMember(_p1),
		TupleData<REST...>(_rest...)
{
}

template <class T, class ... REST>
void TupleData<T, REST...>::Get(T & _p1, REST & ... _rest)
{
		_p1 = mMember;
		TupleData<REST...>::Get(_rest...);
}

#endif // TUPLEDATA_H
