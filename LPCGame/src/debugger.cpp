#include <string>
#include <sstream>
#include "debugger.h"

Debugger::Debugger(){}
Debugger::Debugger(std::string fileName){
	mFileName = fileName;
	mFileStream.open(mFileName.c_str());
}
Debugger::~Debugger(){
	mFileStream.close();
}
void Debugger::Write(std::string output){
	mFileStream << output << std::endl;
}
void Debugger::Write(std::string output, double num){
	std::stringstream sstream;
	sstream << num;
	mFileStream << output << " " << sstream.str() << std::endl;
}