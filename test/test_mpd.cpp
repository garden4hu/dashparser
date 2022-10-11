#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "../parser/dash.h"
#include "../parser/utils/prtime.h"
#include "status.h"
#include "../parser/utils/dash_time.h"
using std::cout;
using std::endl;

namespace {
std::vector<char> ReadMPD(const char* path, int& out_size) {
    std::vector<char> ret;
    do {
        FILE* fp = fopen(path, "rb+");
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
    auto code = dash->open("https://google.com/", &data[0],len);
    if (code != StatusCode::kOk){
        FAIL();
    }
}


TEST(dash_parser, test_parse_date){
    std::string my_date = "PT298.000S";
    PRTime t = 0;
    auto result = PR_ParseTimeString(my_date.c_str(),1,&t);
    cout << t << endl;
    assert(t != 0);
}

TEST(dash_parser, test_parse_duration){
    std::string duration_01 = "P2DT4M0.10S";
    auto delta_01  = ParseDurationString(duration_01);

    GTEST_ASSERT_FALSE(!delta_01.has_value());
    cout << delta_01.value() << endl;
}

TEST(dash_parser, test_xml_doc){
    auto dash = std::make_unique<Dash>();
    int len = 0;
    auto data = ReadMPD("D:\\Github\\dashparser\\test\\assets\\vod_segment_base.mpd",len);
    if (data.empty()) {
        FAIL();
    }
    auto doc = initXmlDoc(&data[0],data.size());
    bool found = false;
    auto item    = doc->children;
    cout <<  FindChildNode(doc->children,"MPD") << endl;
}
}  // namespace