#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
#include <assert.h>

void testStringFunc1()
{
	using namespace qh;
	string s;
	assert(s.size() == 0);
	assert(s[0] == 0);
	assert(s.c_str() == 0);
	
}

void testStringFunc2()
{
	using namespace qh;
	string s ("A character sequence");
	assert(s.size() == 20);
	assert(*(s.c_str()) == 'A');
	assert(*(s[2]) == 'c');
}

void testStringFunc3()
{
	using namespace qh;
	string s0 ("A character sequence");
	string s = s0;
	assert(s.size() == 20);
	assert(*(s.c_str()) == 'A');
	assert(*(s[2]) == 'c');
}

void testStringFunc4()
{
	using namespace qh;
	string s0 ("A character sequence");
	string s(s0);
	assert(s.size() == 20);
	assert(*(s.c_str()) == 'A');
	assert(*(s[2]) == 'c');
}

void testStringFunc5()
{
	using namespace qh;
	string s ("A character sequence", 6);
	assert(s.size() == 6);
	assert(*(s.c_str()) == 'A');
	assert(*(s[2]) == 'c');
}



int main(int argc, char* argv[])
{
	//TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
	//TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。

	testStringFunc1();
	testStringFunc2();
	testStringFunc3();
	testStringFunc4();
	testStringFunc5();


#ifdef WIN32
	system("pause");
#endif

	return 0;
}

