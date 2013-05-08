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
#include "range.hpp"
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

		/// sets all items to corresponding arguments
		inline void Set(const T & _p1, const REST & ... _rest);

		/// stores all items in corresponding arguments
		inline void Get(T & _p1, REST & ... _rest) const;

		/// sets first item
		inline void Set(const T & _p1);

		/// gets first item
		inline const T & Get() const;

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline TupleSuper * Next();

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline const TupleSuper * Next() const;

		/// sets element by INDEX. typesafe. if index is out of bounds, returns error at compile time
		template <unsigned int INDEX>
		inline void Set(const typename TupleIndexer<INDEX>::TupleType::Type & _p1);

		/// gets element by INDEX. typesafe. if index is out of bounds, return error at compile time
		template <unsigned int INDEX>
		inline const typename TupleIndexer<INDEX>::TupleType::Type & Get() const;

		/// returns elements count
		inline constexpr static unsigned int Count() { return mIndex + 1; }

		/// invokes some callable object
		template <class CALLABLE, unsigned int ... INDICES>
		inline void Invoke(CALLABLE & _function, const Indices<INDICES...> &);

		/// invokes some callable object
		template <class CALLABLE>
		inline void Invoke(CALLABLE & _function);
protected:

private:
		static constexpr unsigned int mIndex = TupleSuper::Count();
		T mMember = T();
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

		/// sets all items to corresponding arguments
		inline void Set(const T & _p1);

		/// stores all items in corresponding arguments
		inline void Get(T & _p1) const;

		/// gets first item
		inline const T & Get() const;

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline TupleSuper * Next();

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline const TupleSuper * Next() const;

		/// sets element by INDEX. typesafe. if index is out of bounds, returns error at compile time
		template <unsigned int INDEX>
		inline void Set(const typename TupleIndexer<INDEX>::TupleType::Type & _p1);

		/// gets element by INDEX. typesafe. if index is out of bounds, return error at compile time
		template <unsigned int INDEX>
		inline const typename TupleIndexer<INDEX>::TupleType::Type & Get() const;

		/// returns elements count
		inline constexpr static unsigned int Count() { return mIndex + 1; }

		/// invokes some callable object
		template <class CALLABLE>
		inline void Invoke(CALLABLE & _function);
protected:
private:
		static constexpr unsigned int mIndex = 0;
		T mMember = T();
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
template <unsigned int INDEX>
inline void Tuple<T, REST...>::Set(const typename TupleIndexer<INDEX>::TupleType::Type & _p1)
{
		return static_cast<typename TupleIndexer<INDEX>::TupleType*>(this)->Set(_p1);
}

template <class T, class ... REST>
template <unsigned int INDEX>
inline const typename TupleIndexer<INDEX, T, REST...>::TupleType::Type & Tuple<T, REST...>::Get() const
{
		return static_cast<const typename TupleIndexer<INDEX>::TupleType*>(this)->Get();
}

template <class T, class ... REST>
template <class CALLABLE, unsigned int ... INDICES>
inline void Tuple<T, REST...>::Invoke(CALLABLE & _function, const Indices<INDICES...> &)
{
		_function(Get<INDICES>()...);
}

template <class T, class ... REST>
template <class CALLABLE>
inline void Tuple<T, REST...>::Invoke(CALLABLE & _function)
{
		static constexpr typename Range<0, mIndex>::Indices fiction;
		Invoke(_function, fiction);
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
template <unsigned int INDEX>
inline void Tuple<T>::Set(const typename TupleIndexer<INDEX>::TupleType::Type & _p1)
{
		return static_cast<typename TupleIndexer<INDEX>::TupleType*>(this)->Set(_p1);
}

template <class T>
template <unsigned int INDEX>
inline const typename TupleIndexer<INDEX, T>::TupleType::Type & Tuple<T>::Get() const
{
		return static_cast<const typename TupleIndexer<INDEX>::TupleType*>(this)->Get();
}

template <class T>
template <class CALLABLE>
inline void Tuple<T>::Invoke(CALLABLE & _function)
{
		_function(mMember);
}

} // namespace tuple

#endif // TUPLEIMPL_H
