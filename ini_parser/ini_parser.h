#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <string>
#include <map>

namespace qh
{
	/****-----> add by zhaojincheng in 20140817 <-----****/

	extern std::string& ltrim( std::string &s );
	extern std::string& rtrim( std::string &s );
	extern std::string& trim( std::string &s );



	class INIParser
	{
	public:
		INIParser();
		~INIParser();

		//! \brief 解析一个磁盘上的INI文件
		//! \param[in] - const std::string & ini_file_path
		//! \return - bool
		bool Parse(const std::string& ini_file_path);

		//! \brief 解析一段形如INI格式的内存数据。
		//!   例如：ini_data="a:1||b:2||c:3"
		//!         调用<code>Parse(ini_data, ini_data_len, "||", ":")</code>即可解析出这段数据。
		//!         解析完毕之后 
		//!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
		//! \param[in] - const char * ini_data
		//! \param[in] - size_t ini_data
		//! \param[in] - const std::string & line_seperator
		//! \param[in] - const std::string & key_value_seperator
		//! \return - bool
		bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

		//! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
		//! \param[in] - const std::string & key
		//! \param[in] - bool * found - 输出参数，true表明找到这个key
		//! \return - const std::string& - 返回的具体key对应的value
		const std::string& Get(const std::string& key, bool* found);

		const std::string& Get(const std::string& section, const std::string& key, bool* found);

	private:

		/****-----> add by zhaojincheng in 20140817 <-----****/
		std::map<std::string, std::string>  ini_data_map;                                   //内存数据
		std::map<std::string, std::map<std::string, std::string> > ini_file_map;   //ini文件解析数据
	};
}

#endif

