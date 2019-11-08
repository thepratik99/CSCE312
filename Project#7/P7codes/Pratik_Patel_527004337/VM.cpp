#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void parseTheFile(ifstream&, ofstream&);
void parseArithmatic(ofstream&, vector<string>, int&);
void parseAddSubAndOr(ofstream&, string);
void parseNgNot(ofstream&, string);
void parseEqGtLt(ofstream&, string, const int&);
void parsePushOrPop(ofstream&, vector<string>);
void parsePushConstant(ofstream&, string);
void parsePush(ofstream&, string, string, bool);
void parsePop(ofstream&, string, string, bool);

int main(int argc, char const *argv[])
{
	string filename = argv[1];
	ifstream inFile;
	inFile.open(filename);

	ofstream outFile;
	outFile.open(filename.substr(0, (filename.length() - 2)) + "asm");

	parseTheFile(inFile, outFile);

	return 0;
}

void parseTheFile(ifstream& inFile, ofstream& outFile)
{
	string line;
	int counterForLabels = 0;

	while(getline(inFile, line))
	{
		if(line.at(0) == 13 || (line.at(0) == '/' && line.at(1) == '/'))
			continue;
		else
		{
			string buffer;
			istringstream ss(line);
			vector<string> words;

			while(ss >> buffer)
				words.push_back(buffer);

			if(words.size() <= 1)
				parseArithmatic(outFile, words, counterForLabels);
			else
				parsePushOrPop(outFile, words);
		}		
	}
}

void parseArithmatic(ofstream& outFile, vector<string> words, int& counterForLabels)
{
	if(words.at(0) == "add")
		parseAddSubAndOr(outFile, "+");
	else if(words.at(0) == "sub")
		parseAddSubAndOr(outFile, "-");
	else if(words.at(0) == "and")
		parseAddSubAndOr(outFile, "&");
	else if(words.at(0) == "or")
		parseAddSubAndOr(outFile, "|");
	else if(words.at(0) == "neg")
		parseNgNot(outFile, "-");
	else if(words.at(0) == "not")
		parseNgNot(outFile, "!");
	else if(words.at(0) == "eq")
	{
		++counterForLabels;
		parseEqGtLt(outFile, "JEQ", counterForLabels);
	}
	else if(words.at(0) == "gt")
	{
		++counterForLabels;
		parseEqGtLt(outFile, "JGT", counterForLabels);
	}
	else if(words.at(0) == "lt")
	{
		++counterForLabels;
		parseEqGtLt(outFile, "JLT", counterForLabels);
	}
	else
	{
		cout << "Seems like there is an error in the source VM code." << endl;
		return ;
	}
}

void parseAddSubAndOr(ofstream& outFile, string command)
{
	outFile << "@SP" << endl;
	outFile << "AM=M-1" << endl;
	outFile << "D=M" << endl;
	outFile << "A=A-1" << endl;
	if(command == "-")
	{
		outFile << "M=M-D" << endl;
	}
	else
	{
		outFile << "M=D" << command << "M" << endl;
	}
}

void parseNgNot(ofstream& outFile, string command)
{
	outFile << "@SP" << endl;
	outFile << "A=M-1" << endl;
	outFile << "D=M" << endl;
	outFile << "M=" << command << "D" << endl;
}

void parseEqGtLt(ofstream& outFile, string command, const int& counterForLabels)
{
	outFile << "@SP" << endl;
	outFile << "AM=M-1" << endl;
	outFile << "D=M" << endl;
	outFile << "A=A-1" << endl;
	outFile << "D=M-D" << endl;
	outFile << "@NEXT" << to_string(counterForLabels) << endl;
	outFile << "D;" << command << endl;
	outFile << "@SP" << endl;
	outFile << "A=M-1" << endl;
	outFile << "M=0" << endl;
	outFile << "@VAR" << to_string(counterForLabels) << endl;
	outFile << "0;JMP" << endl;
	outFile << "(NEXT" << to_string(counterForLabels) << ")" << endl;
	outFile << "@SP" << endl;
	outFile << "A=M-1" << endl;
	outFile << "M=-1" << endl;
	outFile << "(VAR" << to_string(counterForLabels) << ")" << endl;
}

void parsePushOrPop(ofstream& outFile, vector<string> words)
{
	bool isTempOrStatic = false;
	if(words.at(0) == "push")
	{
		if(words.at(1) == "constant")
			parsePushConstant(outFile, words.at(2));
		else if(words.at(1) == "local")
			parsePush(outFile, "LCL", words.at(2), isTempOrStatic);
		else if(words.at(1) == "argument")
			parsePush(outFile, "ARG", words.at(2), isTempOrStatic);
		else if(words.at(1) == "temp")
		{
			isTempOrStatic = true;
			parsePush(outFile, "R5", words.at(2), isTempOrStatic);
		}
		else if(words.at(1) == "static")
		{
			isTempOrStatic = true;
			parsePush(outFile, "16", words.at(2), isTempOrStatic);
		}
		else if(words.at(1) == "this")
			parsePush(outFile, "THIS", words.at(2), isTempOrStatic);
		else if(words.at(1) == "that")
			parsePush(outFile, "THAT", words.at(2), isTempOrStatic);
		else if(words.at(1) == "pointer")
		{
			isTempOrStatic = true;
			parsePush(outFile, "3", words.at(2), isTempOrStatic);
		}
	}

	else if(words.at(0) == "pop")
	{
		if(words.at(1) == "local")
			parsePop(outFile, "LCL", words.at(2), isTempOrStatic);
		else if(words.at(1) == "argument")
			parsePop(outFile, "ARG", words.at(2), isTempOrStatic);
		else if(words.at(1) == "temp")
		{
			isTempOrStatic = true;
			parsePop(outFile, "5", words.at(2), isTempOrStatic);
		}
		else if(words.at(1) == "static")
		{
			isTempOrStatic = true;
			parsePop(outFile, "16", words.at(2), isTempOrStatic);
		}
		else if(words.at(1) == "this")
			parsePop(outFile, "THIS", words.at(2), isTempOrStatic);
		else if(words.at(1) == "that")
			parsePop(outFile, "THAT", words.at(2), isTempOrStatic);
		else if(words.at(1) == "pointer")
		{
			isTempOrStatic = true;
			parsePop(outFile, "3", words.at(2), isTempOrStatic);
		}
	}
}

void parsePushConstant(ofstream& outFile, string value)
{
	outFile << "@" << value << endl;
	outFile << "D=A" << endl;
	outFile << "@SP" << endl;
	outFile << "AM=M+1" << endl;
	outFile << "A=A-1" << endl;
	outFile << "M=D" << endl;
}

void parsePush(ofstream& outFile, string command, string value, bool isTempOrStatic)
{
	outFile << "@" << command << endl;
	if(isTempOrStatic)
	{
		outFile << "D=A" << endl;
	}
	else 
	{
		outFile << "A=M" << endl;
		outFile << "D=A" << endl;
	}
	outFile << "@" << value << endl;
	outFile << "A=D+A" << endl;
	outFile << "D=M" << endl;
	outFile << "@SP" << endl;
	outFile << "AM=M+1" << endl;
	outFile << "A=A-1" << endl;
	outFile << "M=D" << endl;
}

void parsePop(ofstream& outFile, string command, string value, bool isTempOrStatic)
{
	outFile << "@" << command << endl;
	outFile << "D=" ;
	if(isTempOrStatic)
	{
		outFile << "A" << endl;
	}
	else 
	{
		outFile << "M" << endl;
	}
	outFile << "@" << value << endl;
	outFile << "D=D+A" << endl;
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	outFile << "@SP" << endl;
	outFile << "AM=M-1" << endl;
	outFile << "D=M" << endl;
	outFile << "@R13" << endl;
	outFile << "A=M" << endl;
	outFile << "M=D" << endl;
}