#include "ini_parser.h"

#include <assert.h>

void test1()
{
	const char* ini_text= "a=1\nb=2\n"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "1");

	std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "");
}

void test2()
{
	const char* ini_text= "a=1||b=2||c=3"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "1");

	std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "3");
}

void test3()
{
	const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
	qh::INIParser parser;
	if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
		assert(false);
	}

	const std::string& a = parser.Get("a", NULL);
	assert(a == "1");

	std::string b = parser.Get("b", NULL);
	assert(b == "2");

	const std::string& c = parser.Get("c", NULL);
	assert(c == "3");
}

void test4()
{
	const char* ini_text= "||a||b:2||c:3||"; 
	qh::INIParser parser;
	if (parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
		assert(false);
	}
}

void test5()
{
	const char* ini_text= "||a=1=2||b:2||c:3||"; 
	qh::INIParser parser;
	if (parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
		assert(false);
	}
}

void testIniFile1()
{
	qh::INIParser parser;
	std::string ini_file_path("test.ini");
	if (!parser.Parse(ini_file_path))
	{
		assert(false);
	}

	const std::string& Key1_1 = parser.Get("Sect1", "Key1_1",NULL);
	assert(Key1_1 == "hello");

	const std::string& Ket2_2 = parser.Get("Sect2", "Ket2_2",NULL);
	assert(Ket2_2 == "am");

	const std::string& Key3_3 = parser.Get("Sect3", "Key3_3",NULL);
	assert(Key3_3 == "cheng");

}

/****-----> add by zhaojincheng in 20140817 <-----****/


int main(int argc, char* argv[])
{
	//TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好

	test1();
	test2();
	test3();

	/****-----> add by zhaojincheng in 20140817 <-----****/
	test4();
	test5();
	testIniFile1();

	return 0;
}


