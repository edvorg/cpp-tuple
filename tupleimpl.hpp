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

#ifndef TUPLEIMPL_H
#define TUPLEIMPL_H

#include "tupleindexer.hpp"
#include "tuplehelpers.hpp"

namespace tuple
{

// declaration

template <class T, class ... REST>
class Tuple : public Tuple<REST...>
{
public:
		using Type = T;
		using TupleSuper = Tuple<REST...>;
		template<unsigned int INDEX>
		using TupleIndexer = tuple::TupleIndexer<INDEX, T, REST...>;

		Tuple();
		Tuple(const T & _p1, const REST & ... _rest);

		inline void Set(const T & _p1, const REST & ... _rest);
		inline void Get(T & _p1, REST & ... _rest) const;
		inline void Set(const T & _p1);
		inline const T & Get() const;
		inline TupleSuper * Next();
		inline const TupleSuper * Next() const;

		inline static unsigned int Index();

		template <unsigned int INDEX>
		inline void Set(const typename TupleIndexer<INDEX>::Type::Type & _p1);
		template <unsigned int INDEX>
		inline const typename TupleIndexer<INDEX>::Type::Type & Get() const;

protected:
		static const unsigned int mIndex = TupleSuper::mIndex + 1;

private:
		T mMember;
};

// ending specialization

template <class T>
class Tuple<T>
{
public:
		using Type = T;
		using TupleSuper = Tuple<T>;
		template<unsigned int INDEX>
		using TupleIndexer = tuple::TupleIndexer<INDEX, T>;

		Tuple();
		Tuple(const T & _p1);

		inline void Set(const T & _p1);
		inline void Get(T & _p1) const;
		inline const T & Get() const;
		inline TupleSuper * Next();
		inline const TupleSuper * Next() const;

		inline static unsigned int Index();

		template <unsigned int INDEX>
		inline void Set(const typename TupleIndexer<INDEX>::Type::Type & _p1);
		template <unsigned int INDEX>
		inline const typename TupleIndexer<INDEX>::Type::Type & Get() const;

protected:
		static const unsigned int mIndex = 0;

private:
		T mMember;
};

// Tuple implementation

template <class T, class ... REST>
Tuple<T, REST...>::Tuple()
{
}

template <class T, class ... REST>
Tuple<T, REST...>::Tuple(const T & _p1, const REST & ... _rest):
		mMember(_p1),
		TupleSuper(_rest...)
{
}

template <class T, class ... REST>
inline void Tuple<T, REST...>::Set(const T & _p1, const REST & ... _rest)
{
		mMember = _p1;
		TupleSuper::Set(_rest...);
}

template <class T, class ... REST>
inline void Tuple<T, REST...>::Get(T & _p1, REST & ... _rest) const
{
		_p1 = mMember;
		TupleSuper::Get(_rest...);
}

template <class T, class ... REST>
inline void Tuple<T, REST...>::Set(const T & _p1)
{
		mMember = _p1;
}

template <class T, class ... REST>
inline const T & Tuple<T, REST...>::Get() const
{
		return mMember;
}

template <class T, class ... REST>
inline Tuple<REST...> * Tuple<T, REST...>::Next()
{
		return this;
}

template <class T, class ... REST>
inline const Tuple<REST...> * Tuple<T, REST...>::Next() const
{
		return this;
}

template <class T, class ... REST>
inline unsigned int Tuple<T, REST...>::Index()
{
		return mIndex;
}

template <class T, class ... REST>
template <unsigned int INDEX>
inline void Tuple<T, REST...>::Set(const typename TupleIndexer<INDEX>::Type::Type & _p1)
{
		return static_cast<typename TupleIndexer<INDEX>::Type*>(this)->Set(_p1);
}

template <class T, class ... REST>
template <unsigned int INDEX>
inline const typename TupleIndexer<INDEX, T, REST...>::Type::Type & Tuple<T, REST...>::Get() const
{
		return static_cast<const typename TupleIndexer<INDEX>::Type*>(this)->Get();
}

// template<class T> Tuple<T> specialization

template <class T>
Tuple<T>::Tuple()
{
}

template <class T>
Tuple<T>::Tuple(const T & _p1):
		mMember(_p1)
{
}

template <class T>
inline void Tuple<T>::Set(const T & _p1)
{
		mMember = _p1;
}

template <class T>
inline void Tuple<T>::Get(T & _p1) const
{
		_p1 = mMember;
}

template <class T>
inline const T & Tuple<T>::Get() const
{
		return mMember;
}

template <class T>
inline Tuple<T> * Tuple<T>::Next()
{
		return nullptr;
}

template <class T>
inline const Tuple<T> * Tuple<T>::Next() const
{
		return nullptr;
}

template <class T>
inline unsigned int Tuple<T>::Index()
{
		return mIndex;
}

template <class T>
template <unsigned int INDEX>
inline void Tuple<T>::Set(const typename TupleIndexer<INDEX>::Type::Type & _p1)
{
		return static_cast<typename TupleIndexer<INDEX>::Type*>(this)->Set(_p1);
}

template <class T>
template <unsigned int INDEX>
inline const typename TupleIndexer<INDEX, T>::Type::Type & Tuple<T>::Get() const
{
		return static_cast<const typename TupleIndexer<INDEX>::Type*>(this)->Get();
}

} // namespace tuple

#endif // TUPLEIMPL_H
