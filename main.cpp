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

#include <cstdio>
#include <string>
#include <iostream>
#include <functional>

#include "tuple.hpp"

void TestFunction(int p1, char p2, double p3, std::string p4)
{
		std::cout << "* " << p1 << std::endl;
		std::cout << "* " << p2 << std::endl;
		std::cout << "* " << p3 << std::endl;
		std::cout << "* " << p4 << std::endl;
		std::cout << std::endl;
}

template <class CALLABLE, class ... ARGS>
class Bind
{
public:
		using Tuple = tuple::Tuple<ARGS ...>;

private:
		CALLABLE mCallable;
		Tuple mTuple;

public:

		Bind(CALLABLE _callable, const ARGS & ... _args):
				mCallable(_callable),
				mTuple(_args ...)
		{
		}

		auto operator() () -> decltype(mTuple.Invoke(mCallable))
		{
				return mTuple.Invoke(mCallable);
		}

};

template <class CALLABLE, class ... ARGS>
Bind<CALLABLE, ARGS ...> MakeBind(CALLABLE _callable, ARGS ... _args)
{
		return Bind<CALLABLE, ARGS ...>(_callable, _args ...);
}

void f1()
{
}

void f2()
{
		return f1(); // works ??
}

int main(int _argc, char ** _argv)
{
		using namespace tuple;

		auto t1 = MakeTuple(1, 'a', 3.14, std::string("hello world"));

		std::cout << t1.Get() << std::endl;
		std::cout << t1.Next()->Get() << std::endl;
		std::cout << t1.Next()->Next()->Get() << std::endl;
		std::cout << t1.Next()->Next()->Next()->Get() << std::endl;
		std::cout << std::endl;

		int v0;
		char v1;
		double v2;
		std::string v3;

		t1.Get(v0, v1, v2, v3);
		std::cout << v0 << std::endl;
		std::cout << v1 << std::endl;
		std::cout << v2 << std::endl;
		std::cout << v3 << std::endl;
		std::cout << std::endl;

		t1.Set(2, 'b', 6.28, std::string("2"));

		t1.Get(v0, v1, v2, v3);
		std::cout << v0 << std::endl;
		std::cout << v1 << std::endl;
		std::cout << v2 << std::endl;
		std::cout << v3 << std::endl;
		std::cout << std::endl;

		t1.Set(3);

		t1.Get(v0, v1, v2, v3);
		std::cout << v0 << std::endl;
		std::cout << v1 << std::endl;
		std::cout << v2 << std::endl;
		std::cout << v3 << std::endl;
		std::cout << std::endl;

		std::cout << t1.Count() << std::endl;
		std::cout << t1.Next()->Count() << std::endl;
		std::cout << t1.Next()->Next()->Count() << std::endl;
		std::cout << t1.Next()->Next()->Next()->Count() << std::endl;
		std::cout << std::endl;

		std::cout << t1.Get<0>() << std::endl;
		std::cout << t1.Get<1>() << std::endl;
		std::cout << t1.Get<2>() << std::endl;
		std::cout << t1.Get<3>() << std::endl;
		// std::cout << t1.Get<4>() << std::endl; // compile time error
		std::cout << std::endl;

		t1.Set<0>(7);
		t1.Set<1>('$');
		t1.Set<2>(3.105);
		t1.Set<3>("set test");
		// t1.Set<4>("set test"); // compile time error for any type of argument

		std::cout << t1.Get<0>() << std::endl;
		std::cout << t1.Get<1>() << std::endl;
		std::cout << t1.Get<2>() << std::endl;
		std::cout << t1.Get<3>() << std::endl;
		std::cout << std::endl;

		auto f = [] (int p1, char p2, double p3, std::string p4)
				{
						std::cout << "& " << p1 << std::endl;
						std::cout << "& " << p2 << std::endl;
						std::cout << "& " << p3 << std::endl;
						std::cout << "& " << p4 << std::endl;
						std::cout << std::endl;
						return std::string("lambda result");
				};

		t1.Invoke(f);
		t1.Invoke(TestFunction);

		auto b1 = MakeBind(f, 12, 'E', 1.178, "bind test");

		std::cout << b1() << std::endl << std::endl;

		auto t2 = t1.MakeTuple<3, 2, 1>();

		std::cout << t2.Get<0>() << std::endl;
		std::cout << t2.Get<1>() << std::endl;
		std::cout << t2.Get<2>() << std::endl;
		// std::cout << t2.Get<3>() << std::endl; // compile time error
		std::cout << std::endl;

		auto t3 = t1.MakeSubTuple<1, 2>();

		std::cout << t3.Get<0>() << std::endl;
		std::cout << t3.Get<1>() << std::endl;
		// std::cout << t3.Get<2>() << std::endl; // compile time error
		std::cout << std::endl;

		auto t4 = t1.MakeSubTuple<3, 0>();

		std::cout << t4.Get<0>() << std::endl;
		std::cout << t4.Get<1>() << std::endl;
		std::cout << t4.Get<2>() << std::endl;
		std::cout << t4.Get<3>() << std::endl;
		// std::cout << t4.Get<4>() << std::endl; // compile time error
		std::cout << std::endl;

		auto l1 = [] (std::string p1, char p2) -> std::string
				{
						return p1 + p2;
				};

		auto t5 = MakeTuple(std::string("Hello, "), 'X');

		// Invoke return type deduction working
		std::cout << t5.Invoke(l1) << std::endl << std::endl;

		return 0;
}
