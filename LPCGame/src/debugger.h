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
	Debugger();
	//open file, filename
	Debugger(std::string fileName);
	//close file
	~Debugger();
	//write data output to file
	void Write(std::string output);
	//write a string and int/float/double
	void Write(std::string output, double num);

private:
	//filename
	std::string mFileName;
	//the file output stream
	std::ofstream mFileStream;
};

#endif