#pragma once
#include <string>
#include <string_view>

#include "base/strings.h"
#include "url_parser.h"
namespace dash {

class URL {
  public:
    URL(std::string url) : url_(std::move(url)) {
        TrimPrefixAll(&url_, ' ');
        TrimSuffixAll(&url_, ' ');
        http_parser_url_init(&parser_url_);
        parsed_ok = http_parser_parse_url(url_.c_str(), url_.length(), 0, &parser_url_) == 0;
    }
    [[nodiscard]] inline bool IsParsedOK() const { return parsed_ok; }
    [[nodiscard]] inline bool IsAbsoluteUrl() const { return !Host().empty(); }
    [[nodiscard]] inline bool HasPath() const { return parser_url_.field_data[3].len != 0; }
    [[nodiscard]] inline bool HasQueries() const { return parser_url_.field_data[4].len != 0; }
    [[nodiscard]] inline std::string Schema() const {
        return url_.substr(parser_url_.field_data[0].off, parser_url_.field_data[0].len);
    }
    [[nodiscard]] inline std::string Host() const {
        return url_.substr(parser_url_.field_data[1].off, parser_url_.field_data[1].len);
    }
    [[nodiscard]] inline std::string Port() const {
        return url_.substr(parser_url_.field_data[2].off, parser_url_.field_data[2].len);
    }
    [[nodiscard]] inline std::string Path() const {
        return url_.substr(parser_url_.field_data[3].off, parser_url_.field_data[3].len);
    }
    [[nodiscard]] inline std::string Query() const {
        return url_.substr(parser_url_.field_data[4].off, parser_url_.field_data[4].len);
    }

    /**
     * @brief AppendPath will append the extra path @param path into current url.
     * @return the new url
     * @note path should not contains whitespace.
     * */
    [[nodiscard]] std::string AppendPath(std::string_view path) {
        std::string ret;
        do {
            if (path.empty()) {
                ret = url_;
                break ;
            }
            auto url_view  = TrimSuffixAll(url_, '/');
            auto path_view = TrimPrefixAll(path, '/');
            path_view      = TrimSuffixAll(path_view, '/');
            ret.reserve(url_.size() + path_view.size() + 3);
            ret.append(url_view.data(), url_view.size());
            if (!path_view.empty()) {
                ret.append("/");
                ret.append(path_view.data(), path_view.size());
            }
            if (HasQueries()) {
                ret.append("?");
                ret.append(Query());
            }
        } while (false);
        return ret;
    }

    /**
     * @brief AppendQuery will return the new url with the added query
     * */
    [[nodiscard]] std::string AppendQuery(std::string_view query) {
        std::string ret;
        do {
            if (query.empty()) {
                ret = url_;
                break;
            }
            if (HasQueries()) {
                if (*(url_.rbegin()) == '&') {
                    ret = url_ + std::string(query.data(), query.length());
                } else {
                    ret = url_ + "&" + std::string(query.data(), query.length());
                }
            } else {
                if (*(url_.rbegin()) == '?') {
                    ret = url_ + std::string(query.data(), query.length());
                } else {
                    ret = url_ + "?" + std::string(query.data(), query.length());
                }
            };
        } while (false);
        return ret;
    }

  private:
    std::string url_;
    bool parsed_ok = false;
    http_parser_url parser_url_;
};

}  // namespace dash