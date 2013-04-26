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
		Tuple<int, char, std::string> t1(1, '!', std::string("test"));

		int tmp1;
		char tmp2;
		std::string tmp3;

		t1.Get(tmp1, tmp2, tmp3);

		std::cout << tmp1 << std::endl;
		std::cout << tmp2 << std::endl;
		std::cout << tmp3 << std::endl;

		TupleData<int, char, TupleDummyType> t2(1 , 'a', 3);

		std::cout << t2.Get();

		return 0;
}
