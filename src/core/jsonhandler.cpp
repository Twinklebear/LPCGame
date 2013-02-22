#include <string>
#include <fstream>
#include <stdexcept>
#include "external/json/json.h"
#include "debug.h"
#include "jsonhandler.h"

JsonHandler::JsonHandler(const std::string file) : mFile(""){
    if (!JsonFile(file)){
        size_t extensionPos = file.find_last_of('.');
	    mFile = file.substr(0, extensionPos + 1) + "json";
    }
    else
        mFile = file;
}
JsonHandler::JsonHandler() : mFile(""){
}
JsonHandler::~JsonHandler(){
}
Json::Value JsonHandler::Read() const {
    std::ifstream fileIn(mFile.c_str(), std::ifstream::binary);
    Json::Value root;
    if (fileIn.is_open()){
        Json::Reader reader;
        if (!reader.parse(fileIn, root, false))
            Debug::Log("JsonHandler: Failed to parse: " + mFile);
    }
    else
        Debug::Log("JsonHandler: Failed to find: " + mFile);

    return root;
}
void JsonHandler::Write(const Json::Value &data) const {
    if (mFile == ""){
        Debug::Log("JsonHandler: Ignoring write to blank filename");
        return;
    }
    std::ofstream fileOut(mFile.c_str());
    Json::StyledWriter writer;
    std::string strData = writer.write(data);
    fileOut << strData << std::endl;
}
void JsonHandler::SetFile(const std::string file){
    mFile = file;
}
std::string JsonHandler::File() const {
    return mFile;
}
bool JsonHandler::JsonFile(const std::string &file) const {
    size_t extPos = file.find_last_of('.');
    if (file.substr(extPos + 1, file.size() - 1) == "json")
        return true;
    return false;
}