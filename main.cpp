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

		std::cout << t1.Index() << std::endl;
		std::cout << t1.Next()->Index() << std::endl;
		std::cout << t1.Next()->Next()->Index() << std::endl;
		std::cout << t1.Next()->Next()->Next()->Index() << std::endl;
		std::cout << std::endl;

		std::cout << t1.GetIndexed<0>() << std::endl;
		std::cout << t1.GetIndexed<1>() << std::endl;
		std::cout << t1.GetIndexed<2>() << std::endl;
		std::cout << t1.GetIndexed<3>() << std::endl;
		// std::cout << t1.GetIndexed<4>() << std::endl; // compile time error
		std::cout << std::endl;

		return 0;
}
