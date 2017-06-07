//Initial code by Naser Al Madi (Zero-Cool)
//Operating Systems - Scheduling project
//21-OCT-2016
//student name: Luke Gulley
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>


//data process ID, Burst time, and priority
//size is the size of the arrays or data records
std::string pID[10];
int burst[10];
int priority[10];
int size;

//checks if array is empty (all 0s)
bool isEmpty(int arr[]) {
    bool result = true;
    for(int i = 0; i < size; i++) {
        if((arr[i]) != 0) {
            result = false;
        }
    }
    return result;
}

//the function initializes the data arrays with records from the file stream
void initFrom(std::ifstream& in){
    
    std::string id, temp;
    int b_time;
    int proi;
    int i = 0;
    
    //prints out the header of the file
    if (!in.eof()){
        in>>id;
        std::cout<<"\n"<<id<<"\t";
        in>>temp;
        std::cout<<temp<<"\t";
        in>>temp;
        std::cout<<temp<<"\n";
    }
    
    //reading in data from the file and storing it in the right array
    while (!in.eof() && in>>id && in>>b_time && in>>proi && i < 10){
        
        pID[i] = id;
        std::cout<<pID[i]<<"\t";
        
        burst[i] = b_time;
        std::cout<< burst[i]<<"\t";
        
        priority[i] = proi;
        std::cout<<priority[i]<<"\n";
        i++;
    }
    //the size of the arrays is the same
    size = i;
    std::cout<<"size: "<<size;
    std::cout<<"\nDone reading data from file\n";
}

//First Come First Serve implementation, this is a working example to show you how the output could look like
void myFCFS(){
    int wait_t[10];
    int turn_t[10];
    double avg_wait=0;
    double avg_turn=0;
    int i=0;
    int t=0;
    
    std::cout<<"\nPID\twait\tturnaround\n";
    
    //calculating wait-time and turnarround-time for each process
    while (i<size){
        //compute wait time
        wait_t[i]=t;
        t = t + burst[i];
        //compute turnaround time
        turn_t[i]=wait_t[i] + burst[i];
        
        std::cout<<"P"<<i+1<<"\t"<<wait_t[i]<<"\t"<<turn_t[i]<<"\n";
        i++;
    }
    
    //calculating the averages of wait time and turnaround time
    i=0;
    while(i<size){
        avg_wait = avg_wait +  wait_t[i];
        avg_turn = avg_turn + turn_t[i];
        i++;
    }
    
    avg_wait = avg_wait/size;
    avg_turn = avg_turn/size;
    
    //printing the averages
    std::cout<<"AVG wait is: "<<avg_wait<<"\n";
    std::cout<<"AVG turnaround is: "<<avg_turn<<"\n";
    
}


void mySJF() {
    //initializes array containing indices of burst/pID order
    int sortedInd[10];
    int r = 0;
    while (r < size) {
        sortedInd[r] = r;
        r++;
    }
    
    
    //sorts first array by value, using indices in the second array
    for(int i =0; i < size; i++) {
        for(int j = 0; j < size - 1; j++) {
            if(burst[sortedInd[j+1]] < burst[sortedInd[j]]) {
                std::swap(sortedInd[j], sortedInd[j+1]);
            }
        }
    }
    
    std::cout<<"\nPID\twait\tturnaround\n";
    
    
    int total_wait = 0;
    int total_turn = 0;
    int wait[10];
    int turn[10];
    for(int i =0; i < size; i++) {
        //prints pID
        std::cout << pID[sortedInd[i]];
        //prints wait time
        wait[i] = total_wait;
        std::cout << "\t" << wait[i];
        total_wait += burst[sortedInd[i]];
        //prints turnaround
        turn[i] = total_wait;
        total_turn += burst[sortedInd[i]];
        std::cout << "\t" << turn[i] << "\n";
    }
    
    double avg_wait = 0;
    double avg_turn = 0;
    for(int i = 0; i < size; i++) {
        avg_wait += wait[i];
        avg_turn += turn[i];
    }
    
    avg_wait /= size;
    avg_turn /= size;
    
    
    //printing the averages
    std::cout<<"AVG wait is: "<<avg_wait<<"\n";
    std::cout<<"AVG turnaround is: "<<avg_turn<<"\n";
}

void myPriority(){
    //initializes array containing indices of priority/pID order
    int sortedInd[10];
    int r = 0;
    while (r < size) {
        sortedInd[r] = r;
        r++;
    }
    
    
    //sorts first array by value, using indices in the second array
    for(int i =0; i < size; i++) {
        for(int j = 0; j < size - 1; j++) {
            if(priority[sortedInd[j+1]] > priority[sortedInd[j]]) {
                std::swap(sortedInd[j], sortedInd[j+1]);
            }
        }
    }
    
    std::cout<<"\nPID\twait\tturnaround\n";
    
    int total_wait = 0;
    int total_turn = 0;
    int wait[10];
    int turn[10];
    for(int i =0; i < size; i++) {
        //prints pID
        std::cout << pID[sortedInd[i]];
        //prints wait time
        wait[i] = total_wait;
        std::cout << "\t" << wait[i];
        total_wait += burst[sortedInd[i]];
        //prints turnaround
        turn[i] = total_wait;
        total_turn += burst[sortedInd[i]];
        std::cout << "\t" << turn[i] << "\n";
    }
    
    double avg_wait = 0;
    double avg_turn = 0;
    for(int i = 0; i < size; i++) {
        avg_wait += wait[i];
        avg_turn += turn[i];
    }
    
    avg_wait /= size;
    avg_turn /= size;
    
    
    //printing the averages
    std::cout<<"AVG wait is: "<<avg_wait<<"\n";
    std::cout<<"AVG turnaround is: "<<avg_turn<<"\n";
}

void myLJF(){
    //initializes array containing indices of burst/pID order
    int sortedInd[10];
    int r = 0;
    while (r < size) {
        sortedInd[r] = r;
        r++;
    }
    
    
    //sorts first array by value, using indices in the second array
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - 1; j++) {
            if(burst[sortedInd[j+1]] > burst[sortedInd[j]]) {
                std::swap(sortedInd[j], sortedInd[j+1]);
            }
        }
    }
    
    std::cout<<"\nPID\twait\tturnaround\n";
    
    
    int total_wait = 0;
    int total_turn = 0;
    int wait[10];
    int turn[10];
    for(int i =0; i < size; i++) {
        //prints pID
        std::cout << pID[sortedInd[i]];
        //prints wait time
        wait[i] = total_wait;
        std::cout << "\t" << wait[i];
        total_wait += burst[sortedInd[i]];
        //prints turnaround
        turn[i] = total_wait;
        total_turn += burst[sortedInd[i]];
        std::cout << "\t" << turn[i] << "\n";
    }
    
    double avg_wait = 0;
    double avg_turn = 0;
    for(int i = 0; i < size; i++) {
        avg_wait += wait[i];
        avg_turn += turn[i];
    }
    
    avg_wait /= size;
    avg_turn /= size;
    
    
    //printing the averages
    std::cout<<"AVG wait is: "<<avg_wait<<"\n";
    std::cout<<"AVG turnaround is: "<<avg_turn<<"\n";
}
void myRR() {
    int start[10];
    int wait[10];
    int turn[10];
    int tmpBurst[10];
    int count = 0;
    
    for(int r = 0; r < 10; r++) {
        start[r] = 0;
        wait[r] = 0;
        turn[r] = 0;
    }
    
    //copys burst to tmp array for modifying
    for(int q = 0; q < 10; q++) {
        tmpBurst[q] = burst[q];
    }
    
    for(int j = 0; !isEmpty(tmpBurst); j++) {
        for(int i = 0; i < size; i++) {
            if(tmpBurst[i] >= 2) {
                wait[i] += count - start[i];
                count+= 2;
                tmpBurst[i] -= 2;
                if(tmpBurst[i] == 0) {
                    turn[i] = count;
                }
                start[i] = count;
            }
            else if(tmpBurst[i] == 1) {
                wait[i] += count - start[i];
                count+= 1;
                tmpBurst[i] -= 1;
                if(tmpBurst[i] == 0) {
                    turn[i] = count;
                }
                start[i] = count;
            }
        }
    }
    
    std::cout<<"\nPID\twait\tturnaround\n";
    
    for(int i = 0; i < size; i++) {
        std::cout << pID[i] << "\t" << wait[i] << "\t" << turn[i] << "\n";
    }
    
    double avg_wait = 0;
    double avg_turn = 0;
    for(int i = 0; i < size; i++) {
        avg_wait += wait[i];
        avg_turn += turn[i];
    }
    
    avg_wait /= size;
    avg_turn /= size;
    
    
    //printing the averages
    std::cout<<"AVG wait is: "<<avg_wait<<"\n";
    std::cout<<"AVG turnaround is: "<<avg_turn<<"\n";
}

int main (){
    //open a file stream
    std::ifstream file ("proc.txt");
    
    if (!file){
        std::cerr<<"Error, could not open file.\n";
        return 1;
    }
    initFrom(file);
    
    int alg;
    //this outputs the usage message
    while (true){
        
        std::cout<<"\nWhich scheduling algorithm do you want to run?\n1. First Come First Serve (FCFS)\n2. Shortest Job First (SJF)\n3. Priority (p)\n4. Longest Job First (LJF)\n5. Round-Robin (RR)\n0. Exit\n: ";
        std::cin>>alg;
        if(alg == 0) { break; }
        
        switch(alg) {
            case 1: myFCFS();
                break;
            case 2: mySJF();
                break;
            case 3: myPriority();
                break;
            case 4: myLJF();
                break;
            case 5: myRR();
                break;
            default: std::cout<<"\nInvalid choice. Please select a number between 1 and 5.\n";
        }
    }
    
    return 0;
}
