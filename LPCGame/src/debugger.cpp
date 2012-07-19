#include <string>
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
	mFileStream << output << " " << num << std::endl;
}