#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../parser/dash.h"
#include "status.h"
using std::cout;
using std::endl;

namespace {
std::vector<char> ReadMPD(const char* path, int& out_size) {
    std::vector<char> ret;
    do {
        FILE* fp = fopen(path, "r");
        if (!fp) {
            break ;
        }
        fseek(fp, 0, SEEK_END);
        auto mpd_size = ftell(fp);
        if (mpd_size <= 0) {
            break ;
        }
        fseek(fp, 0, SEEK_SET);
        ret.resize(mpd_size);
        auto real_read = fread(&ret[0], 1, mpd_size, fp);
        if (real_read != mpd_size) {
            return ret;
        }
        out_size = real_read;
        fclose(fp);
    } while (false);
    return  ret;
}

}  // namespace

using namespace dash;
namespace {
TEST(dash_parser, mpd_parse) {
    auto dash = std::make_unique<Dash>();
    int len = 0;
    auto data = ReadMPD("../test/assets/vod_segment_base.mpd",len);
    if (data.empty()) {
        FAIL();
    }
    for(auto i : data){
        cout << i;
    }
    auto code = dash->open("https://google.com/", &data[0],len);
    if (code != StatusCode::kOk){
        FAIL();
    }
}
}  // namespace