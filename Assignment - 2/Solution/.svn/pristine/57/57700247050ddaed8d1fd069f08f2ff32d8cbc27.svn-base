/*
created by: Vandit Jyotindra Gajjar
ID: a1779153
Time: 14.10.2020
Course: Operating Systems 
Assignment 2: Page Replacement 
Contact Email: a1779153@student.adelaide.edu.au, vanditjyotindra.gajjar@adelaide.edu.au
*/

//Importing header files 
#include<iostream>
#include<cstring>
#include<cstdlib>
#define WRITE_ true;
#include<stdlib.h>
#include<algorithm>
#include"utilities.h"
using namespace std;
#define READ_ false;

//Definiing a boolean tableChecker function 
bool tableChecker(map<string,bool> &deletionPageTable,string _page)
{
    if (!(deletionPageTable[_page] == true))
        return false;
    return true;
}

//Main method 
int main(int argc,char *argv[])
{
	vector<string> temporary; 
	string algorithm = argv[4]; 
	unsigned int totalTime = 0; 
	unsigned int threshold;
	unsigned int countError = 0;
	string unk; 
	unk = argv[6];
	unsigned int var = atoi(unk.c_str());
	vector<int> registerShifting;
    if (algorithm != "ARB" && algorithm != "WSARB-1" && algorithm != "WSARB-2") {}
    else {
        string tmpVar;
        tmpVar = argv[5];
        unsigned int tempVar = atoi(tmpVar.c_str());
        for (unsigned int i = 0; i < tempVar; i++) {
            registerShifting.push_back(0);
        }
        registerShifting.at(0) = 1;
    }
    if (algorithm != "WSARB-1" && algorithm != "WSARB-2") {}
    else {
        string thresholdT = argv[7];
        threshold = atoi(thresholdT.c_str());
    }
    FILE * fp = freopen(argv[1],"r",stdin);
    bool nameOfProcess = false;
	string numTmp = argv[3];
    bool option;
    unsigned int countDiskReads = 0;
    unsigned int eventTracerCount = 0;
    vector<string> deletionPages;
	unsigned int pageNumbers = atoi(numTmp.c_str());
    map<string,bool> deletionPageTable;
	string idProcessor;
    string pageTmp = argv[2];
	map<string,bool> pageDirt;
	unsigned int writeCounter = 0;
    map<string,int> ageDeletion;
	unsigned int sizeOfPage = atoi(pageTmp.c_str()); 
    map<string,vector<int>> deletionBuffer;
	string lineTracer;
    map<string,int> deletionCount;

    while(cin>>lineTracer)
    {
        if (!(lineTracer.at(0) == '#')) {
            if (!(lineTracer[0] == 'W')) {
                if (!(lineTracer[0] == 'R')) {
                    if (!nameOfProcess) {
                        string _page = accessPage(lineTracer, sizeOfPage);

                        if (!option) {}
                        else {
                            pageDirt[_page] = true;
                        }

                        if (algorithm != "ARB" || (totalTime) % var != 0 || totalTime == 0) {}
                        else {
                            memoryBitShifting(deletionPages, deletionBuffer);
                        }

                        if (algorithm != "WSARB-1" || (totalTime) % var != 0 || totalTime == 0) {}
                        else {
                            memoryBitShifting(deletionPages, deletionBuffer);
                        }

                        if (algorithm != "WSARB-2" || (totalTime) % var != 0 || totalTime == 0) {}
                        else {
                            memoryBitShifting(deletionPages, deletionBuffer);
                        }

                        if (algorithm != "WSARB-1" && algorithm != "WSARB-2") {}
                        else {
                            temporary.push_back(_page);
                            if (!(temporary.size() > threshold)) {}
                            else {
                                temporary.erase(temporary.begin());
                            }

                            for (unsigned int j = 0; j < deletionPages.size(); j++) {
                                deletionCount[deletionPages.at(j)] = 0;
                            }

                            for (unsigned int i = 0; i < deletionPages.size(); i++) {
                                string currentPage = deletionPages.at(i);

                                for (unsigned int j = 0; j < temporary.size(); j++) {
                                    if (!(temporary.at(j) == currentPage)) continue;
                                    deletionCount[currentPage] = deletionCount[currentPage] + 1;
                                }
                            }
                        }

                        if (!tableChecker(deletionPageTable, _page)) {
                            if (tableChecker(deletionPageTable, _page)) {}
                            else {
                                countDiskReads++;
                                countError++;
                                ageDeletion[_page] = 0;
                                deletionBuffer[_page] = registerShifting;

                                for (unsigned int j = 0; j < deletionPages.size(); j++) {
									string tmp = deletionPages.at(j);
                                    ageDeletion[tmp] = ageDeletion[tmp] + 1;
                                }

                                if (!(deletionPages.size() >= pageNumbers)) {}
                                else {
                                    deletion(deletionPages, deletionPageTable, algorithm, pageDirt, writeCounter, ageDeletion, deletionBuffer, deletionCount, temporary);
                                }

                                deletionPages.push_back(_page);
                                deletionPageTable[_page] = true;
                            }
                        } else {
                            for (unsigned int j = 0; j < deletionPages.size(); j++) {
                                if (!(deletionPages.at(j) == _page)) {
                                    ageDeletion[deletionPages.at(j)] = ageDeletion[deletionPages.at(j)] + 1;
                                } else {
                                    ageDeletion[_page] = 0;
                                }
                            }

                            if (algorithm != "ARB" && algorithm != "WSARB-1" && algorithm != "WSARB-2") {}
                            else {
                                vector<int> valHolder;
                                valHolder = deletionBuffer[_page];
                                valHolder.at(0) = 1;
                                deletionBuffer[_page] = valHolder;

                                int index;
                            }

                            if (algorithm != "WSARB-1" && algorithm != "WSARB-2") {}
                            else {
                                for (unsigned int i = 0; i < deletionPages.size(); i++) {
                                    if (!(deletionPages.at(i) == _page)) continue;
                                    deletionPages.push_back(_page);
                                    deletionPages.erase(deletionPages.begin() + i);
                                }
                            }
                        }

                        totalTime++;
                    } else {
                        idProcessor = lineTracer;
                        nameOfProcess = false;
                    }
                } else {
                    option = READ_;
                    eventTracerCount++;
                }
            } else {
                option = WRITE_;
                eventTracerCount++;
            }
        } else {
            nameOfProcess = true;
        }
    }

    printResult(eventTracerCount,countDiskReads,writeCounter,countError,algorithm);

};

//References: 
// [1] https://www.w3schools.com/cpp/
// [2] https://www.cplusplus.com/
// [3] https://www.tutorialspoint.com/cplusplus/index.htm
// [4] https://www.geeksforgeeks.org/c-plus-plus/
// [5] https://docs.microsoft.com/en-us/cpp/?view=vs-2019
// [6] Silberschatz, Abraham, Peter Galvin, and Greg Gagne. Applied operating system concepts. John Wiley & Sons, Inc., 2001.

//OpenSource:
//The source code has been published at https://github.com/Vanditg/COMP-SCI-7064---Operating-Systems
