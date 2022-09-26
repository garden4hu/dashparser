#ifndef DASH_XML_SMART_PTR_H_
#define DASH_XML_SMART_PTR_H_


#include "base/c_smart_ptr.h"
#include <libxml/tree.h>
#include <libxml/xmlschemas.h>


namespace dash
{
	struct XmlDeleter
	{
		void operator()(xmlDocPtr p) const { xmlFreeDoc(p); }
		void operator()(xmlNodePtr p) const { xmlFreeNode(p); }
		void operator()(xmlSchemaPtr p) const { xmlSchemaFree(p); }
		void operator()(xmlAttributeTablePtr p) const { xmlFreeAttributeTable(p); }
	};

	// template <typename xmlType>
	// using xmlSmartPtr = std::unique_ptr<xmlType, XmlDeleter>;


}




#endif // !DASH_XML_SMART_PTR_H_