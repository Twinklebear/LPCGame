#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <string>
#include <fstream>

/*
*	A simple class to help with debugging, will print 
*	string data passed to it to a desired text file
*/
class Debugger{
public:
	//Debugger();
	//open file, filename
	//Debugger(std::string fileName);
	//close file
	~Debugger();
	//For static version of class
	static void Init();
	static void Close();
	//write data output to file
	static void Write(std::string output);
	//write a string and int/float/double
	static void Write(std::string output, double num);

private:
	//filename
	static std::string mFileName;
	//the file output stream
	static std::ofstream mFileStream;
};

#endif