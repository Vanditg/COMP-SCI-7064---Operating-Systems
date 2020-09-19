/*
created by: Vandit Jyotindra Gajjar
ID: a1779153
time: 19.09.2020
Contact Email: a1779153@student.adelaide.edu.au, vanditjyotindra.gajjar@adelaide.edu.au
Include int main(int argc,char *argv[])
input: argv[1]
output: Screen

input sample:
ID arrival_time priority age total_tickets_required
for example: s1 3 1 0 50

output sample:
ID, arrival and termination times, ready time and durations of running and waiting
*/
//Including useful utility files

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <sstream>
using namespace std;

//Constructing customerRes class with some variables 
class customerRes
{
    public:
        string customerName;
        unsigned int customerArrival;
        unsigned int customerEndQueue;
        unsigned int customerReadyTime;
        unsigned int customerRunning;
        unsigned int customerWaiting;
};

//Constructing customer class with some variables and pointers
class customer
{
    public:
        customerRes * corresponding = new customerRes();
        string ID;
        unsigned int arrival_time;
        unsigned int priority;
        unsigned int age;
        unsigned int total_ticket_required;
        customer * next = NULL;

};

//Constructing Queue class with pointer
class Queue
{
    public:
        customer * header = NULL;
};

//Initialisation of Queues and creating vectors
Queue * Queue_1 = new Queue();
vector<customer*> customerVectorQueue1;
Queue * Queue_2 = new Queue();
vector<customer*> customerVectorQueue2;
vector<customerRes*> customerResVec;

//Defining void Function - Initial and initialising the data types 
void initial()
{
    string tmp;
    unsigned int i;
    tmp = "";
    stringstream ss;
    i = 0;
    customer *pointer;
    pointer = NULL;

    while(getline(cin , tmp))
    {
        pointer = new customer();
        for (int i = 0; i < 5; ++i) {
            ss << tmp;
            switch(i)
            {
                case 0:
                    ss >> (*pointer).ID;
                    break;
                case 1:
                    ss >> (*pointer).arrival_time;
                    break;
                case 2:
                    ss >> (*pointer).priority;
                    break;
                case 3:
                    ss >> (*pointer).age;
                    break;
                case 4:
                    ss >> (*pointer).total_ticket_required;
                    break;
                default:
                    break;
            }
        }

        ss.str("");
        i = 0;

        if ((*pointer).priority > 3) {
            customerVectorQueue2.push_back(pointer);
        } else {
            customerVectorQueue1.push_back(pointer);
        }

        pointer->corresponding->customerName = (*pointer).ID;
        pointer->corresponding->customerArrival = (*pointer).arrival_time;
        pointer->corresponding->customerEndQueue = -1;
        pointer->corresponding->customerReadyTime = -1;
        pointer->corresponding->customerRunning = (*pointer).total_ticket_required * 5;
        pointer->corresponding->customerWaiting = 0;
    }

}
Queue * currentQueue1 = new Queue();
Queue * currentQueue2 = new Queue();

//Defining void Function - Input for parsing the input data 
void input()
{
    customer *pointerQueue1;
    pointerQueue1 = NULL;
    customer *pointerQueue2;
    pointerQueue2 = NULL;
    customer *lastCustomer;
    lastCustomer = NULL;
    customer *tmp;
    tmp = NULL;

    if (customerVectorQueue1.size() < 1) {}
    else {
        Queue_1->header = customerVectorQueue1[0];
    }

    if (customerVectorQueue2.size() < 1) {}
    else {
        Queue_2->header = customerVectorQueue2[0];
    }

    for(int i = 1 ; customerVectorQueue1.size() > i; i++)
    {
        pointerQueue1 = Queue_1->header;
        lastCustomer = NULL;

        while(pointerQueue1 != NULL)
        {
            if (customerVectorQueue1[i]->arrival_time >= pointerQueue1->arrival_time &&
                !(customerVectorQueue1[i]->arrival_time == pointerQueue1->arrival_time &&
                  customerVectorQueue1[i]->priority < pointerQueue1->priority)) {
                lastCustomer = pointerQueue1;
                pointerQueue1 = pointerQueue1->next;
            } else {
                if (pointerQueue1 != Queue_1->header) {
                    lastCustomer->next = customerVectorQueue1[i];
                    (*customerVectorQueue1[i]).next = pointerQueue1;
                    break;
                } else {
                    Queue_1->header = customerVectorQueue1[i];
                    (*customerVectorQueue1[i]).next = pointerQueue1;
                    break;
                }
            }
        }

        if (pointerQueue1 != NULL)
            continue;
        lastCustomer->next = customerVectorQueue1[i];
    }

    for(int i = 1 ; customerVectorQueue2.size() > i; i++)
    {
        pointerQueue2 = Queue_2->header;
        lastCustomer = NULL;

        while(pointerQueue2 != NULL)
        {
            if (customerVectorQueue2[i]->arrival_time >= pointerQueue2->arrival_time &&
                !(customerVectorQueue2[i]->arrival_time == pointerQueue2->arrival_time &&
                  customerVectorQueue2[i]->total_ticket_required < pointerQueue2->total_ticket_required)) {
                lastCustomer = pointerQueue2;
                pointerQueue2 = pointerQueue2->next;
            } else {
                if (pointerQueue2 != (*Queue_2).header) {
                    lastCustomer->next = customerVectorQueue2[i];
                    (*customerVectorQueue2[i]).next = pointerQueue2;
                    break;
                } else {
                    Queue_2->header = customerVectorQueue2[i];
                    (*customerVectorQueue2[i]).next = pointerQueue2;
                    break;
                }
            }
        }

        if (pointerQueue2 != NULL)
            continue;
        lastCustomer->next = customerVectorQueue2[i];
    }
}
//Defining void Function - Works for processing the parsed data 
void works()
{	
	//Defining several int and Boolean variables according to problem statement
    unsigned int totalTime;
	unsigned int leftTimeTicketReduction;
	unsigned int weightedTime;
	bool noTicketReduction;
	bool customerInQueue1ToQueue2;
	bool customerInQueue1ToEnd;
	bool customerInQueue1ToResult;
	bool customerInQueue1ToPromotion;
	bool customerInQueue2ToSubstitute;
	bool customerInQueue2ForTotalTime;
	bool customerInQueue1ToQueue2ForTotalTime;
	bool customerInQueue2ToQueue1WhenNull;
	bool newCustomerInQueue1;
	bool nullQueue1;
	bool endOfTicket;
    totalTime = 0;
    customer *tmp;
    tmp = Queue_1->header;
    customer *endPosition;
    endPosition = NULL;
    leftTimeTicketReduction = 0;
    weightedTime = -1;
    noTicketReduction = false;
    customer *customerToPosition;
    customerToPosition = NULL;
    customer *customerForTicket;
    customerForTicket = NULL;
    customerInQueue1ToQueue2 = false;
    customerInQueue1ToEnd = false;
    customerInQueue1ToResult = false;
    customerInQueue1ToPromotion = false;
    customerInQueue2ToSubstitute = false;
    customer *customerInQueue2;
    customerInQueue2 = NULL;
    customerInQueue2ForTotalTime = false;
    customerInQueue1ToQueue2ForTotalTime = false;
    customerInQueue2ToQueue1WhenNull = false;
    customer *customerToQueue1WhenNull;
    customerToQueue1WhenNull = NULL;
    newCustomerInQueue1 = false;
    customer *lastCustomer;
    lastCustomer = NULL;
    endOfTicket = false;
    nullQueue1 = false;
    while(true)
    {
        if (Queue_1->header != NULL || Queue_2->header != NULL || currentQueue1->header != NULL ||
            currentQueue2->header != NULL) {
            endOfTicket = false;
            nullQueue1 = false;
            if (!noTicketReduction) {
                if (currentQueue1->header != NULL || currentQueue2->header == NULL) {}
                else {
                    currentQueue2->header->total_ticket_required -= 1;

                    if (currentQueue2->header->corresponding->customerReadyTime == -1) {
                        if (customerInQueue1ToQueue2ForTotalTime) {
                            currentQueue2->header->corresponding->customerWaiting += 5;
                        } else {}
                        currentQueue2->header->corresponding->customerReadyTime = totalTime;
                    } else {}
                    tmp = currentQueue2->header->next;
                    while (tmp != NULL) {
                        if (tmp->corresponding->customerReadyTime != -1) {
                            tmp->corresponding->customerWaiting += 5;
                        } else {}
                        tmp = tmp->next;
                    }
                }
            } else {
                leftTimeTicketReduction += 5;
                (*customerForTicket).total_ticket_required -= 1;

                tmp = (*currentQueue1).header;
                while (tmp != NULL) {
                    if (tmp != customerForTicket) {
                        if (tmp->corresponding->customerReadyTime == -1) {}
                        else {
                            tmp->corresponding->customerWaiting += 5;
                        }
                    } else {}
                    tmp = tmp->next;
                }
                tmp = currentQueue2->header;
                while (tmp != NULL) {
                    if (tmp->corresponding->customerReadyTime == -1) {}
                    else {
                        tmp->corresponding->customerWaiting += 5;
                    }
                    tmp = tmp->next;
                }
            }
            if (leftTimeTicketReduction != weightedTime) {
                if (currentQueue1->header == NULL && currentQueue2->header != NULL) {
                    if (currentQueue2->header->total_ticket_required != 0) {}
                    else {
                        endOfTicket = true;
                        currentQueue2->header->corresponding->customerEndQueue = totalTime;
                        customerResVec.push_back(currentQueue2->header->corresponding);

                        (*currentQueue2).header = currentQueue2->header->next;
                        customerInQueue2ForTotalTime = true;
                    }
                }
            } else {
                endOfTicket = true;
                leftTimeTicketReduction = 0;
                weightedTime = -1;
                noTicketReduction = false;
                customerToPosition = customerForTicket;
                if (!newCustomerInQueue1) {
                    currentQueue1->header = currentQueue1->header->next;
                } else {
                    if (newCustomerInQueue1 == true) {
                        lastCustomer->next = customerForTicket->next;
                    }
                }

                if (customerToPosition->total_ticket_required != 0) {
                    customerInQueue1ToPromotion = true;
                } else {
                    customerInQueue1ToResult = true;
                }
            }

            customer *tmp_next = NULL;
            if (customerInQueue1ToPromotion == true) {
                if (customerToPosition->age >= 1) {
                    customerToPosition->age = 0;
                    customerToPosition->priority++;
                    if (customerToPosition->priority == 4) {
                        customerInQueue1ToQueue2 = true;
                        customerInQueue1ToQueue2ForTotalTime = true;

                        if (!newCustomerInQueue1) {}
                        else {
                            lastCustomer->next = customerForTicket->next;
                            newCustomerInQueue1 = false;
                        }
                    } else {
                        customerInQueue1ToEnd = true;
                        if (!newCustomerInQueue1) {}
                        else {
                            lastCustomer->next = customerForTicket->next;
                            newCustomerInQueue1 = false;
                        }
                    }
                } else {
                    customerInQueue1ToEnd = true;
                    customerToPosition->age++;

                    if (newCustomerInQueue1) {
                        lastCustomer->next = customerForTicket->next;
                        newCustomerInQueue1 = false;
                    } else {}
                }
                customerInQueue1ToPromotion = false;
            }

            while (Queue_1->header != NULL && Queue_1->header->arrival_time <= totalTime) {
                if (!(currentQueue1->header == NULL)) {
                    if (Queue_1->header->priority >= currentQueue1->header->priority) {
                        tmp = currentQueue1->header;
                        while (tmp->next != NULL) {
                            if (Queue_1->header->priority >= tmp->next->priority || tmp != lastCustomer ||
                                tmp->next != customerForTicket) {
                                if (Queue_1->header->priority >= tmp->next->priority ||
                                    tmp->next != customerForTicket) {
                                    if (Queue_1->header->priority >= tmp->next->priority) {
                                        tmp = tmp->next;
                                    } else {
                                        tmp_next = tmp->next;
                                        tmp->next = Queue_1->header;
                                        (*Queue_1).header = Queue_1->header->next;
                                        tmp->next->next = tmp_next;
                                        break;
                                    }
                                } else {
                                    newCustomerInQueue1 = true;
                                    lastCustomer = Queue_1->header;

                                    tmp_next = tmp->next;
                                    tmp->next = Queue_1->header;
                                    (*Queue_1).header = Queue_1->header->next;
                                    tmp->next->next = tmp_next;
                                    break;
                                }
                            } else {
                                newCustomerInQueue1 = true;
                                (*lastCustomer).next = Queue_1->header;
                                lastCustomer = Queue_1->header;
                                Queue_1->header = Queue_1->header->next;
                                lastCustomer->next = customerForTicket;
                                break;
                            }
                        }
                        if (!!!!(tmp->next == NULL)) {
                            tmp->next = Queue_1->header;
                            (*Queue_1).header = Queue_1->header->next;
                            tmp->next->next = NULL;
                        }
                    } else {
                        if (currentQueue1->header != customerForTicket) {}
                        else {
                            newCustomerInQueue1 = true;
                            lastCustomer = Queue_1->header;
                        }

                        tmp = currentQueue1->header;
                        (*currentQueue1).header = Queue_1->header;
                        Queue_1->header = Queue_1->header->next;
                        currentQueue1->header->next = tmp;
                    }
                } else {
                    (*currentQueue1).header = Queue_1->header;
                    Queue_1->header = Queue_1->header->next;
                    currentQueue1->header->next = NULL;

                    nullQueue1 = true;
                }
            }
            if (!customerInQueue1ToEnd || currentQueue1->header == NULL) {
                if (customerInQueue1ToEnd && currentQueue1->header == NULL) {
                    currentQueue1->header = customerToPosition;
                    customerToPosition->next = NULL;
                    customerInQueue1ToEnd = false;
                } else {
                    if (customerInQueue1ToQueue2 && currentQueue2->header != NULL) {
                        if (customerToPosition->total_ticket_required >= currentQueue2->header->total_ticket_required) {
                            tmp = currentQueue2->header;
                            while (tmp->next != NULL) {
                                if (customerToPosition->total_ticket_required >= tmp->next->total_ticket_required) {
                                    tmp = tmp->next;
                                } else {
                                    tmp_next = tmp->next;
                                    tmp->next = customerToPosition;
                                    customerToPosition->next = tmp_next;
                                    break;
                                }
                            }

                            if (!(tmp->next == NULL)) {}
                            else {
                                tmp->next = customerToPosition;
                                customerToPosition->next = NULL;
                            }
                        } else {
                            tmp = currentQueue2->header;
                            (*currentQueue2).header = customerToPosition;
                            (*customerToPosition).next = tmp;
                        }
                        customerInQueue1ToQueue2 = false;
                    } else {
                        if (!customerInQueue1ToQueue2 || currentQueue2->header != NULL) {}
                        else {
                            currentQueue2->header = customerToPosition;
                            customerToPosition->next = NULL;
                            customerInQueue1ToQueue2 = false;
                        }
                    }
                }
            } else {
                tmp = currentQueue1->header;
                if (customerToPosition->priority >= tmp->priority) {
                    while (tmp->next != NULL) {
                        if (customerToPosition->priority < tmp->next->priority) {
                            tmp_next = tmp->next;
                            (*tmp).next = customerToPosition;
                            (*customerToPosition).next = tmp_next;
                            break;
                        } else {
                            tmp = tmp->next;
                        }
                    }
                    if (!(tmp->next == NULL)) {}
                    else {
                        tmp->next = customerToPosition;
                        customerToPosition->next = NULL;
                    }
                }
                else {
                    currentQueue1->header = customerToPosition;
                    currentQueue1->header->next = tmp;
                }
                customerInQueue1ToEnd = false;
            }
            bool singleUsecase;
            singleUsecase = true;
            while (Queue_2->header != NULL && Queue_2->header->arrival_time <= totalTime) {
                if (!!(currentQueue2->header != NULL)) {
                    if (Queue_2->header->total_ticket_required >= currentQueue2->header->total_ticket_required) {
                        tmp = currentQueue2->header;
                        while ((*tmp).next != NULL) {
                            if (Queue_2->header->total_ticket_required < tmp->next->total_ticket_required) {
                                tmp_next = tmp->next;
                                (*tmp).next = Queue_2->header;
                                (*Queue_2).header = Queue_2->header->next;
                                tmp->next->next = tmp_next;
                                break;
                            } else {
                                tmp = tmp->next;
                            }
                        }

                        if (tmp->next == NULL) {
                            (*tmp).next = Queue_2->header;
                            (*Queue_2).header = Queue_2->header->next;
                            tmp->next->next = NULL;
                        }
                    } else {
                        if (!singleUsecase || customerInQueue2ForTotalTime) {}
                        else {
                            customerInQueue2 = (*currentQueue2).header;                 
                            customerInQueue2ToSubstitute = true;      
                            singleUsecase = false;
                        }
                        tmp = currentQueue2->header;
                        (*currentQueue2).header = Queue_2->header;
                        (*Queue_2).header = Queue_2->header->next;
                        currentQueue2->header->next = tmp;
                    }
                } else {
                    currentQueue2->header = (*Queue_2).header;
                    (*Queue_2).header = Queue_2->header->next;
                    currentQueue2->header->next = NULL;
                }
            }
            if (customerInQueue1ToResult) {
                customerToPosition->corresponding->customerEndQueue = totalTime;

                customerResVec.push_back(customerToPosition->corresponding);

                customerInQueue1ToResult = false;
            } else {}
            if ((*currentQueue1).header != NULL && !noTicketReduction) {
                noTicketReduction = true;
                if (currentQueue1->header->total_ticket_required < (10 - currentQueue1->header->priority) * 10 / 5) {
                    weightedTime = (*(*currentQueue1).header).total_ticket_required * 5;
                } else {
                    weightedTime = (10 - (*(*currentQueue1).header).priority) * 10;
                }

                if (currentQueue1->header->corresponding->customerReadyTime == -1) {
                    currentQueue1->header->corresponding->customerReadyTime = totalTime;
                } else {}

                customerForTicket = currentQueue1->header;
            } else {}
            if (!noTicketReduction) {
                if (currentQueue1->header != NULL || currentQueue2->header == NULL) {

                } else {
                    if (customerInQueue2ForTotalTime) {
                        tmp = currentQueue2->header;
                        customerInQueue2ForTotalTime = false;
                    } else {
                        tmp = currentQueue2->header;
                        if (tmp == NULL || customerInQueue2ToSubstitute ||
                            endOfTicket) {}
                        else {
                            tmp->age = 0;
                        }

                        if (!endOfTicket) {
                            tmp = currentQueue2->header->next;
                        } else {
                            tmp = currentQueue2->header;
                        }
                    }
                    while (tmp != NULL) {
                        if (tmp != customerToPosition ||
                            !customerInQueue1ToQueue2ForTotalTime) {
                            if (tmp != customerInQueue2 ||
                                !customerInQueue2ToSubstitute) {
                                if (tmp->arrival_time != totalTime) {
                                    tmp->age += 5;
                                }
                            } else {
                                customerInQueue2 = NULL;
                                customerInQueue2ToSubstitute = false;
                            }
                        } else {
                            customerInQueue1ToQueue2ForTotalTime = false;
                        }

                        tmp = tmp->next;
                    }
                }
            }
            else {
                tmp = currentQueue2->header;
                while (tmp != NULL) {
                    if (tmp != customerToPosition ||
                        !customerInQueue1ToQueue2ForTotalTime) {
                        if (tmp->arrival_time == totalTime || nullQueue1) {}
                        else {
                            tmp->age += 5;
                        }
                    } else {
                        customerInQueue1ToQueue2ForTotalTime = false;
                    }

                    tmp = tmp->next;
                }
            }
            bool emptyQueue1;
            bool onlySingleTimeUsage;
            emptyQueue1 = false;
            onlySingleTimeUsage = true;
            if (!!!(currentQueue1->header == NULL)) {
                tmp = currentQueue1->header;
                while ((*tmp).next != NULL) {
                    tmp = tmp->next;
                }
                endPosition = tmp;
                emptyQueue1 = false;
            } else {
                emptyQueue1 = true;
            }
            tmp = (*currentQueue2).header;
            while (tmp != NULL && tmp == currentQueue2->header) {
                if (tmp->age < 100 || tmp->priority != 4) {
                    if (tmp->age < 100 || (*tmp).priority <= 4) {
                        break;
                    } else {
                        (*tmp).age -= 100;
                        tmp->priority--;
                        break;
                    }
                } else {
                    if (!emptyQueue1) {
                        currentQueue2->header = currentQueue2->header->next;
                        endPosition->next = tmp;
                        (*tmp).next = NULL;
                        tmp->age = 0;
                        tmp->priority--;
                        endPosition = (*endPosition).next;
                        tmp = (*currentQueue2).header;
                    } else {
                        if (emptyQueue1) {
                            currentQueue2->header = (*currentQueue2).header->next;
                            (*currentQueue1).header = tmp;
                            tmp->next = NULL;
                            (*tmp).age = 0;
                            tmp->priority--;
                            endPosition = currentQueue1->header;
                            tmp = (*currentQueue2).header;
                            emptyQueue1 = false;

                            //
                            if (!onlySingleTimeUsage) continue;
                            customerInQueue2ToQueue1WhenNull = true;
                            customerToQueue1WhenNull = endPosition;
                            onlySingleTimeUsage = false;
                        }
                    }
                }
            }
            if (!(tmp != NULL)) {}
            else {
                while (tmp->next != NULL) {
                    if (tmp->next->age < 100 || tmp->next->priority != 4) {
                        if (tmp->next->age < 100 || tmp->next->priority <= 4) {
                            tmp = tmp->next;
                        } else {
                            tmp->next->age -= 100;
                            tmp->next->priority--;
                            tmp = tmp->next;
                        }
                    } else if (emptyQueue1) {
                        if (emptyQueue1) {
                            tmp->next->age = 0;
                            tmp->next->priority--;
                            currentQueue1->header = tmp->next;
                            (*tmp).next = tmp->next->next;
                            currentQueue1->header->next = NULL;
                            endPosition = currentQueue1->header;
                            emptyQueue1 = false;
                            if (!onlySingleTimeUsage) continue;
                            customerInQueue2ToQueue1WhenNull = true;
                            customerToQueue1WhenNull = endPosition;
                            onlySingleTimeUsage = false;
                        }
                    } else {
                        tmp->next->age = 0;
                        tmp->next->priority--;
                        endPosition->next = tmp->next;
                        (*tmp).next = tmp->next->next;
                        endPosition->next->next = NULL;
                        endPosition = endPosition->next;
                    }
                }
            }
            if (currentQueue2->header == NULL || noTicketReduction ||
                customerInQueue2ToQueue1WhenNull) {}
            else if (currentQueue2->header->corresponding->customerReadyTime != -1) {}
            else {
                currentQueue2->header->corresponding->customerReadyTime = totalTime;
            }
            if (!customerInQueue2ToQueue1WhenNull) {}
            else {
                if (!noTicketReduction) {
                    noTicketReduction = true;

                    if (currentQueue1->header->total_ticket_required >= (10 - currentQueue1->header->priority) * 10 / 5) {
                        weightedTime = (10 - currentQueue1->header->priority) * 10;
                    } else {
                        weightedTime = currentQueue1->header->total_ticket_required * 5;
                    }

                    if (currentQueue1->header->corresponding->customerReadyTime == -1) {
                        currentQueue1->header->corresponding->customerReadyTime = totalTime;
                    } else {}
                } else {}

                customerForTicket = currentQueue1->header;

                customerInQueue2ToQueue1WhenNull = false;
            }
            totalTime += 5;
        } else {
            break;
        }
    }
}
//Defining void Function - Output which showcase the results in terminal 
void output()
{
    unsigned int a;
    unsigned int b = 0;
    unsigned int counter = 1;
    unsigned int tmp = 0;
    string spacing = "          ";
    cout << "name   arrival   end   ready   running   waiting" << endl;
    for(a = 0; customerResVec.size() > a; a++)
    {
        cout << customerResVec[a]->customerName;
        for (; b < 5; b++) {
            switch(b)
            {
                case 0:
                    tmp = (*customerResVec[a]).customerArrival;
                    break;
                case 1:
                    tmp = (*customerResVec[a]).customerEndQueue;
                    break;
                case 2:
                    tmp = (*customerResVec[a]).customerReadyTime;
                    break;
                case 3:
                    tmp = (*customerResVec[a]).customerRunning;
                    break;
                case 4:
                    tmp = (*customerResVec[a]).customerWaiting;
                    break;
                default:
                    break;
            }
            for (;tmp >= 10; tmp/=10) {
                counter++;
            }
            switch(b)
            {
                case 0:
                    cout << spacing.substr(0 , 10 - counter) << (*customerResVec[a]).customerArrival;
                    break;
                case 1:
                    cout << spacing.substr(0 , 10 - counter) << (*customerResVec[a]).customerEndQueue;
                    break;
                case 2:
                    cout << spacing.substr(0 , 10 - counter) << (*customerResVec[a]).customerReadyTime;
                    break;
                case 3:
                    cout << spacing.substr(0 , 10 - counter) << (*customerResVec[a]).customerRunning;
                    break;
                case 4:
                    cout << spacing.substr(0 , 10 - counter) << (*customerResVec[a]).customerWaiting;
                    break;
                default:
                    break;
            }

            counter = 1;
            tmp = 0;
        }
        cout << endl;
        b = 0;
    }
    cout << endl;
}
//Main file to access the txt testcases on websubmission
int main(int argc,char *argv[])
{
    int i,j,k;
    freopen(argv[1],"r",stdin);

    initial();	//Initial Data
    input();	//Input Data
    works();	//Process Data
    output();	//Output Result
    return 0;
}

//References: 
// [1] https://www.w3schools.com/cpp/
// [2] https://www.cplusplus.com/
// [3] https://www.tutorialspoint.com/cplusplus/index.htm
// [4] https://www.geeksforgeeks.org/c-plus-plus/
// [5] https://docs.microsoft.com/en-us/cpp/?view=vs-2019
// [6] Silberschatz, Abraham, Peter Galvin, and Greg Gagne. Applied operating system concepts. John Wiley & Sons, Inc., 2001.

//OpenSource:
//The source code has been published at https://github.com/Vanditg/COMP-SCI-7064---Operating-Systems