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

#include "tuple.hpp"

void TestFunction(int p1, char p2, double p3, std::string p4)
{
		std::cout << "* " << p1 << std::endl;
		std::cout << "* " << p2 << std::endl;
		std::cout << "* " << p3 << std::endl;
		std::cout << "* " << p4 << std::endl;
}

template <class ... ARGS>
class Bind
{
public:
		using Function = std::function<void (ARGS ...)>;
		using Tuple = tuple::Tuple<ARGS ...>;

		Bind(Function _function, const ARGS & ... _args):
				mFunction(_function),
				mTuple(_args ...)
		{
		}

		void operator() ()
		{
				mTuple.Invoke(mFunction);
		}

private:
		Function mFunction;
		Tuple mTuple;
};

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

		std::function<void (int, char, double, std::string)> f = [] (int p1, char p2, double p3, std::string p4)
				{
						std::cout << "& " << p1 << std::endl;
						std::cout << "& " << p2 << std::endl;
						std::cout << "& " << p3 << std::endl;
						std::cout << "& " << p4 << std::endl;
				};

		t1.Invoke(f);
		t1.Invoke(TestFunction);

		Bind<int, char, double, std::string> b1(f, 12, 'E', 1.178, "bind test");

		b1();

		return 0;
}
