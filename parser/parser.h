#ifndef DASH_PARSER_INTERNAL_H_
#define  DASH_PARSER_INTERNAL_H_

#include <string>


namespace dash
{
	class Parser
	{
	public:
		Parser() = default;
		Parser(std::string& content):raw_content(content) {}
		Parser(const char* content) :raw_content(content){}
		~Parser() = default;
	private:
		std::string raw_content;
	};
}


#endif // !DASH_PARSER_INTERNAL_H_