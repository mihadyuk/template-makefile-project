#include <assert.h>
#include <iostream>
#include "settings.h"

using namespace verifone::service::usbcomm;

static std::string xmlNodeTypeToString(int nodeType)
{
	switch (nodeType)
	{
	case XML_READER_TYPE_NONE:
		return "XML_READER_TYPE_NONE";

	case XML_READER_TYPE_ELEMENT:
		return "XML_READER_TYPE_ELEMENT";

	case XML_READER_TYPE_ATTRIBUTE:
		return "XML_READER_TYPE_ATTRIBUTE";

	case XML_READER_TYPE_TEXT:
		return "XML_READER_TYPE_TEXT";

	case XML_READER_TYPE_CDATA:
		return "XML_READER_TYPE_CDATA";

	case XML_READER_TYPE_ENTITY_REFERENCE:
		return "XML_READER_TYPE_ENTITY_REFERENCE";

	case XML_READER_TYPE_ENTITY:
		return "XML_READER_TYPE_ENTITY";

	case XML_READER_TYPE_PROCESSING_INSTRUCTION:
		return "XML_READER_TYPE_PROCESSING_INSTRUCTION";

	case XML_READER_TYPE_COMMENT:
		return "XML_READER_TYPE_COMMENT";

	case XML_READER_TYPE_DOCUMENT:
		return "XML_READER_TYPE_DOCUMENT";

	case XML_READER_TYPE_DOCUMENT_TYPE:
		return "XML_READER_TYPE_DOCUMENT_TYPE";

	case XML_READER_TYPE_DOCUMENT_FRAGMENT:
		return "XML_READER_TYPE_DOCUMENT_FRAGMENT";

	case XML_READER_TYPE_NOTATION:
		return "XML_READER_TYPE_NOTATION";

	case XML_READER_TYPE_WHITESPACE:
		return "XML_READER_TYPE_WHITESPACE";

	case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
		return "XML_READER_TYPE_SIGNIFICANT_WHITESPACE";

	case XML_READER_TYPE_END_ELEMENT:
		return "XML_READER_TYPE_END_ELEMENT";

	case XML_READER_TYPE_END_ENTITY:
		return "XML_READER_TYPE_END_ENTITY";

	case XML_READER_TYPE_XML_DECLARATION:
		return "XML_READER_TYPE_XML_DECLARATION";

	default:
		return "XML_UNDEFINED_READER_TYPE";
	}
}

static void dumpXml(const std::string fileName)
{
	xmlTextReaderPtr reader;
	int ret;

	reader = xmlNewTextReaderFilename(fileName.c_str());
	if (reader != nullptr)
	{
		ret = xmlTextReaderRead(reader);
		while (ret == 1)
		{
			xmlChar *name = xmlTextReaderName(reader);
			xmlChar *value = xmlTextReaderValue(reader);
			printf("depth: %d, nodeType: \"%s\", name: \"%s\", isEmpty: %d, hasAttr: %d, hasValue: %d, value: \"%s\"\n",
						xmlTextReaderDepth(reader),
						xmlNodeTypeToString(xmlTextReaderNodeType(reader)).c_str(),
						name,
						xmlTextReaderIsEmptyElement(reader),
						xmlTextReaderHasAttributes(reader),
						xmlTextReaderHasValue(reader),
						value);
			xmlFree(name);
			xmlFree(value);
			ret = xmlTextReaderRead(reader);
		}
		xmlFreeTextReader(reader);
	}
}

int main(int argc, char *argv[]) {

  std::cout << "template makefile project \r\n";

  //dumpXml("test.xml");
  Settings &settings = Settings::instance();
  settings.open("test.xml");

  UsbParameters usbParams 			= settings.usbParameters();
  IPParameters ipParameters 		= settings.ipParameters();
  SerialParameters serialParameters = settings.serialParameters();
  return 0;
}


