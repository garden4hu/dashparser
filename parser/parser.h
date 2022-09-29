#pragma once

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
