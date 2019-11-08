//Project 6 CSCE 312
//Name: Pratik Patel
//UIN: 527004337
//Date: 04/09/2019

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

using namespace std;

void prePopulateSymbolTable(vector<string>&, vector<int>&);
void firstParse(ifstream&, ofstream&, vector<string>&, vector<int>&);
void secondParse(ifstream&, ofstream&, vector<string>&, vector<int>&, int&);
string parseAInstruction(string, vector<string>&, vector<int>&, int&);
string parseCInstruction(string);
string parseJump(string);
string parseDest(string);
string parseComp(string);

int main(int argc, char *argv[])
{
	//getting the file name
	string fileName;
	cout << "Enter the file name: " ;
	cin >> fileName;

	//opening a file into a file stream
	ifstream inFile;
	inFile.open(fileName);

	//checking if the file exists or not
	if(!inFile)
	{
		cout << "Could not find the file." << endl;
		return -1;
	}

	//opening an output file
	ofstream outFile;
	outFile.open(fileName.substr(0, (fileName.length() - 4)) + ".hack");

	//data structure for symbol table
	vector<string> variableNames;
	vector<int> values;
	int varibleCounter = 16;

	//pre populate the table
	prePopulateSymbolTable(variableNames, values);

	//first parse to handle labels
	firstParse(inFile, outFile, variableNames, values);

	//for second parse
	ifstream inFileForSecondParse;
	inFileForSecondParse.open(fileName);

	//checking if the file exists or not
	if(!inFileForSecondParse)
	{
		cout << "Could not find the file." << endl;
		return -1;
	}

	//second parse to convert asm to binary
	secondParse(inFileForSecondParse, outFile, variableNames, values, varibleCounter);
	
	return 0;
}

//pre populate the table
void prePopulateSymbolTable(vector<string>& variableNames, vector<int>& values)
{
	//for R0 to R15
	for(int i = 0; i < 16; ++i)
	{
		values.push_back(i);
		variableNames.push_back("R" + to_string(i));
	}

	//some pre defined values
	variableNames.push_back("KBD");
	values.push_back(24576);

	variableNames.push_back("SCREEN");
	values.push_back(16384);

	variableNames.push_back("SP");
	values.push_back(0);

	variableNames.push_back("LCL");
	values.push_back(1);

	variableNames.push_back("ARG");
	values.push_back(2);

	variableNames.push_back("THIS");
	values.push_back(3);

	variableNames.push_back("THAT");
	values.push_back(4);
}

//doing the first parse to handle labels
void firstParse(ifstream& inFile, ofstream& outFile, vector<string>& variableNames, vector<int>& values)
{
	//variables
	string line;
	int lineCounter = -1;

	//parse through the file
	while(getline(inFile, line))
	{
		//NULL line or a comment
		if(line.at(0) == 13 || (line.at(0) == '/' && line.at(1) == '/'))
			continue;

		//A Insrtuction - increase line counter
		else if(line.at(0) == '@')
			lineCounter++;

		//labels
		else if(line.at(0) == '(')
		{
			string labelName = "";
			int index = 1;

			//get the label
			while(line.at(index) != ')')
			{
				labelName += line.at(index);
				index++;
			}

			//store it in the symbol table
			variableNames.push_back(labelName);
			values.push_back(lineCounter + 1);
		}

		//C Instruction - increase line counter
		else
			lineCounter++;
	}
}

//doing the second parse
void secondParse(ifstream& inFile, ofstream& outFile, vector<string>& variableNames, vector<int>& values, int& varibleCounter)
{
	//variables
	string line;

	//parse through the file
	while(getline(inFile, line))
	{
		//to get rid of the comments after an A or C Instruction
		//eg. @temp           //A=temp
		if(line.length() >= 4)
		{
			for(int i = 1; i < line.length() - 1; ++i)
			{
				if((line.at(i) == 32 || line.at(i) == 9) && (line.at(i+1) == 32 || line.at(i+1) == 9) && (line.at(i+2) == 32 || line.at(i+2) == 9) 
					&& (line.at(i+3) == 32 || line.at(i+3) == 9))
				{
					line = line.substr(0, i);
					break;
				}
			}
		}

		//to get rid of the indentation
		for(int i = 0; i < line.length(); ++i)
		{
			if(line.at(i) == 32 || line.at(i) == 9)
			{
				line.erase(i, 1);
				i--;
			}
		}

		//NULL Line
		if(line.at(0) == 13)
			continue;

		//Label
		else if(line.at(0) == '(')
			continue;

		//Comment
		else if(line.at(0) == '/' && line.at(1) == '/')
			continue;

		//A Instruction
		else if(line.at(0) == '@')
			outFile << parseAInstruction(line.substr(1, (line.length()-1)), variableNames, values, varibleCounter) << endl;

		//C Instruction
		else
			outFile << parseCInstruction(line) << endl;
	}
}

//Parse an A Instruction
string parseAInstruction(string input, vector<string>& variableNames, vector<int>& values, int& varibleCounter)
{
	//get rid of any indentation
	for(int i = 0; i < input.length(); ++i)
	{
		if(input.at(i) == 32 || input.at(i) == ' ' || input.at(i) == 13)
		{
			input.erase(i, 1);
		}
	}

	//if it is a numerical value followed by @
	//eg. @12
	if(isdigit(input.at(0)))
	{
		int decimal = stoi(input);

		string output = bitset<15>(decimal).to_string();

		return ("0" + output);
	}

	//a variable followed by @
	//eg. @temp
	else
	{
		//if the variable already exists in the table
		//read its value and convert it to binary
		for(int i = 0; i < variableNames.size(); ++i)
		{
			if(variableNames.at(i) == input)
			{
				string output = bitset<15>(values.at(i)).to_string();
				return("0" + output);
			}
		}

		//else add it to the symbol table
		variableNames.push_back(input);
		values.push_back(varibleCounter);

		//update the counter for next variable
		string output = bitset<15>(varibleCounter).to_string();
		varibleCounter++;

		return ("0" + output);
	}
}

//Parse a C Instruction
string parseCInstruction(string input)
{
	//variables
	int indexOfEqualSign = 0;

	bool printZeroForJump = true;
	bool printZeroForDest = true;

	string dest;
	string comp;
	string jump;

	string output = "";

	//get rid of any leftover indentation
	for(int i = 0; i < input.length(); ++i)
	{
		if(input.at(i) == 32 || input.at(i) == ' ' || input.at(i) == 13)
		{
			input.erase(i, 1);
		}
	}

	//if it has an equal sign, get the index of it
	for(int i = 0; i < input.length(); ++i)
	{
		if(input.at(i) == '=')
			indexOfEqualSign = i;
	}

	//erase the new line character at the end
	if(input.at(input.length() - 1) == 13)
		input.erase((input.length() - 1), 1);

	//if it has a JUMP, take it out and pass it to ParseJump function
	//which will return its value in binary accordingly
	//and update the input by removing last 4 characters
	if(input.length() >= 5 && input.at(input.length() - 4) == ';')
	{
		jump = parseJump(input.substr((input.length() - 3), 3));
		printZeroForJump = false;
		input = input.substr(0, input.length() - 4);
	}

	//if it has a DEST, take it out and pass it to ParseDest function
	//which will return its value in binary accordingly
	//and update the input by removing characters till = sign
	if(indexOfEqualSign > 0)
	{
		dest = parseDest(input.substr(0, indexOfEqualSign));
		printZeroForDest = false;
		input = input.erase(0, (indexOfEqualSign + 1));
	}

	//leftover is a COMP, pass it to ParseComp function
	//which will return its value in binary accordingly
	comp = parseComp(input);

	//update the output as per the flags decided before
	if(printZeroForJump && printZeroForDest)
		output = "111" + comp + "000000";
	else if(printZeroForJump)
		output = "111" + comp + dest + "000";
	else if(printZeroForDest)
		output = "111" + comp + "000" + jump;
	else
		output = "111" + comp + dest + jump;

	return output;
}

//Output the binary according to the given input
string parseJump(string input)
{
	string output;

	if(input == "")
		output = "000";
	else if(input == "JGT")
		output = "001";
	else if(input == "JGE")
		output = "011";
	else if(input == "JLT")
		output = "100";
	else if(input == "JLE")
		output = "110";
	else if(input == "JEQ")
		output = "010";
	else if(input == "JNE")
		output = "101";
	else if(input == "JMP")
		output = "111";

	return output;
}

//Output the binary according to the given input
string parseDest(string input)
{
	string output;

	if(input == "")
		output = "000";
	else if(input == "M")
		output = "001";
	else if(input == "D")
		output = "010";
	else if(input == "MD")
		output = "011";
	else if(input == "A")
		output = "100";
	else if(input == "AM")
		output = "101";
	else if(input == "AD")
		output = "110";
	else if(input == "AMD")
		output = "111";

	return output;
}

//Output the binary according to the given input
string parseComp(string input)
{
	string output;

	if(input == "0")
		output = "0101010";
	else if(input == "1")
		output = "0111111";
	else if(input == "-1")
		output = "0111010";
	else if(input == "D")
		output = "0001100";
	else if(input == "A" || input == "M")
	{
		if(input == "A")
			output = "0110000";
		else
			output = "1110000";
	}
	else if(input == "!D")
		output = "0001101";
	else if(input == "!A" || input == "!M")
	{
		if(input == "!A")
			output = "0110001";
		else
			output = "1110001";
	}
	else if(input == "-D")
		output = "0001111";
	else if(input == "-A" || input == "-M")
	{
		if(input == "-A")
			output = "0110011";
		else
			output = "1110011";
	}
	else if(input == "D+1")
		output = "0011111";
	else if(input == "A+1" || input == "M+1")
	{
		if(input == "A+1")
			output = "0110111";
		else
			output = "1110111";
	}
	else if(input == "D-1")
		output = "0001110";
	else if(input == "A-1" || input == "M-1")
	{
		if(input == "A-1")
			output = "0110010";
		else
			output = "1110010";
	}
	else if(input == "D+A" || input == "D+M")
	{
		if(input == "D+A")
			output = "0000010";
		else
			output = "1000010";
	}
	else if(input == "D-A" || input == "D-M")
	{
		if(input == "D-A")
			output = "0010011";
		else
			output = "1010011";
	}
	else if(input == "A-D" || input == "M-D")
	{
		if(input == "A-D")
			output = "0000111";
		else
			output = "1000111";
	}
	else if(input == "D&A" || input == "D&M")
	{
		if(input == "D&A")
			output = "0000000";
		else
			output = "1000000";
	}
	else if(input == "D|A" || input == "D|M")
	{
		if(input == "D|A")
			output = "0010101";
		else
			output = "1010101";
	}

	return output;
}