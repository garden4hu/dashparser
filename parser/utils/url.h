#pragma once
#include <string>

#include "url_parser.h"
namespace dash {
class URL {
  public:
    URL(std::string url) : url_(url) { http_parser_url_init(&parser_url_);
        parsed_ok = http_parser_parse_url(url_.c_str(),url_.length(),0,&parser_url_) == 0 ? true : false;
    }
    bool ParsedOK(){return parsed_ok;}
    std::string Schema() {
        return url_.substr(parser_url_.field_data[0].off, parser_url_.field_data[0].len);
    }
    std::string Host() {
        return url_.substr(parser_url_.field_data[1].off, parser_url_.field_data[1].len);
    }
    std::string Port() {
        return url_.substr(parser_url_.field_data[2].off, parser_url_.field_data[2].len);
    }
    std::string Path() {
        return url_.substr(parser_url_.field_data[3].off, parser_url_.field_data[3].len);
    }
    std::string Query() {
        return url_.substr(parser_url_.field_data[4].off, parser_url_.field_data[4].len);
    }

  private:
    std::string url_;
    bool parsed_ok = false;
    http_parser_url parser_url_;
};

}  // namespace dash