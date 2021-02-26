#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/schema.h>

using namespace rapidjson;

class RemoteSchemaProvider : public IRemoteSchemaDocumentProvider {
public:
	virtual const SchemaDocument* GetRemoteDocument(const char* uri, SizeType length) {
		(void)length;

		// stream
		std::ifstream refFile("schemas/" + std::string(uri));
		IStreamWrapper refWrapper(refFile);

		// document
		Document refDoc;
		refDoc.ParseStream(refWrapper);
		if (refDoc.HasParseError()) {
			std::cout << refDoc.GetParseError();
		}

		// provider schema document
		SchemaDocument* providerDoc = new SchemaDocument(refDoc);
		return providerDoc;
	}
};
