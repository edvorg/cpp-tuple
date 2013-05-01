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
		typedef typename TupleIndexer<INDEX - 1, REST...>::Type Type;
};

template <class T, class ... REST>
class TupleIndexer<0, T, REST...>
{
public:
		typedef Tuple<T, REST...> Type;
};

} // namespace tuple

#endif // TUPLEINDEXER_H
