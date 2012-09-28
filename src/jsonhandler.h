#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <string>
#include "../externals/json/json.h"

///A simple wrapper around JSON file reading and writing functionality
/**
*  Acts to simplify JSON file reading and writing tasks
*/
class JsonHandler {
public:
    /**
    *  Construct the JsonHandler and give it a filename to work with
    *  if the filename doesn't end in .json it will be assumed a config json
    *  file exists under the same path & name with the .json extension
    *  @param file The filename the JsonHandler is to read/write too
    */
    JsonHandler(const std::string file);
    JsonHandler();
    ~JsonHandler();
    /**
    *  Read JSON formatted data from  mFile and return it
    *  @return the Json::Value containing the file data
    *  @throw runtime_error File to find if file not found
    *  @throw runtime_error Failed to parse if file couldn't be parsed as JSON
    */
    Json::Value ReadFile() const;
    /**
    *  Write data from a Json::Value to a JSON formatted file named mFile
    *  @param data The Json::Value of data to write
    */
    void WriteFile(const Json::Value &data) const;
    ///Set the filename to file
    void SetFile(const std::string file);
    ///Get the filename
    std::string File() const;

private:
    /**
    *  Check if a file extension ends in .json
    *  @param file The file to check
    *  @return True if it's a json file
    */
    bool JsonFile(const std::string &file) const;

private:
    ///The file to read/write from
    std::string mFile;
};

#endif