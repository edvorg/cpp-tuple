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
		using TupleDataSuper = TupleData<REST...>;

		TupleData();
		TupleData(const T & _p1, const REST & ... _rest);

		inline void Get(T & _p1, REST & ... _rest) const;
		inline const T & Get() const;

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

		inline void Get(TupleDummyType & _p1) const;
		inline const TupleDummyType & Get() const;

private:
		static const TupleDummyType mMember = TupleDummyType();
};

// TupleData implementation

template <class T, class ... REST>
TupleData<T, REST...>::TupleData()
{
}

template <class T, class ... REST>
TupleData<T, REST...>::TupleData(const T & _p1, const REST & ... _rest):
		mMember(_p1),
		TupleDataSuper(_rest...)
{
}

template <class T, class ... REST>
inline void TupleData<T, REST...>::Get(T & _p1, REST & ... _rest) const
{
		_p1 = mMember;
		TupleDataSuper::Get(_rest...);
}

template <class T, class ... REST>
inline const T & TupleData<T, REST...>::Get() const
{
		return mMember;
}

// TupleData<TupleDummyType> implementation

TupleData<TupleDummyType>::TupleData()
{
}

TupleData<TupleDummyType>::TupleData(const TupleDummyType & _p1)
{
}

inline void TupleData<TupleDummyType>::Get(TupleDummyType & _p1) const
{
}

inline const TupleDummyType & TupleData<TupleDummyType>::Get() const
{
		return mMember;
}

#endif // TUPLEDATA_H
