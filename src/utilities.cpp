/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;
vector<process_stats> stats;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	stats.clear();
	string line;
	string subSTR;
	vector<string> temp;
	  ifstream myfile (filename);
	  if (myfile.is_open())
	  {
		  if (ignoreFirstRow) {
			  // Skip first line
			  getline (myfile,line);
		  }
		  // loop through lines
	    while ( getline (myfile,line) )
	    {
	    	// check how many commas
	    	std::string::difference_type n = std::count(line.begin(), line.end(), ',');
	    	bool corrupted = false;
	    	if (n == 3){
	    		stringstream ss(line);
	    		    string word;
	    		    while (!ss.eof()) {
	    		    	// split word by comma
	    		            getline(ss, word, ',');
	    		            temp.push_back(word);
	    		            // if word is not correct than flag line
	    		            if (word == ""){
	    		            	corrupted = true;
	    		            }
	    		        }
				// create and add struct
	    		process_stats tempStruct;
	    		tempStruct.process_number = stringToInt(temp[0].c_str());
	    		tempStruct.start_time = stringToInt(temp[1].c_str());
	    		tempStruct.cpu_time = stringToInt(temp[2].c_str());
	    		tempStruct.io_time = stringToInt(temp[3].c_str());
	    		temp.clear();
	    		// if line is not flagged than push to final vector
	    		if (!corrupted ){
	    			stats.push_back(tempStruct);
	    		}
	    	}
	    }
	    myfile.close();
	  }

	  else return COULD_NOT_OPEN_FILE;

	return SUCCESS;
}


bool compareCPU(process_stats a, process_stats b)
{
		return a.cpu_time < b.cpu_time;
}
bool compareProcess(process_stats a, process_stats b)
{
		return a.process_number < b.process_number;
}
bool compareio(process_stats a, process_stats b)
{
		return a.io_time < b.io_time;
}
bool compareStartTime(process_stats a, process_stats b)
{
		return a.start_time < b.start_time;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch (mySortOrder){
	case CPU_TIME:
		sort(stats.begin(), stats.end(), compareCPU);
		break;
	case PROCESS_NUMBER:
		sort(stats.begin(), stats.end(), compareProcess);
			break;
	case START_TIME:
		sort(stats.begin(), stats.end(), compareStartTime);
			break;
	case IO_TIME:
		sort(stats.begin(), stats.end(), compareio);
			break;
	}
}

process_stats getNext() {
	process_stats myFirst = stats[0];
	stats.erase(stats.begin());

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


