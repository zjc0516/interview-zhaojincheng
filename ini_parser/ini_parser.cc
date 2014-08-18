#include "ini_parser.h"
#include <fstream>


namespace qh
{
	//-----> add by zhaojincheng in 20140817 <-----//
	//去掉字符串左边空格符及tab符
	extern inline std::string& ltrim( std::string &s )
	{
		s = s.substr( s.find_first_not_of("\t ") );
		return s;
	}
	//去掉字符串右边空格符及tab符
	extern inline std::string& rtrim( std::string &s )
	{
		s = s.substr( 0, s.find_last_not_of("\t ")+1 );
		return s;
	}
	//去掉字符串左右两边空格符及tab符
	extern inline std::string& trim( std::string &s )
	{
		return ltrim(rtrim(s));
	}

	INIParser::INIParser()
	{
	}

	INIParser::~INIParser()
	{
	}

	bool INIParser::Parse( const std::string& ini_file_path )
	{
		std::ifstream fs_ini_file(ini_file_path.c_str(), std::ios_base::in);

		if (!fs_ini_file)
		{
			return false;
		}

		// search section
		std::string strLine ;
		std::string strSection;

		while (getline(fs_ini_file, strLine))
		{
			// section found
			trim(strLine);

			if (strLine.size() ==0)
			{
				continue;
			}
			else if (strLine[0] == ';')
			{
				continue;
			}
			else if (strLine[0] == '[')
			{
				std::string::size_type pos= strLine.find("]", 0);
				if (pos == std::string::npos)
				{
					ini_file_map.clear();
					return false;
				}
				strSection = strLine.substr(1, pos-1);				
			}
			else
			{
				if (strSection.size())
				{
					std::string s_key, s_value;
					std::string key_value_seperator("=");
					strLine += key_value_seperator;

					size_t pre_pos = 0;
					size_t cur_pos = strLine.find(key_value_seperator, pre_pos);
					s_key = strLine.substr(pre_pos, cur_pos-pre_pos);
					trim(s_key);

					pre_pos = cur_pos + key_value_seperator.size();
					cur_pos = strLine.find(key_value_seperator, pre_pos);
					s_value = strLine.substr(pre_pos, cur_pos-pre_pos);
					trim(s_value);

					ini_file_map[strSection][s_key] = s_value;
				}
			}
		}
		return true;

	}

	bool INIParser::Parse( const char* ini_data, size_t ini_data_len, const std::string& line_seperator /*= "\n"*/, const std::string& key_value_seperator /*= "="*/ )
	{
		std::string::size_type pos ;
		std::string str(ini_data);
		str += line_seperator;
		std::string sub_str;
		for(size_t i=0; i<str.size(); i++)
		{
			pos = str.find(line_seperator, i);
			if (pos <str.size())
			{
				sub_str = str.substr(i, pos-i);
				i = pos + line_seperator.size() -1;

				if (sub_str.size())
				{
					std::string s_key, s_value;
					sub_str += key_value_seperator;
					size_t pre_pos = 0;
					size_t cur_pos = sub_str.find(key_value_seperator, pre_pos);
					s_key = sub_str.substr(pre_pos, cur_pos-pre_pos);

					pre_pos = cur_pos + key_value_seperator.size();
					cur_pos = sub_str.find(key_value_seperator, pre_pos);
					if (cur_pos != std::string::npos)
					{
						s_value = sub_str.substr(pre_pos, cur_pos-pre_pos);
					}
					else
					{
						/**
						* case 1: 
						*   ini_text= "||a||"; 
						*  key  没有对应值，排除
						*/
						ini_data_map.clear();
						return false;
					}

					if (sub_str.find(key_value_seperator, cur_pos+key_value_seperator.size()) != std::string::npos)
					{
						/**
						* case 1: 
						*   ini_text= "||a=1=2||"; 
						*  同一个key对应多个值，排除
						*/
						ini_data_map.clear();
						return false;
					}

					ini_data_map[s_key] = s_value;
				}
			}
		}
		return true;
	}

	const std::string& INIParser::Get( const std::string& key, bool* found )
	{
		if (ini_data_map.count(key) < 0)
		{
			if (found)
			{
				*found = false;
			}
			return NULL;
		}	
		if (found)
		{
			*found = true;
		}
		return ini_data_map[key];

	}

	const std::string& INIParser::Get( const std::string& section, const std::string& key, bool* found )
	{
		if (ini_file_map.count(section))
		{
			if (ini_file_map[section].count(key))
			{
				if (found)
				{
					*found = true;
				}
				return ini_file_map[section][key];
			}
			
		}
		if (found)
		{
			*found = false;
		}
		return NULL;		

	}



}