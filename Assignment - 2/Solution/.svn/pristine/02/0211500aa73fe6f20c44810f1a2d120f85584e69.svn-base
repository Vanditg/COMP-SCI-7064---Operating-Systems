/*
created by: Vandit Jyotindra Gajjar
ID: a1779153
Time: 14.10.2020
Course: Operating Systems 
Assignment 2: Page Replacement 
Contact Email: a1779153@student.adelaide.edu.au, vanditjyotindra.gajjar@adelaide.edu.au
*/

//Importing header files 
#ifndef _PAGE_REPLACEMENT
#define _PAGE_REPLACEMENT
#include<vector>
#include<map>
#include<algorithm>
#include<string>
#include<sstream>
#include<iostream>
#include<list>
#include<cstdlib>
#include<tuple>
#include<exception>
#include<iterator>
#include<regex>

using namespace std;

//Defining a string accessPage function. 
string accessPage(string address, unsigned int memory)
{
	string page;

    if (memory != 4096) {
        if (memory != 2048) {
            if (memory != 1024) {
                if (memory != 512) {}
                else {
                    char one = address.at(4);
                    char two = address.at(5);

                    string sOne;
                    stringstream ss;
                    ss << one;
                    ss >> sOne;
                    string sTwo;

                    if (two != '0' && two != '1') {
                        if (two != '2' && two != '3') {
                            if (two != '4' && two != '5') {
                                if (two != '6' && two != '7') {
                                    if (two != '8' && two != '9') {
                                        if (two != 'a' && two != 'b') {
                                            if (two != 'c' && two != 'd') {
                                                if (two != 'e' && two != 'f') {} else { sTwo = "e"; }
                                            } else { sTwo = "c"; }
                                        } else { sTwo = "a"; }
                                    } else { sTwo = "8"; }
                                } else { sTwo = "6"; }
                            } else { sTwo = "4"; }
                        } else { sTwo = "2"; }
                    } else { sTwo = "0"; }
                    page = sOne + sTwo;
                    return page;
                }
            } else {
                char one = address.at(4);
                char two = address.at(5);

                string sOne;
                stringstream ss;
                ss << one;
                ss >> sOne;
                string sTwo;

                if (two != '0' && two != '1' && two != '2' && two != '3') {
                    if (two != '4' && two != '5' && two != '6' && two != '7') {
                        if (two != '8' && two != '9' && two != 'a' && two != 'b') {
                            if (two != 'c' && two != 'd' && two != 'e' && two != 'f') {}
                            else { sTwo = "c"; }
                        } else { sTwo = "8"; }
                    } else { sTwo = "4"; }
                } else { sTwo = "0"; }

                page = sOne + sTwo;
            }
        } else {
            char one = address.at(4);
            char two = address.at(5);

            string sOne;
            stringstream ss;
            ss << one;
            ss >> sOne;
            string sTwo;

            if (two != '0' && two != '1' && two != '2' && two != '3' && two != '4' && two != '5' &&
                two != '6' && two != '7') {
                if (two != '8' && two != '9' && two != 'a' && two != 'b' && two != 'c' &&
                    two != 'd' && two != 'e' && two != 'f') {}
                else { sTwo = "8"; }
            } else { sTwo = "0"; }
            page = sOne + sTwo;
            return page;
        }
    } else {
        unsigned int zeroPage = 0;
        address.erase(address.begin() + 5, address.end());
        page = address;
        for (unsigned int i = 0; i < page.size(); i++) {
            if (page.at(i) != '0' || zeroPage == 4) {
                i = page.size();
            } else {
                page.erase(page.begin() + i);
                i--;
            }
            zeroPage++;
        }
        return page;

    }

}

//Defining a void printResult function.
void printResult(unsigned int eventTracerCount,unsigned int countDiskReads,unsigned int writeCounter,unsigned int countError,string reg)
{
	cout<<"events in trace: "<<eventTracerCount<<endl;
	cout<<"total disk reads: "<<countDiskReads<<endl;
	cout<<"total disk writes: "<<writeCounter<<endl;
	cout<<"page faults: "<<countError<<endl;
}

//Defining a void memoryBitShifting function.
void memoryBitShifting(vector<string> testPages,map<string,vector<int>> &buff)
{ 
	unsigned int i = 0; 
	do{
		vector<int> tmp;
		//tmp = buff[testPages.at(i)];
		rotate(buff[testPages.at(i)].begin(), buff[testPages.at(i)].begin() + buff[testPages.at(i)].size()-1, buff[testPages.at(i)].end());
		buff[testPages.at(i)].at(0)=0;
		buff[testPages.at(i)] = buff[testPages.at(i)]; 
		i++;
	} while(i < testPages.size());
}

//Defining an int intConversion function.
unsigned int intConversion(vector<int> in)
{
	unsigned int convert = 0;
	unsigned int memSize = in.size();
	unsigned int multi = 1; 
	unsigned int i = memSize-1;
	do{
		convert = convert + in.at(i)*multi;
		multi = multi*10;
		i--;
	} while(i>-1);
	return convert; 
}

//Defining a void deletion function.
void deletion(vector<string> &deletionPages,map<string,bool> &deletionPageTable,string algorithm,map<string,bool> &pageDirt,unsigned int &writeCounter,map<string,int> &ageDeletion,map<string,vector<int>> deletionBuffer,map<string,int> deletionCount,vector<string> &temporary)
{
    if (algorithm != "FIFO") {
        if (algorithm != "LRU") {
            if (algorithm != "ARB") {
                if (algorithm != "WSARB-1") {
                    if (algorithm != "WSARB-2") {
                        cout << "!!!Error Detected!!!" << endl;
                    } else {

                        signed int indexChecker = -1;
                        unsigned int indexVic;
                        vector<int> checker;
                        string vic;
                        unsigned int maximum = 999999999;
                        for (unsigned int k = 0; k < deletionPages.size(); k++) {
                            checker = deletionBuffer[deletionPages.at(k)];
                            unsigned int tmp = intConversion(checker);
                            if (tmp >= maximum) continue;
                            maximum = tmp;
                            indexVic = k;
                            vic = deletionPages.at(k);
                        }

                        unsigned int _counter = 0;
                        for (unsigned int o = 0; o < deletionPages.size(); o++) {
                            checker = deletionBuffer[deletionPages.at(o)];
                            unsigned int tmp = intConversion(checker);
                            if (tmp != maximum) continue;
                            _counter++;
                        }
                        if (_counter != 1) {
                            if (_counter <= 1) {
                                cout << "!!!Invalid!!!" << endl;
                            } else {
                                string vic;
                                unsigned int tmp;
                                unsigned int minimum = 99999999;
                                string _minimumPage;
                                unsigned int minimumIndex;

                                for (unsigned int page = 0; page < deletionPages.size(); page++) {
                                    if (!(deletionCount[deletionPages.at(page)] < minimum)) continue;
                                    minimum = deletionCount[deletionPages.at(page)];
                                    _minimumPage = deletionPages.at(page);
                                    minimumIndex = page;
                                }

                                if (!(pageDirt[_minimumPage] == true)) {}
                                else {
                                    writeCounter++;
                                }

                                map<string, bool>::iterator it2;
                                it2 = deletionPageTable.find(_minimumPage);
                                deletionPageTable.erase(it2);
                                map<string, bool>::iterator it1;
                                it1 = pageDirt.find(_minimumPage);
                                pageDirt.erase(it1);
                                map < string, vector < int >> ::iterator it4;
                                it4 = deletionBuffer.find(_minimumPage);
                                deletionBuffer.erase(it4);
                                map<string, int>::iterator it5;
                                it5 = deletionCount.find(_minimumPage);
                                deletionCount.erase(it5);
                                deletionPages.erase(deletionPages.begin() + minimumIndex);
                            }
                        } else {
                            if (!(pageDirt[vic] == true)) {}
                            else {
                                writeCounter++;
                            }
                            map < string, vector < int >> ::iterator it4;
                            map<string, bool>::iterator it2;
                            it2 = deletionPageTable.find(vic);
                            deletionPageTable.erase(it2);
                            map<string, bool>::iterator it1;
                            it1 = pageDirt.find(vic);
                            pageDirt.erase(it1);
                            it4 = deletionBuffer.find(vic);
                            deletionBuffer.erase(it4);
                            deletionPages.erase(deletionPages.begin() + indexVic);
                        }
                    }
                } else {

                    string vic;
                    unsigned int tmp;
                    unsigned int minimum = 99999999;
                    string _minimumPage;
                    unsigned int minimumIndex;

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

                    for (unsigned int page = 0; page < deletionPages.size(); page++) {
                        if (!(deletionCount[deletionPages.at(page)] < minimum)) continue;
                        minimum = deletionCount[deletionPages.at(page)];
                        _minimumPage = deletionPages.at(page);
                        minimumIndex = page;
                    }

                    unsigned int _checker = 0;
                    for (unsigned int p = 0; p < deletionPages.size(); p++) {
                        if (!(deletionCount[deletionPages.at(p)] == minimum)) continue;
                        _checker++;
                    }

                    if (_checker != 1) {
                        if (_checker <= 1) {
                            cout << "!!!Error!!!" << endl;
                        } else {
                            vector<int> checker;
                            string vic;
                            unsigned int maximum = 999999999;
                            for (unsigned int k = 0; k < deletionPages.size(); k++) {
                                if (!(deletionCount[deletionPages.at(k)] == minimum)) continue;
                                checker = deletionBuffer[deletionPages.at(k)];
                                unsigned int tempOne = intConversion(checker);;
                                if (tempOne >= maximum) continue;
                                maximum = tempOne;
                                vic = deletionPages.at(k);
                            }

                            if (!(pageDirt[vic] == true)) {}
                            else {
                                writeCounter++;
                            }

                            map<string, bool>::iterator it2;
                            it2 = deletionPageTable.find(vic);
                            deletionPageTable.erase(it2);
                            map<string, bool>::iterator it1;
                            it1 = pageDirt.find(vic);
                            pageDirt.erase(it1);
                            map < string, vector < int >> ::iterator it4;
                            it4 = deletionBuffer.find(vic);
                            deletionBuffer.erase(it4);
                            map<string, int>::iterator it5;
                            it5 = deletionCount.find(_minimumPage);
                            deletionCount.erase(it5);
                            unsigned int indexVic;

                            for (unsigned int o = 0; o < deletionPages.size(); o++) {
                                if (!(deletionPages.at(o) == vic)) continue;
                                indexVic = o;
                                o = deletionPages.size();
                            }

                            for (unsigned int i = 0; i < temporary.size(); i++) {
                                if (!(temporary.at(i) == vic)) continue;
                                temporary.erase(temporary.begin() + i);
                            }

                            deletionPages.erase(deletionPages.begin() + indexVic);
                        }
                    } else {
                        if (!(pageDirt[_minimumPage] == true)) {}
                        else {
                            writeCounter++;
                        }

                        map<string, bool>::iterator it2;
                        it2 = deletionPageTable.find(_minimumPage);
                        deletionPageTable.erase(it2);
                        map<string, bool>::iterator it1;
                        it1 = pageDirt.find(_minimumPage);
                        pageDirt.erase(it1);
                        map < string, vector < int >> ::iterator it4;
                        it4 = deletionBuffer.find(_minimumPage);
                        deletionBuffer.erase(it4);
                        map<string, int>::iterator it5;
                        it5 = deletionCount.find(_minimumPage);
                        deletionCount.erase(it5);
                        deletionPages.erase(deletionPages.begin() + minimumIndex);

                    }
                }
            } else {
                signed int indexChecker = -1;
                unsigned int indexVic;
                vector<int> checker;
                string vic;
                unsigned int maximum = 999999999;
                for (unsigned int k = 0; k < deletionPages.size(); k++) {
                    checker = deletionBuffer[deletionPages.at(k)];
                    unsigned int tmp = intConversion(checker);
                    if (tmp >= maximum) continue;
                    maximum = tmp;
                    indexVic = k;
                    vic = deletionPages.at(k);
                }

                if (!(pageDirt[vic] == true)) {}
                else {
                    writeCounter++;
                }
                map <string, vector<int>> ::iterator it4;
                map<string, bool>::iterator it2;
                it2 = deletionPageTable.find(vic);
                deletionPageTable.erase(it2);
                map<string, bool>::iterator it1;
                it1 = pageDirt.find(vic);
                pageDirt.erase(it1);              
                it4 = deletionBuffer.find(vic);
                deletionBuffer.erase(it4);
                deletionPages.erase(deletionPages.begin() + indexVic);

            }
        } else {
            signed int last = -1;
            unsigned int val;
            string nameOfPage;

            for (unsigned int i = 0; i < deletionPages.size(); i++) {
                if (!(ageDeletion[deletionPages.at(i)] > last)) continue;
                last = ageDeletion[deletionPages.at(i)];
                nameOfPage = deletionPages.at(i);
                val = i;
            }

            if (!(pageDirt[nameOfPage] == true)) {}
            else {
                writeCounter++;
            }

            map<string, bool>::iterator it2;
            it2 = deletionPageTable.find(nameOfPage);
            deletionPageTable.erase(it2);
            map<string, bool>::iterator it1;
            it1 = pageDirt.find(nameOfPage);
            pageDirt.erase(it1);
            map<string, int>::iterator it3;
            it3 = ageDeletion.find(nameOfPage);
            ageDeletion.erase(it3);
            deletionPages.erase(deletionPages.begin() + val);

        }
    } else {

        string nameOfPage = deletionPages.at(0);
        deletionPages.erase(deletionPages.begin());
        if (!(pageDirt[nameOfPage] == true)) {}
        else {
            writeCounter++;
            map<string, bool>::iterator it1;
            it1 = pageDirt.find(nameOfPage);
            pageDirt.erase(it1);
        }
        map<string, bool>::iterator it2;
        it2 = deletionPageTable.find(nameOfPage);
        deletionPageTable.erase(it2);
    }
}
#endif 

//References: 
// [1] https://www.w3schools.com/cpp/
// [2] https://www.cplusplus.com/
// [3] https://www.tutorialspoint.com/cplusplus/index.htm
// [4] https://www.geeksforgeeks.org/c-plus-plus/
// [5] https://docs.microsoft.com/en-us/cpp/?view=vs-2019
// [6] Silberschatz, Abraham, Peter Galvin, and Greg Gagne. Applied operating system concepts. John Wiley & Sons, Inc., 2001.

//OpenSource:
//The source code has been published at https://github.com/Vanditg/COMP-SCI-7064---Operating-Systems
