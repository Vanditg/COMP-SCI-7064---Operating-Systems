/*
created by:Vandit Jyotindra Gajjar
ID:a1779153
time:06.08.2020
Contact Email: a1779153@student.adelaide.edu.au
Include int main(int argc,char *argv[])
input: argv[1]
output: Screen

input sample:
ID arrival_time priority age total_tickets_required
for example: s1 3 1 0 50

output sample:
ID, arrival and termination times, ready time and durations of running and waiting
*/

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

//To hold output
class Customer_result
{
    public:
        string name;                    //Initialized in initial()
        int arrival;                    //Initialized in initial()
        int end;
        int ready;
        int running;                    //Initialized in initial()
        int waiting;
};

//To hold input
class Customer
{
    public:
        string customerID;
        int arrival_time;
        int priority;
        int age;
        int total_ticket;
        Customer * next = NULL;
        Customer_result * corresponding = new Customer_result();        //Everything is initialized in initial()
};

//To hold all inputs (unordered);
vector<Customer*> customer_in_queue1_vector;
vector<Customer*> customer_in_queue2_vector;

//To hold all outputs;
vector<Customer_result*> customer_result_vector;

class Queue
{
    public:
        Customer * header = NULL;
};

//These Queues are to hold sorted customers
Queue * queue1 = new Queue();
Queue * queue2 = new Queue();

//These Queues are for working on
Queue * working_queue1 = new Queue();
Queue * working_queue2 = new Queue();

//Grab string from stdin , then turn it into Customer object and store in vector (unordered)
//Also , separate the object into 2 different vector due to their priority (priority <=3 will store into customer_in_queue1_vector)
void initial()
{
    string temp = "";
    stringstream ss;
    int i = 0;
    Customer * ptr = NULL;

    while(getline(cin , temp))
    {
        ptr = new Customer();
        while(i < 5)
        {
            ss << temp;
            switch(i)
            {
                case 0:
                    ss >> ptr->customerID;
                    break;
                case 1:
                    ss >> ptr->arrival_time;
                    break;
                case 2:
                    ss >> ptr->priority;
                    break;
                case 3:
                    ss >> ptr->age;
                    break;
                case 4:
                    ss >> ptr->total_ticket;
                    break;
                default:
                    break;
            }
            i++;
        }
        ss.str("");                     // <-- ss.clear() not working
        i = 0;

        //Put into the vector
        if(ptr->priority <= 3)
        {
            customer_in_queue1_vector.push_back(ptr);
        }
        else
        {
            customer_in_queue2_vector.push_back(ptr);
        }

        //Initialize corresponding as well (Customer_result object)
        ptr->corresponding->name = ptr->customerID;
        ptr->corresponding->arrival = ptr->arrival_time;
        ptr->corresponding->end = -1;
        ptr->corresponding->ready = -1;
        ptr->corresponding->running = ptr->total_ticket * 5;
        ptr->corresponding->waiting = 0;
    }

}

//Grab the Customer object from vector , then arrange the object into a queue list (ordered)
void input()
{
    Customer * ptr_queue1 = NULL;
    Customer * ptr_queue2 = NULL;
    Customer * previous_customer = NULL;
    Customer * temp = NULL;

    //Set queue1 and queue2 to the first customer
    if(customer_in_queue1_vector.size() >= 1)
    {
        queue1->header = customer_in_queue1_vector[0];
    }

    if(customer_in_queue2_vector.size() >= 1)
    {
        queue2->header = customer_in_queue2_vector[0];
    }

    //Set up queue1
    for(int i = 1 ; i < customer_in_queue1_vector.size() ; i++)
    {
        //Reset back to header
        ptr_queue1 = queue1->header;
        previous_customer = NULL;

        while(ptr_queue1 != NULL)
        {
            if((customer_in_queue1_vector[i]->arrival_time < ptr_queue1->arrival_time) || (customer_in_queue1_vector[i]->arrival_time == ptr_queue1->arrival_time && customer_in_queue1_vector[i]->priority < ptr_queue1->priority))
            {
                //Check if it is the header of queue1
                if(ptr_queue1 == queue1->header)
                {
                    queue1->header = customer_in_queue1_vector[i];
                    customer_in_queue1_vector[i]->next = ptr_queue1;
                    break;
                }
                else
                {
                    previous_customer->next = customer_in_queue1_vector[i];
                    customer_in_queue1_vector[i]->next = ptr_queue1;
                    break;
                }
            }
            else
            {
                previous_customer = ptr_queue1;
                ptr_queue1 = ptr_queue1->next;
            }
        }

        //Last customer
        if(ptr_queue1 == NULL)
        {
            previous_customer->next = customer_in_queue1_vector[i];
        }
    }

    //Set up queue2
    for(int i = 1 ; i < customer_in_queue2_vector.size() ; i++)
    {
        //Reset back to header
        ptr_queue2 = queue2->header;
        previous_customer = NULL;

        while(ptr_queue2 != NULL)
        {
            if((customer_in_queue2_vector[i]->arrival_time < ptr_queue2->arrival_time) || (customer_in_queue2_vector[i]->arrival_time == ptr_queue2->arrival_time && customer_in_queue2_vector[i]->total_ticket < ptr_queue2->total_ticket))
            {
                //Check if it is the header of queue2
                if(ptr_queue2 == queue2->header)
                {
                    queue2->header = customer_in_queue2_vector[i];
                    customer_in_queue2_vector[i]->next = ptr_queue2;
                    break;
                }
                else
                {
                    previous_customer->next = customer_in_queue2_vector[i];
                    customer_in_queue2_vector[i]->next = ptr_queue2;
                    break;
                }
            }
            else
            {
                previous_customer = ptr_queue2;
                ptr_queue2 = ptr_queue2->next;
            }
        }

        //Last customer
        if(ptr_queue2 == NULL)
        {
            previous_customer->next = customer_in_queue2_vector[i];
        }
    }
}

//Do queue1 and queue2 , then combine them into multilevel queue
void works()
{
    //Set initial timer
    int timer = 0;

    Customer * temp = queue1->header;
    Customer * last_position = NULL;
   

    //
    int time_remaining_to_finish_ticket_reduction = 0;                                 //<-- to prevent time_remaining == weight_round_robin at first loop
    int weighted_round_robin_time = -1;
    bool no_one_can_do_ticket_reduction = false;
    Customer * first_customer_going_to_reposition = NULL;
    Customer * first_customer_that_is_doing_ticket = NULL;
    //
    bool first_customer_in_working_queue1_reposition_to_queue2 = false;
    bool first_customer_in_working_queue1_reposition_to_behind = false;
    //
    bool first_customer_in_working_queue1_is_done_and_going_to_result = false;
    bool first_customer_in_working_queue1_is_done_and_need_to_check_promotion = false;
    //
    bool first_customer_in_working_queue2_is_substitute_by_new_customer = false;
    Customer * previous_first_customer_in_queue2 = NULL;
    bool first_customer_in_working_queue2_is_done_and_timer_need_to_be_careful = false;
    bool first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful = false;
    //
    bool customer_in_working_queue2_is_promoted_to_queue1_when_queue1_is_NULL = false;
    Customer * first_of_several_customer_that_is_promote_to_queue1_when_queue1_is_NULL = NULL;
    //
    bool there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = false;
    Customer * previous_customer = NULL;
    //
    bool someone_just_done_the_ticket = false;
    bool someone_just_come_into_null_working_queue1 = false;
    while(true)
    {

        //Base Condition
        if(queue1->header == NULL && queue2->header == NULL && working_queue1->header == NULL && working_queue2->header == NULL)
        {
            break;
        }

        //Reset
        someone_just_done_the_ticket = false;
        someone_just_come_into_null_working_queue1 = false;

        //Add 5 to time_remaining_to_finish_ticket_reduction , waiting
        //Sub 1 from total ticket
        //Set ready
        //For queue1 first customer PART2
        if(no_one_can_do_ticket_reduction == true)
        {
            time_remaining_to_finish_ticket_reduction += 5;
            first_customer_that_is_doing_ticket->total_ticket -= 1;

            //Add waiting time to queue1
            temp = working_queue1->header;
            while(temp != NULL)
            {
                if(temp != first_customer_that_is_doing_ticket)
                {
                    if(temp->corresponding->ready != -1)
                    {
                        temp->corresponding->waiting += 5;
                    }
                }
                temp = temp->next;
            }

            //Add waiting time to queue2
            temp = working_queue2->header;
            while(temp != NULL)
            {
                if(temp->corresponding->ready != -1)
                {
                    temp->corresponding->waiting += 5;
                }
                temp = temp->next;
            }
        }
        //For queue2 first customer PART2
        else if(working_queue1->header == NULL && working_queue2->header != NULL)
        {
            working_queue2->header->total_ticket -= 1;

            if(working_queue2->header->corresponding->ready == -1)
            {
                if(first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful == true)
                {
                    working_queue2->header->corresponding->waiting += 5;
                }
                working_queue2->header->corresponding->ready = timer;
            }

            //Add waiting time to queue2 (not include first customer in queue2)
            temp = working_queue2->header->next;
            while(temp != NULL)
            {
                if(temp->corresponding->ready != -1)
                {
                    temp->corresponding->waiting += 5;
                }
                temp = temp->next;
            }
        }

        //S1) First Customer in Working Queue 1 done its ticket reduction
        if(time_remaining_to_finish_ticket_reduction == weighted_round_robin_time)
        {
            someone_just_done_the_ticket = true;
            time_remaining_to_finish_ticket_reduction = 0;
            weighted_round_robin_time = -1;
            no_one_can_do_ticket_reduction = false;
            first_customer_going_to_reposition = first_customer_that_is_doing_ticket;
            if(there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 == false)
            {
                working_queue1->header = working_queue1->header->next;                  //<-- we move the working_queue1->header to the next customer
            }
            else if(there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 == true)
            {
                previous_customer->next = first_customer_that_is_doing_ticket->next;
            }

            if(first_customer_going_to_reposition->total_ticket == 0)
            {
                first_customer_in_working_queue1_is_done_and_going_to_result = true;
            }
            else
            {
                first_customer_in_working_queue1_is_done_and_need_to_check_promotion = true;
            }
        }
        //S2) First Customer in Working Queue 2 done its ticket reduction
        else if(working_queue1->header == NULL && working_queue2->header != NULL)
        {
            if(working_queue2->header->total_ticket == 0)
            {
                someone_just_done_the_ticket = true;
                working_queue2->header->corresponding->end = timer;
                customer_result_vector.push_back(working_queue2->header->corresponding);

                working_queue2->header = working_queue2->header->next;
                first_customer_in_working_queue2_is_done_and_timer_need_to_be_careful = true;
            }
        }

        //1) Demotion Working Queue1
        Customer * temp_next = NULL;
        if(first_customer_in_working_queue1_is_done_and_need_to_check_promotion == true)
        {
            if(first_customer_going_to_reposition->age < 1)
            {
                first_customer_in_working_queue1_reposition_to_behind = true;
                first_customer_going_to_reposition->age ++;

                if(there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 == true)
                {
                    previous_customer->next = first_customer_that_is_doing_ticket->next;
                    there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = false;
                }
            }
            else
            {
                first_customer_going_to_reposition->age = 0;
                first_customer_going_to_reposition->priority ++;

                //Check if this first customer is going to queue2
                if(first_customer_going_to_reposition->priority == 4)
                {
                    first_customer_in_working_queue1_reposition_to_queue2 = true;
                    first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful = true;

                    if(there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 == true)
                    {
                        previous_customer->next = first_customer_that_is_doing_ticket->next;
                        there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = false;
                    }
                }
                else
                {
                    first_customer_in_working_queue1_reposition_to_behind = true;
                    if(there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 == true)
                    {
                        previous_customer->next = first_customer_that_is_doing_ticket->next;
                        there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = false;
                    }
                }
            }
            
            //Reset
            first_customer_in_working_queue1_is_done_and_need_to_check_promotion = false;
        }

        //2) Take all Customers from Queue1
        //3) Rearrange Queue1 (in Priority)
        while(queue1->header != NULL && queue1->header->arrival_time <= timer)
        {
            if(working_queue1->header != NULL)
            {
                if(queue1->header->priority < working_queue1->header->priority)
                {

                    //Test case 6 (sub 1) , a6->a10
                    if(working_queue1->header == first_customer_that_is_doing_ticket)
                    {
                        there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = true;
                        previous_customer = queue1->header;
                    }

                    temp = working_queue1->header;
                    working_queue1->header = queue1->header;
                    queue1->header = queue1->header->next;
                    working_queue1->header->next = temp;
                }
                else
                {
                    temp = working_queue1->header;
                    while(temp->next != NULL)
                    {
                        if(queue1->header->priority < temp->next->priority && temp == previous_customer && temp->next == first_customer_that_is_doing_ticket)
                        {
                            there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = true;
                            previous_customer->next = queue1->header;
                            previous_customer = queue1->header;
                            queue1->header = queue1->header->next;
                            previous_customer->next = first_customer_that_is_doing_ticket;
                            break;
                        }
                        else if(queue1->header->priority < temp->next->priority && temp->next == first_customer_that_is_doing_ticket)
                        {
                            there_are_new_customer_in_front_of_working_ticket_first_customer_in_queue1 = true;
                            previous_customer = queue1->header;

                            temp_next = temp->next;
                            temp->next = queue1->header;
                            queue1->header = queue1->header->next;
                            temp->next->next = temp_next;
                            break;
                        }
                        else if(queue1->header->priority < temp->next->priority)
                        {
                            temp_next = temp->next;
                            temp->next = queue1->header;
                            queue1->header = queue1->header->next;
                            temp->next->next = temp_next;
                            break;
                        }
                        else
                        {
                            temp = temp->next;
                        }
                    }

                    //Last position
                    if(temp->next == NULL)
                    {
                        temp->next = queue1->header;
                        queue1->header = queue1->header->next;
                        temp->next->next = NULL;
                    }
                }
            }
            else
            {
                working_queue1->header = queue1->header;
                queue1->header = queue1->header->next;
                working_queue1->header->next = NULL;

                someone_just_come_into_null_working_queue1 = true;
            }
        }

        //4) Reposition first customer in Queue1 (to behind)
        if(first_customer_in_working_queue1_reposition_to_behind == true && working_queue1->header != NULL)
        {
            temp = working_queue1->header;
            //Check the working queue1 header first
            if(first_customer_going_to_reposition->priority < temp->priority)
            {
                working_queue1->header = first_customer_going_to_reposition;
                working_queue1->header->next = temp;
            }
            //Then iterate through the working queue1
            else
            {
                while(temp->next != NULL)
                {
                    if(first_customer_going_to_reposition->priority < temp->next->priority)
                    {
                        temp_next = temp->next;
                        temp->next = first_customer_going_to_reposition;
                        first_customer_going_to_reposition->next = temp_next;
                        break;
                    }
                    else
                    {
                        temp = temp->next;
                    }
                }

                //Last position
                if(temp->next == NULL)
                {
                    temp->next = first_customer_going_to_reposition;
                    first_customer_going_to_reposition->next = NULL;
                }
            }
            
            //Reset
            first_customer_in_working_queue1_reposition_to_behind = false;
        }
        else if(first_customer_in_working_queue1_reposition_to_behind == true && working_queue1->header == NULL)
        {
            working_queue1->header = first_customer_going_to_reposition;
            first_customer_going_to_reposition->next = NULL;

            //Reset
            first_customer_in_working_queue1_reposition_to_behind = false;
        }

        //5) Reposition first customer in Queue1 (to queue2)
        //This need to happen before new arrival of new customers in working queue2
        else if(first_customer_in_working_queue1_reposition_to_queue2 == true && working_queue2->header != NULL)
        {
            if(first_customer_going_to_reposition->total_ticket < working_queue2->header->total_ticket)
            {
                temp = working_queue2->header;
                working_queue2->header = first_customer_going_to_reposition;
                first_customer_going_to_reposition->next = temp;
            }
            else
            {
                temp = working_queue2->header;
                while(temp->next != NULL)
                {
                    if(first_customer_going_to_reposition->total_ticket < temp->next->total_ticket)
                    {
                        temp_next = temp->next;
                        temp->next = first_customer_going_to_reposition;
                        first_customer_going_to_reposition->next = temp_next;
                        break;
                    }
                    else
                    {
                        temp = temp->next;
                    }
                }

                if(temp->next == NULL)
                {
                    temp->next = first_customer_going_to_reposition;
                    first_customer_going_to_reposition->next = NULL;
                }
            }

            //Reset
            first_customer_in_working_queue1_reposition_to_queue2 = false;
        }
        else if(first_customer_in_working_queue1_reposition_to_queue2 == true && working_queue2->header == NULL)
        {
            working_queue2->header = first_customer_going_to_reposition;
            first_customer_going_to_reposition->next = NULL;

            //Reset
            first_customer_in_working_queue1_reposition_to_queue2 = false;
        }

        //6) Take all Customers from Queue2
        //7) Rearrange Queue2 (in Shortest Remaining)
        bool one_time_only = true;
        while(queue2->header != NULL && queue2->header->arrival_time <= timer)
        {
            if(working_queue2->header != NULL)
            {
                if(queue2->header->total_ticket < working_queue2->header->total_ticket)
                {
                    //if new_customer substitute new_customer(working_queue2) , that does not count
                    if(one_time_only == true && first_customer_in_working_queue2_is_done_and_timer_need_to_be_careful == false)
                    {
                        previous_first_customer_in_queue2 = working_queue2->header;                 //<--
                        first_customer_in_working_queue2_is_substitute_by_new_customer = true;      //<--
                        one_time_only = false;
                    }
                    temp = working_queue2->header;
                    working_queue2->header = queue2->header;
                    queue2->header = queue2->header->next;
                    working_queue2->header->next = temp;
                }
                else
                {
                    temp = working_queue2->header;
                    while(temp->next != NULL)
                    {
                        if(queue2->header->total_ticket < temp->next->total_ticket)
                        {
                            temp_next = temp->next;
                            temp->next = queue2->header;
                            queue2->header = queue2->header->next;
                            temp->next->next = temp_next;
                            break;
                        }
                        else
                        {
                            temp = temp->next;
                        }
                    }

                    //Last
                    if(temp->next == NULL)
                    {
                        temp->next = queue2->header;
                        queue2->header = queue2->header->next;
                        temp->next->next = NULL;
                    }
                }
            }
            else
            {
                working_queue2->header = queue2->header;
                queue2->header = queue2->header->next;
                working_queue2->header->next = NULL;
            }
        }

        //Result
        if(first_customer_in_working_queue1_is_done_and_going_to_result == true)
        {
            first_customer_going_to_reposition->corresponding->end = timer;
            
            customer_result_vector.push_back(first_customer_going_to_reposition->corresponding);

            //False
            first_customer_in_working_queue1_is_done_and_going_to_result = false;
        }

        //S3) Do Ticket Reduction (in Queue1)
        if(working_queue1->header != NULL)
        {
            //Another customer is ready for reduction
            if(no_one_can_do_ticket_reduction == false)
            {
                no_one_can_do_ticket_reduction = true;

                //Check for the total tickets to set a time
                if(working_queue1->header->total_ticket < ((10 - working_queue1->header->priority) * 10 / 5) )
                {
                    weighted_round_robin_time = working_queue1->header->total_ticket * 5;
                }
                else
                {
                    weighted_round_robin_time = (10 - working_queue1->header->priority) * 10;
                }     

                if(working_queue1->header->corresponding->ready == -1)
                {
                    working_queue1->header->corresponding->ready = timer;
                }

                first_customer_that_is_doing_ticket = working_queue1->header;
            }
        }

        //For queue1 first customer PART1
        if(no_one_can_do_ticket_reduction == true)
        {
            //Add age to queue2
            temp = working_queue2->header;
            while(temp != NULL)
            {
                if(temp == first_customer_going_to_reposition && first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful == true)
                {
                    first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful = false;
                }
                else if(temp->arrival_time != timer && someone_just_come_into_null_working_queue1 == false)
                {
                    temp->age += 5;
                }

                temp = temp->next;
            }
        }
        //For queue2 first customer PART1
        else if(working_queue1->header == NULL && working_queue2->header != NULL)
        {
            //Add age to queue2
            if(first_customer_in_working_queue2_is_done_and_timer_need_to_be_careful == true)
            {
                temp = working_queue2->header;
                first_customer_in_working_queue2_is_done_and_timer_need_to_be_careful = false;
            }
            else
            {
                //First Customer in queue2
                temp = working_queue2->header;
                if(temp != NULL && first_customer_in_working_queue2_is_substitute_by_new_customer == false && someone_just_done_the_ticket == false)
                {
                    //Reset age to 0
                    temp->age = 0;
                }

                if(someone_just_done_the_ticket == true)
                {
                    temp = working_queue2->header;
                }
                else
                {
                    temp = working_queue2->header->next;
                }
                
            }
            while(temp != NULL)
            {
                if(temp == first_customer_going_to_reposition && first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful == true)
                {
                    first_customer_in_working_queue1_is_demote_to_queue2_and_timer_need_to_be_careful = false;
                }
                else if(temp == previous_first_customer_in_queue2 && first_customer_in_working_queue2_is_substitute_by_new_customer == true)
                {
                    previous_first_customer_in_queue2 = NULL;
                    first_customer_in_working_queue2_is_substitute_by_new_customer = false;
                }
                else if(temp->arrival_time != timer)
                {
                    temp->age += 5;
                }
                
                temp = temp->next;
            }
        }

        //8) Promotion Working Queue2
        //Look for Working Queue 1 last customer
        bool working_queue1_is_empty = false;
        bool one_time_only_two = true;
        if(working_queue1->header == NULL)
        {
            working_queue1_is_empty = true;
        }
        else
        {
            temp = working_queue1->header;
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            last_position = temp;
            working_queue1_is_empty = false;
        } 
        temp = working_queue2->header;

        //Check if Working Queue2 first customer
        while(temp != NULL && temp == working_queue2->header)
        {
            if(temp->age >= 100 && temp->priority == 4)
            {
                if(working_queue1_is_empty == false)
                {
                    working_queue2->header = working_queue2->header->next;
                    last_position->next = temp;
                    temp->next = NULL;
                    temp->age = 0;
                    temp->priority--;
                    last_position = last_position->next;
                    temp = working_queue2->header;
                }
                else if(working_queue1_is_empty == true)
                {
                    working_queue2->header = working_queue2->header->next;
                    working_queue1->header = temp;
                    temp->next = NULL;
                    temp->age = 0;
                    temp->priority--;
                    last_position = working_queue1->header;
                    temp = working_queue2->header;
                    working_queue1_is_empty = false;

                    //
                    if(one_time_only_two == true)
                    {
                        customer_in_working_queue2_is_promoted_to_queue1_when_queue1_is_NULL = true;
                        first_of_several_customer_that_is_promote_to_queue1_when_queue1_is_NULL = last_position;
                        one_time_only_two = false;
                    }
                }
            }
            else if(temp->age >= 100 && temp->priority > 4)
            {
                temp->age -= 100;
                temp->priority --;
                break;
            }
            else
            {
                break;
            }
        }
        //If not first customer in Working Queue 2
        if(temp != NULL)
        {
            while(temp->next != NULL)
            {
                if(temp->next->age >= 100 && temp->next->priority == 4)
                {
                    if(working_queue1_is_empty == false)
                    {
                        temp->next->age = 0;
                        temp->next->priority--;
                        last_position->next = temp->next;
                        temp->next = temp->next->next;
                        last_position->next->next = NULL;
                        last_position = last_position->next;
                    }
                    else if(working_queue1_is_empty == true)
                    {
                        temp->next->age = 0;
                        temp->next->priority--;
                        working_queue1->header = temp->next;
                        temp->next = temp->next->next;
                        working_queue1->header->next = NULL;
                        last_position = working_queue1->header;

                        working_queue1_is_empty = false;

                        //
                        if(one_time_only_two == true)
                        {
                            customer_in_working_queue2_is_promoted_to_queue1_when_queue1_is_NULL = true;
                            first_of_several_customer_that_is_promote_to_queue1_when_queue1_is_NULL = last_position;
                            one_time_only_two = false;
                        }
                    }
                }
                else if(temp->next->age >= 100 && temp->next->priority > 4)
                {
                    temp->next->age -= 100;
                    temp->next->priority--;
                    temp = temp->next;
                }
                else
                {
                    temp = temp->next;
                }
            }
        }

        //
        if(working_queue2->header != NULL && no_one_can_do_ticket_reduction == false && customer_in_working_queue2_is_promoted_to_queue1_when_queue1_is_NULL == false)
        {
            if(working_queue2->header->corresponding->ready == -1)
            {
                working_queue2->header->corresponding->ready = timer;
            }
        }

        //Quick set up for new customer promote from queue2 to queue1
        if(customer_in_working_queue2_is_promoted_to_queue1_when_queue1_is_NULL == true)
        {
            //Another customer is ready for reduction
            if(no_one_can_do_ticket_reduction == false)
            {
                no_one_can_do_ticket_reduction = true;

                //Check for the total tickets to set a time
                if(working_queue1->header->total_ticket < ((10 - working_queue1->header->priority) * 10 / 5) )
                {
                    weighted_round_robin_time = working_queue1->header->total_ticket * 5;
                }
                else
                {
                    weighted_round_robin_time = (10 - working_queue1->header->priority) * 10;
                }     

                if(working_queue1->header->corresponding->ready == -1)
                {
                    working_queue1->header->corresponding->ready = timer;
                }
            }
            
            first_customer_that_is_doing_ticket = working_queue1->header;

            customer_in_working_queue2_is_promoted_to_queue1_when_queue1_is_NULL = false;
        }
        

        timer += 5;
    }   
}

//Print the output from Customer_result vector
void output()
{
    int i;
    int k = 0;
    int digit_counter = 1;
    int temp = 0;
    string spacing = "          ";

    cout << "name   arrival   end   ready   running   waiting" << endl;
    for(i = 0 ; i < customer_result_vector.size(); i++) // every result
    {
        cout << customer_result_vector[i]->name;
        while(k < 5)
        {
            switch(k)
            {
                case 0:
                    temp = customer_result_vector[i]->arrival;
                    break;
                case 1:
                    temp = customer_result_vector[i]->end;
                    break;
                case 2:
                    temp = customer_result_vector[i]->ready;
                    break;
                case 3:
                    temp = customer_result_vector[i]->running;
                    break;
                case 4:
                    temp = customer_result_vector[i]->waiting;
                    break;
                default:
                    break;
            }

            //Find digit
            while ( temp >= 10 )
            {
                temp = temp / 10;
                digit_counter++;
            }

            //Set indentation
			
            switch(k)
            {
                case 0:
                    cout << spacing.substr(0 , 10 - digit_counter) << customer_result_vector[i]->arrival;
                    break;
                case 1:
                    cout << spacing.substr(0 , 10 - digit_counter) << customer_result_vector[i]->end;
                    break;
                case 2:
                    cout << spacing.substr(0 , 10 - digit_counter) << customer_result_vector[i]->ready;
                    break;
                case 3:
                    cout << spacing.substr(0 , 10 - digit_counter) << customer_result_vector[i]->running;
                    break;
                case 4:
                    cout << spacing.substr(0 , 10 - digit_counter) << customer_result_vector[i]->waiting;
                    break;
                default:
                    break;
            }
            
            //Reset
            k++;
            digit_counter = 1;
            temp = 0;
        }
        cout << endl;
        k = 0;
    }
    cout << endl;
}

int main(int argc,char *argv[])
{
    int i,j,k;
    freopen(argv[1],"r",stdin);

    initial();        // initial data
    input();          // input data
    works();          // process data
    output();         // output result
    return 0;
}