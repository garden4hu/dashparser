#include "dash_xml.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <absl/strings/str_split.h>
#include <optional>


namespace dash
{
	std::optional<DocSmartPtr> initXMLDoc(const char* src, int length)
	{
		auto doc = xmlReadMemory(src, length, nullptr, "UTF-8", 0);
		return doc ? std::optional<DocSmartPtr>{DocSmartPtr(doc)} : std::nullopt;
	}
}
