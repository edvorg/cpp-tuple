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
#include "accessor.hpp"

namespace tuple
{

// declaration

template <class T, class ... REST>
class Tuple
{
public:
		using LeftMemberType = T;
		template <unsigned int INDEX>
		using MemberTypeIndexed = typename tuple::TupleIndexer<INDEX, T, REST ...>::TupleType::LeftMemberType;
		using TupleSuper = Tuple<REST ...>;
		template <unsigned int INDEX>
		using TupleTypeIndexed = typename tuple::TupleIndexer<INDEX, T, REST ...>::TupleType;
		template <unsigned int ... INDICES>
		using SubTupleTypeIndexed = Tuple<MemberTypeIndexed<INDICES> ...>;
		template <unsigned int A, unsigned int B>
		using SubTupleTypeRanged = typename Range<A, B>::Indices::template SubTupleType<T, REST ...>;

		static constexpr unsigned int mIndex = TupleSuper::Count();

		Tuple();
		Tuple(const Tuple & _src);
		Tuple(Tuple && _src);
		Tuple(const T & _p1, const REST & ... _rest);

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline TupleSuper * Next();

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline const TupleSuper * Next() const;

		/// copies data from entire _src tuple to this tuple
		inline void Set(const Tuple & _src);

		/// sets all items to corresponding arguments
		inline void Set(const T & _p1, const REST & ... _rest);

		/// stores all items in corresponding arguments
		inline void Get(T & _p1, REST & ... _rest) const;

		/// sets first item
		inline void Set(const T & _p1);

		/// gets first item
		inline const T & Get() const;

		/// sets element by INDEX. typesafe. if index is out of bounds, returns error at compile time
		template <unsigned int INDEX>
		inline void Set(const MemberTypeIndexed<INDEX> & _p1);

		/// gets element by INDEX. typesafe. if index is out of bounds, return error at compile time
		template <unsigned int INDEX>
		inline const MemberTypeIndexed<INDEX> & Get() const;

		/// creates new tuple with members from this tuple, indexed by INDICES template parameter pack
		template <unsigned int ... INDICES>
		inline SubTupleTypeIndexed<INDICES ...> MakeTuple(const Indices<INDICES ...> & _indices = Indices<INDICES ...>()) const;

		/// creates new tuple with members from this tuple, ranged by A,B indices
		template <unsigned int A, unsigned int B>
		inline SubTupleTypeRanged<A, B> MakeSubTuple() const;

		/// returns elements count
		inline static constexpr unsigned int Count() { return mIndex + 1; }

		/// invokes some callable object
		template <class CALLABLE, unsigned int ... INDICES>
		inline auto Invoke(CALLABLE & _function, const Indices<INDICES ...> & _indices = Indices<INDICES ...>()) const -> decltype(_function(Get<INDICES>() ...));

		/// invokes some callable object
		template <class CALLABLE>
		inline auto Invoke(CALLABLE & _function) const -> decltype(Invoke(_function, typename Range<0, mIndex>::Indices()));
protected:

private:
		T mMember = T();
		TupleSuper mRest = TupleSuper();
};

// ending specialization

template <class T>
class Tuple<T>
{
public:
		using LeftMemberType = T;
		template <unsigned int INDEX>
		using MemberTypeIndexed = typename tuple::TupleIndexer<INDEX, T>::TupleType::LeftMemberType;
		using TupleSuper = Tuple<T>;
		template <unsigned int INDEX>
		using TupleTypeIndexed = typename tuple::TupleIndexer<INDEX, T>::TupleType;
		template <unsigned int ... INDICES>
		using SubTupleTypeIndexed = Tuple<MemberTypeIndexed<INDICES> ...>;
		template <unsigned int A, unsigned int B>
		using SubTupleTypeRanged = typename Range<A, B>::Indices::template SubTupleType<T>;

		static constexpr unsigned int mIndex = 0;

		Tuple();
		Tuple(const Tuple & _src);
		Tuple(Tuple && _src);
		Tuple(const T & _p1);

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline TupleSuper * Next();

		/// gets subtuple not containing first item (just converts this pointer to it)
		/// use this to get next item in runtime
		/// if there is no items after first item, returns nullptr
		inline const TupleSuper * Next() const;

		/// copies data from entire _src tuple to this tuple
		inline void Set(const Tuple & _src);

		/// sets all items to corresponding arguments
		inline void Set(const T & _p1);

		/// stores all items in corresponding arguments
		inline void Get(T & _p1) const;

		/// gets first item
		inline const T & Get() const;

		/// sets element by INDEX. typesafe. if index is out of bounds, returns error at compile time
		template <unsigned int INDEX>
		inline void Set(const MemberTypeIndexed<INDEX> & _p1);

		/// gets element by INDEX. typesafe. if index is out of bounds, return error at compile time
		template <unsigned int INDEX>
		inline const MemberTypeIndexed<INDEX> & Get() const;

		/// creates new tuple with members from this tuple, indexed by INDICES template parameter pack
		template <unsigned int ... INDICES>
		inline SubTupleTypeIndexed<INDICES ...> MakeTuple(const Indices<INDICES ...> & _indices = Indices<INDICES ...>()) const;

		/// creates new tuple with members from this tuple, ranged by A,B indices
		template <unsigned int A, unsigned int B>
		inline SubTupleTypeRanged<A, B> MakeSubTuple() const;

		/// returns elements count
		inline static constexpr unsigned int Count() { return mIndex + 1; }

		/// invokes some callable object
		template <class CALLABLE, unsigned int INDEX = 0>
		inline auto Invoke(CALLABLE & _function) const -> decltype(_function(Get<INDEX>()));
protected:
private:
		T mMember = T();
};

// Tuple implementation

template <class T, class ... REST>
Tuple<T, REST ...>::Tuple()
{
}

template <class T, class ... REST>
Tuple<T, REST ...>::Tuple(const Tuple & _src):
		mMember(_src.mMember),
		mRest(_src.mRest)
{
}

template <class T, class ... REST>
Tuple<T, REST ...>::Tuple(Tuple && _src):
		mMember(std::move(_src.mMember)),
		mRest(std::move(_src.mRest))
{
}

template <class T, class ... REST>
Tuple<T, REST ...>::Tuple(const T & _p1, const REST & ... _rest):
		mMember(_p1),
		mRest(_rest ...)
{
}

template <class T, class ... REST>
inline Tuple<REST ...> * Tuple<T, REST ...>::Next()
{
		return &mRest;
}

template <class T, class ... REST>
inline const Tuple<REST ...> * Tuple<T, REST ...>::Next() const
{
		return &mRest;
}

template <class T, class ... REST>
inline void Tuple<T, REST ...>::Set(const Tuple & _src)
{
		mMember = _src.mMember;
		mRest.Set(_src.mRest);
}

template <class T, class ... REST>
inline void Tuple<T, REST ...>::Set(const T & _p1, const REST & ... _rest)
{
		mMember = _p1;
		mRest.Set(_rest ...);
}

template <class T, class ... REST>
inline void Tuple<T, REST ...>::Get(T & _p1, REST & ... _rest) const
{
		_p1 = mMember;
		mRest.Get(_rest ...);
}

template <class T, class ... REST>
inline void Tuple<T, REST ...>::Set(const T & _p1)
{
		mMember = _p1;
}

template <class T, class ... REST>
inline const T & Tuple<T, REST ...>::Get() const
{
		return mMember;
}

template <class T, class ... REST>
template <unsigned int INDEX>
inline void Tuple<T, REST ...>::Set(const MemberTypeIndexed<INDEX> & _p1)
{
		Accessor<INDEX, T, REST ...>::Set(*this, _p1);
}

template <class T, class ... REST>
template <unsigned int INDEX>
inline const typename Tuple<T, REST ...>::template MemberTypeIndexed<INDEX> & Tuple<T, REST ...>::Get() const
{
		return Accessor<INDEX, T, REST ...>::Get(*this);
}

template <class T, class ... REST>
template <unsigned int ... INDICES>
inline Tuple<T, REST ...>::SubTupleTypeIndexed<INDICES ...> Tuple<T, REST ...>::MakeTuple(const Indices<INDICES ...> &) const
{
		return Tuple<MemberTypeIndexed<INDICES> ...>(Get<INDICES>() ...);
}

template <class T, class ... REST>
template <unsigned int A, unsigned int B>
inline Tuple<T, REST ...>::SubTupleTypeRanged<A, B> Tuple<T, REST ...>::MakeSubTuple() const
{
		return MakeTuple(typename Range<A, B>::Indices());
}

template <class T, class ... REST>
template <class CALLABLE, unsigned int ... INDICES>
inline auto Tuple<T, REST ...>::Invoke(CALLABLE & _function, const Indices<INDICES ...> &) const -> decltype(_function(Get<INDICES>() ...))
{
		return _function(Get<INDICES>()...);
}

template <class T, class ... REST>
template <class CALLABLE>
inline auto Tuple<T, REST ...>::Invoke(CALLABLE & _function) const -> decltype(Invoke(_function, typename Range<0, mIndex>::Indices()))
{
		return Invoke(_function, typename Range<0, mIndex>::Indices());
}

// template<class T> Tuple<T> specialization

template <class T>
Tuple<T>::Tuple()
{
}

template <class T>
Tuple<T>::Tuple(const Tuple & _src):
		mMember(_src.mMember)
{
}

template <class T>
Tuple<T>::Tuple(Tuple && _src):
		mMember(std::move(_src.mMember))
{
}

template <class T>
Tuple<T>::Tuple(const T & _p1):
		mMember(_p1)
{
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
inline void Tuple<T>::Set(const Tuple & _src)
{
		mMember = _src.mMember;
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
template <unsigned int INDEX>
inline void Tuple<T>::Set(const MemberTypeIndexed<INDEX> & _p1)
{
		Accessor<INDEX, T>::Set(*this, _p1);
}

template <class T>
template <unsigned int INDEX>
inline const typename Tuple<T>::template MemberTypeIndexed<INDEX> & Tuple<T>::Get() const
{
		return Accessor<INDEX, T>::Get(*this);
}

template <class T>
template <unsigned int ... INDICES>
inline Tuple<T>::SubTupleTypeIndexed<INDICES ...> Tuple<T>::MakeTuple(const Indices<INDICES ...> &) const
{
		return Tuple<MemberTypeIndexed<INDICES> ...>(Get<INDICES>() ...);
}

template <class T>
template <unsigned int A, unsigned int B>
inline Tuple<T>::SubTupleTypeRanged<A, B> Tuple<T>::MakeSubTuple() const
{
		return MakeTuple(typename Range<A, B>::Indices());
}

template <class T>
template <class CALLABLE, unsigned int INDEX>
inline auto Tuple<T>::Invoke(CALLABLE & _function) const -> decltype(_function(Get<INDEX>()))
{
		_function(mMember);
}

} // namespace tuple

#endif // TUPLEIMPL_H
