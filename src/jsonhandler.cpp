#include <string>
#include <fstream>
#include <stdexcept>
#include "../externals/json/json.h"
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
Json::Value JsonHandler::ReadFile() const {
    std::ifstream fileIn(mFile.c_str(), std::ifstream::binary);
    if (fileIn){
        Json::Reader reader;
        Json::Value root;
        if (reader.parse(fileIn, root, false)){
            fileIn.close();
            return root;
        }
        else {
            fileIn.close();
            throw std::runtime_error("JsonHandler: Failed to parse: " + mFile);
        }
    }
    else
        throw std::runtime_error("JsonHandler: Failed to find: " + mFile);
}
void JsonHandler::WriteFile(const Json::Value &data) const {
    std::ofstream fileOut(mFile.c_str());
    Json::StyledWriter writer;
    std::string strData = writer.write(data);
    fileOut << strData << std::endl;
    fileOut.close();
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