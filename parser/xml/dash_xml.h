#ifndef DASH_PARSER_XML_H_
#define DASH_PARSER_XML_H_


#include <optional>
#include <string>
#include <fmt/format.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <absl/types/optional.h>
#include "xml_smart_ptr.h"

namespace dash
{

	using DocSmartPtr = CSmartPtr<xmlDoc, xmlFreeDoc>;

	using NodeSmartPtr = CSmartPtr<xmlNode, xmlFreeNode>;

	std::optional<DocSmartPtr> initXMLDoc(const char* src, int length);
	
	class XMLNode
	{
	public:
		XMLNode() = default;
		bool init() { return true; }
	private:
		NodeSmartPtr node;
	};
}

#endif // !DASH_PARSER_XML_H_
