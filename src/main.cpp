#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <boost/filesystem.hpp>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/pointer.h>
#include <rapidjson/schema.h>
#include <rapidjson/stringbuffer.h>

#include "RemoteSchemaProvider.cpp"

int main() {
	// schema
	std::string schemaPath("schemas/base_schema.json");
	std::cout << "Reading schema file " << schemaPath << std::endl;
	std::ifstream schema(schemaPath);
	rapidjson::IStreamWrapper schemaWrapper(schema);
	rapidjson::Document schemaDoc;
	schemaDoc.ParseStream(schemaWrapper);
	if (schemaDoc.HasParseError()) {
		std::cout << "error" << std::endl;
		std::cout << schemaDoc.GetParseError();
		return EXIT_FAILURE;
	}
	RemoteSchemaProvider provider;
	rapidjson::SchemaDocument sd(schemaDoc, &provider);

	for (auto& file : boost::filesystem::directory_iterator("data")) {
		// file document
		std::cout << std::endl << "Found json file: " << file.path() << std::endl;
		std::ifstream testfile(file.path().c_str());
		rapidjson::IStreamWrapper fileWrapper(testfile);
		rapidjson::Document f;
		f.ParseStream(fileWrapper);
		if (f.HasParseError()) {
			std::cout << f.GetParseError();
			return EXIT_FAILURE;
		}

		// validation
		rapidjson::SchemaValidator validator(sd);
		if (!f.Accept(validator)) {
			rapidjson::StringBuffer sb;
			std::string property, jsondoc, jsonschema;
			validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
			jsonschema = sb.GetString();
			property = validator.GetInvalidSchemaKeyword();
			sb.Clear();
			validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
			jsondoc = sb.GetString();
			std::cout << "Schema violation: " << property << ", violating element: " << jsondoc << std::endl;
		} else {
			std::cout << "No violations detected." << std::endl;
		}
	}
	
	return EXIT_SUCCESS;
}
