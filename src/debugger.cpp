#include <string>
#include <fstream>
#include "debugger.h"

//For static version of class
std::string Debugger::mFileName;
std::ofstream Debugger::mFileStream;

/*
Debugger::Debugger(){}
Debugger::Debugger(std::string fileName){
	mFileName = fileName;
	mFileStream.open(mFileName.c_str());
}
*/
Debugger::~Debugger(){
	//mFileStream.close();
	Close();
}
void Debugger::Init(){
	mFileName = "dbgOut.txt";
	mFileStream.open(mFileName.c_str());
}
void Debugger::Close(){
	mFileStream.close();
}
void Debugger::Write(std::string output){
	mFileStream << output << std::endl;
}
void Debugger::Write(std::string output, double num){
	mFileStream << output << " " << num << std::endl;
}