#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

class Process
{
	int arrivalTime;
	int burstTime;
	int priority;
public:
	Process(int arrivalTime, int burstTime, int priority)
		: arrivalTime(arrivalTime), burstTime(burstTime), priority(priority) {}
	Process(int arrivalTime, int burstTime)
		: arrivalTime(arrivalTime), burstTime(burstTime) {}
	int getArrivalTime(){return arrivalTime;}
	int getBurstTime(){return burstTime;}
	int getPriority(){return priority;}
	void setBurstTime(int burstTime){this->burstTime = burstTime;}
};

class ProcessPoint : public Process
{
	int processNum;
public:
	ProcessPoint(int processNum, Process process)
		: processNum(processNum), Process(process) {}
	int getProcessNum(){return processNum;}
};

class GanttChart : public ProcessPoint
{
	int startTime;
	int finishTime;
public:
	GanttChart(ProcessPoint processPoint, int startTime, int finishTime)
		: ProcessPoint(processPoint), startTime(startTime), finishTime(finishTime) {}
	int getStartTime(){return startTime;}
	int getFinishTime(){return finishTime;}
};

void sortArrivalTime(vector<ProcessPoint>& sortVec)
{
	for(int i=0; i<sortVec.size(); i++)
	{
		for(int j=i+1; j<sortVec.size(); j++)
		{
			if(sortVec[i].getArrivalTime() > sortVec[j].getArrivalTime())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}
}

void sortPriority(vector<ProcessPoint>& sortVec)
{
	for(int i=0; i<sortVec.size(); i++)
	{
		for(int j=i+1; j<sortVec.size(); j++)
		{
			if(sortVec[i].getPriority() > sortVec[j].getPriority())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}
}

void sortBurstTime(vector<ProcessPoint>& sortVec)
{
	for(int i=0; i<sortVec.size(); i++)
	{
		for(int j=i+1; j<sortVec.size(); j++)
		{
			if(sortVec[i].getBurstTime() > sortVec[j].getBurstTime())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}
}

void sortStartingPriority(vector<ProcessPoint>& sortVec)
{
	int counter = 0;
	for(int i=1; i<sortVec.size(); i++)
	{
		if(sortVec[0].getArrivalTime() == sortVec[i].getArrivalTime())
			counter++;
	}

	for(int i=0; i<counter+1; i++)
	{
		for(int j=i+1; j<counter+1; j++)
		{
			if(sortVec[i].getPriority() > sortVec[j].getPriority())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}
}

void sortStartingBurstTime(vector<ProcessPoint>& sortVec)
{
	int counter = 0;
	for(int i=1; i<sortVec.size(); i++)
	{
		if(sortVec[0].getArrivalTime() == sortVec[i].getArrivalTime())
			counter++;
	}

	for(int i=0; i<counter+1; i++)
	{
		for(int j=i+1; j<counter+1; j++)
		{
			if(sortVec[i].getBurstTime() > sortVec[j].getBurstTime())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}
}

void sortBurstTimeWithArrival(vector<ProcessPoint>& sortVec)
{
	int counter = 0;
	for(int i=0; i<sortVec.size(); i++)
	{
		for(int j=i+1; j<sortVec.size(); j++)
		{
			if(sortVec[i].getBurstTime() > sortVec[j].getBurstTime())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}

	for(int i=1; i<sortVec.size(); i++)
	{
		if(sortVec[0].getBurstTime() == sortVec[i].getBurstTime())
			counter++;
	}

	for(int i=0; i<counter+1; i++)
	{
		for(int j=i+1; j<counter+1; j++)
		{
			if(sortVec[i].getArrivalTime() > sortVec[j].getArrivalTime())
			{
				ProcessPoint temp = sortVec[i];
				sortVec[i] = sortVec[j];
				sortVec[j] = temp;
			}
		}
	}
}

void displayGC(vector<GanttChart> ganttChart)
{
	int loop = 0;
	for(int i=0; i<ganttChart.size(); i++)
		if(ganttChart[i].getProcessNum() != ganttChart[i+1].getProcessNum())
			loop++;

	cout << endl << "Gantt Chart: " << endl << "=";
	for(int i=0; i<loop; i++)
	{
		cout << "=======";
	}
	cout << endl << "|  ";
	for(int i=0; i<ganttChart.size(); i++)
	{
		if(ganttChart[i].getProcessNum() != ganttChart[i+1].getProcessNum())
		{
			if(ganttChart[i].getProcessNum() > 9)
				cout << "P" << ganttChart[i].getProcessNum() << " |  ";
			else
				cout << "P" << ganttChart[i].getProcessNum() << "  |  ";
		}
	}
	cout << endl << "=";
	for(int i=0; i<loop; i++)
		cout << "=======";
	cout << endl << ganttChart[0].getStartTime();
	for(int i=0; i<ganttChart.size(); i++)
	{
		if(ganttChart[i].getProcessNum() != ganttChart[i+1].getProcessNum())
		{
			if(ganttChart[i].getFinishTime() > 9)
				cout << "     " << ganttChart[i].getFinishTime();
			else
				cout << "      " << ganttChart[i].getFinishTime();
		}
	}
	cout << endl << endl;
}

void displayMainMenu(int& method)
{
	bool errorChecking = true;
	system("cls");
	while(errorChecking)
	{
		cout << "================================================" << endl;
		cout << "|     TSN2101 - Operating System Assignment    |" << endl;
		cout << "|    Simulation of CPU Scheduling Algorithms   |" << endl;
		cout << "================================================" << endl;
		cout << "Section: TC01 TT03" << endl << endl;
		cout << "Prepared by: " << endl;
		cout << "Name: Nicholas Tan Yu Zhe\tID: 1142701655" << endl;
		cout << "Name: Ng Kang Jie\t\tID: 1142700809" << endl;
		cout << "Name: Liew Soon Pang\t\tID: 1142700808" << endl;
		cout << "Name: Choo Jia Sheng\t\tID: 1142700814" << endl << endl;

		cout << "1. First Come First Served" << endl;
		cout << "2. Round Robin" << endl;
		cout << "3. Three-level Queue" << endl;
		cout << "4. Shortest Remaining Time" << endl;
		cout << "5. Run all together" << endl;
		cout << "0. Quit" << endl;
		cout << "Please choose which scheduling method you prefer" << endl;
		cout << "-> ";
		cin >> method;
		if(method < 0 || method > 5)
			cout << "Please enter from 0 - 5" << endl;
		else
			errorChecking = false;
	}
	if(method == 0)
		exit(0);
}

void displayProcess(vector<ProcessPoint> original, int method, int quantum)
{
	cout << "Process Detail: " << endl;
	if(method == 1 || method == 3 || method == 5)
	{
		cout << "     ProcessID\t   Arrival Time\t   Burst Time\t   Priority" << endl;
		for(int i=0; i<original.size(); i++)
			cout << "\t" << original[i].getProcessNum() << "\t\t" << original[i].getArrivalTime() << "\t\t" << original[i].getBurstTime() << "\t\t" << original[i].getPriority() << endl;
	}
	else if(method == 2 || method == 4)
	{
		cout << "     ProcessID\t   Arrival Time\t   Burst Time" << endl;
		for(int i=0; i<original.size(); i++)
			cout << "\t" << original[i].getProcessNum() << "\t\t" << original[i].getArrivalTime() << "\t\t" << original[i].getBurstTime() << endl;
	}
	if(method == 2 || method == 3 || method == 5)
		cout << "Quantum: " << quantum << endl;
	cout << endl;
}

void displayProcessDetail(vector<int>& turnAroundTime, vector<int>& waitingTime)
{
	cout << "     ProcessID\tTurnaround Time\t   Waiting Time" << endl;
	for(int i=0; i<turnAroundTime.size(); i++)
		cout << "\t" << i+1 << "\t\t" << turnAroundTime[i] << "\t\t" << waitingTime[i] << endl;
}

void calculateTurnAroundTime(vector<GanttChart> ganttChart, vector<ProcessPoint> original, vector<int>& turnAroundTime)
{
	vector<int> final;

	for(int i=0; i<original.size(); i++)
	{
		for(int j=ganttChart.size()-1; j>-1; j--)
		{
			if(original[i].getProcessNum() == ganttChart[j].getProcessNum())
			{
				final.push_back(ganttChart[j].getFinishTime());
				break; 
			}
		}
	}

	for(int i=0; i<original.size(); i++)
		turnAroundTime.push_back(final[i] - original[i].getArrivalTime());
}

void calculateWaitingTime(vector<ProcessPoint> original, vector<int> turnAroundTime, vector<int>& waitingTime)
{
	for(int i=0; i<original.size(); i++)
		waitingTime.push_back(turnAroundTime[i] - original[i].getBurstTime());
}

double calculateAverageTurnaroundTime(vector<int> turnAroundTime)
{
	double sum, avg;

	for(int i=0; i<turnAroundTime.size(); i++)
		sum = sum + turnAroundTime[i];

	avg = sum/turnAroundTime.size();

	return avg;
}

double calculateAverageWaitingTime(vector<int> waitingTime)
{
	double sum, avg;

	for(int i=0; i<waitingTime.size(); i++)
		sum = sum + waitingTime[i];

	avg = sum/waitingTime.size();

	return avg;
}

void getTotalProcesses(int& totalProcesses, int& quantum, int method)
{
	bool errorChecking = true;

	while(errorChecking)
	{
		cout << "How many processes in total? (3-10)" << endl;
		cout << "-> ";
		cin >> totalProcesses;

		if(totalProcesses < 3 || totalProcesses > 10)
		{
			cout << "Please enter from 3 to 10" << endl;
			system("pause");
			system("cls");
		}
		else
			errorChecking = false;
	}
	if(method == 2 || method == 3|| method == 5)
	{
		cout << "What is the time quantum?" << endl;
		cout << "-> ";
		cin >> quantum;
	}
}

void getProcessDetail(vector<ProcessPoint>& original, vector<ProcessPoint>& sortVec1, vector<ProcessPoint>& sortVec2, vector<ProcessPoint>& sortVec3, vector<ProcessPoint>& sortVec4, int totalProcesses, int method)
{
	int arrivalTime, burstTime, priority;
	bool errorChecking;

	for(int i=0; i<totalProcesses; i++)
	{
		cout << endl << "Detail of process " << i+1 << endl;
		cout << "Arrival Time: ";
		cin >> arrivalTime;
		cout << "Burst Time: ";
		cin >> burstTime;

		if(method == 1 || method == 3 || method == 5)
		{
			errorChecking = true;
			while(errorChecking)
			{
				cout << "Priority (1-6): ";
				cin >> priority;

				if(priority < 1 || priority > 6)
					cout << "Please enter from 1 to 6" << endl;
				else
					errorChecking = false;
			}
			sortVec1.push_back(ProcessPoint(i+1, Process(arrivalTime, burstTime, priority)));
			sortVec3.push_back(ProcessPoint(i+1, Process(arrivalTime, burstTime, priority)));
			original.push_back(ProcessPoint(i+1, Process(arrivalTime, burstTime, priority)));
		}
		if(method == 2 || method == 4 || method == 5)
		{
			sortVec2.push_back(ProcessPoint(i+1, Process(arrivalTime, burstTime)));
			sortVec4.push_back(ProcessPoint(i+1, Process(arrivalTime, burstTime)));
			if(method != 5)
				original.push_back(ProcessPoint(i+1, Process(arrivalTime, burstTime)));
		}
	}
}

void getTotalBurstTime(int& totalBurstTime, vector<ProcessPoint> sortVec)
{
	totalBurstTime = sortVec[0].getArrivalTime();
	for(int i=0; i<sortVec.size(); i++)     //To calculate total time required
		totalBurstTime = totalBurstTime + sortVec[i].getBurstTime();
}

int main()
{
	int totalProcesses, arrivalTime, burstTime, priority, quantum, totalBurstTime = 0, counter = 0, method, increaseTime;
	bool errorChecking, sortVector = true, clear = false, firstEnter = true;
	vector<int> turnAroundTime1;
	vector<int> waitingTime1;
	vector<int> turnAroundTime2;
	vector<int> waitingTime2;
	vector<int> turnAroundTime3;
	vector<int> waitingTime3;
	vector<int> turnAroundTime4;
	vector<int> waitingTime4;
	vector<int> schedulingNumber;
	vector<double> avgTurnAroundTime;
	vector<ProcessPoint> original;
	vector<ProcessPoint> sortVec1;
	vector<ProcessPoint> sortVec2;
	vector<ProcessPoint> sortVec3;
	vector<ProcessPoint> sortVec4;
	vector<ProcessPoint> tempVec;
	vector<ProcessPoint> readyQueue;
	vector<ProcessPoint> queue1;
	vector<ProcessPoint> queue2;
	vector<ProcessPoint> queue3;
	vector<GanttChart> ganttChart;

	displayMainMenu(method);

	getTotalProcesses(totalProcesses, quantum, method);

	getProcessDetail(original, sortVec1, sortVec2, sortVec3, sortVec4, totalProcesses, method);

	sortArrivalTime(sortVec1);
	sortArrivalTime(sortVec2);
	sortArrivalTime(sortVec3);
	sortArrivalTime(sortVec4);

	if(method == 1 || method == 3 || method == 5)
		getTotalBurstTime(totalBurstTime, sortVec1);
	else if(method == 2 || method == 4)
		getTotalBurstTime(totalBurstTime, sortVec2);

	system("cls");
	displayProcess(original, method, quantum);

	if(method == 1 || method == 5)     //FCFS
	{
		sortStartingPriority(sortVec1);

		for(int k=0; k<totalBurstTime; k++)
		{
			//To make sure the starting time is the first arrival time
			if(firstEnter)
			{
				k = sortVec1[0].getArrivalTime();
				firstEnter = false;
			}
			//If sortVector is true, pushback from the sortvec1. If false, puchback from the tempVec
			if(sortVector)
			{
				sortVec1[0].setBurstTime(sortVec1[0].getBurstTime()-1);
				ganttChart.push_back(GanttChart(sortVec1[0], k, k+1));
			}
			else
			{
				tempVec[0].setBurstTime(tempVec[0].getBurstTime()-1);
				ganttChart.push_back(GanttChart(tempVec[0], k, k+1));
			}

			//If the first process burst time in tempVec is 0, erase it
			if(!tempVec.empty())
				if(tempVec[0].getBurstTime() == 0)
					tempVec.erase(tempVec.begin());

			//If the first process burst time in sortVec1 is 0, erase it and set clear to true to check more condition
			if(!sortVec1.empty())
				if(sortVec1[0].getBurstTime() == 0)
				{
					sortVec1.erase(sortVec1.begin());
					clear = true;
				}

			if(!sortVec1.empty())     //To check sortVec1 is empty or not
			{
				//If clear is true, check more condition. If false, skip
				if(clear)
				{
					if(!tempVec.empty())
					{
						if(k+1 > sortVec1[1].getArrivalTime() && k+1 > tempVec[1].getArrivalTime()) //If the future time is greater than sortVec1 arrival time and tempVec arrival time, check more condition to choose which process to run
						{
							if(tempVec[0].getArrivalTime() > sortVec1[0].getArrivalTime())
								sortVector = false;
							else if(tempVec[0].getArrivalTime() < sortVec1[0].getArrivalTime())
								sortVector = true;
							else if(tempVec[0].getArrivalTime() < sortVec1[0].getArrivalTime())
								if(tempVec[0].getBurstTime() < sortVec1[0].getBurstTime())
									sortVector = false;
								else if(tempVec[0].getBurstTime() >= sortVec1[0].getBurstTime())
									sortVector = true;
						}
					}
					clear = false;
				}
				else if(sortVec1.size() == 1) //If only 1 process in sortVec1, straight pushback
					sortVector = true;
				else if(k+1 < sortVec1[1].getArrivalTime())     //The time havent reach the next arrival time
					sortVector = true;
				else if(k+1 >= sortVec1[1].getArrivalTime())
				{
					if(sortVec1[0].getBurstTime() != 0)     //If the current process have finish the process, no need to check its priority but check for the new and tempVec[0] priority
					{
						if(sortVec1[0].getPriority() <= sortVec1[1].getPriority()) //If sortVec1[0] priority is smaller or equal than sortVec[1] priority, continue run process. If false, preempt the current process
						{
							tempVec.push_back(sortVec1[1]);
							sortVec1.erase(sortVec1.begin()+1);
						}
						else
						{
							tempVec.push_back(sortVec1[0]);
							sortVec1.erase(sortVec1.begin());
						}
						sortPriority(tempVec);
						sortVector = true;
					}
				}
			}
			else if(!tempVec.empty())     //If sortVec is empty but tempVec is not
				sortVector = false;
			else     //If both is empty then break
				break;
		}
		cout << "\nFirst Come First Served-based pre-emptive Priority" << endl;
		calculateTurnAroundTime(ganttChart, original, turnAroundTime1);
		calculateWaitingTime(original, turnAroundTime1, waitingTime1);
		displayProcessDetail(turnAroundTime1, waitingTime1);
		displayGC(ganttChart);
		cout << "Average Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime1) << endl;
		cout << "Average Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime1) << endl;
	}
	if(method == 2 || method == 5)     //RR
	{
		counter = 0;
		firstEnter = true;
		ganttChart.clear();
		increaseTime = quantum;

		sortStartingBurstTime(sortVec2);

		for(int k=0; k<totalBurstTime; k=k+increaseTime)
		{
			//To make sure the starting time is the first arrival time
			if(firstEnter)
				k = sortVec2[0].getArrivalTime();
			if(!sortVec2.empty())
			{
				//Add process to tempVec if current time is greater than or equal the process arrival time
				while(k >= sortVec2[0].getArrivalTime())
				{
					readyQueue.push_back(sortVec2[0]);
					sortVec2.erase(sortVec2.begin());
					if(sortVec2.empty())
						break;
				}
			}
			//To make sure the readyqueue will not be circulate to behind if is first time run process
			if(!clear && !firstEnter)
			{
				readyQueue.push_back(readyQueue[0]);
				readyQueue.erase(readyQueue.begin());
			}
			if(firstEnter)
				firstEnter = false;
			//If process from readyqueue burst time is less than the quantum, continue finish the process. If false, continue till quantum time is reach
			if(readyQueue[0].getBurstTime() < quantum)
			{
				ganttChart.push_back(GanttChart(readyQueue[0], k, k+readyQueue[0].getBurstTime()));
				increaseTime = readyQueue[0].getBurstTime();
				readyQueue[0].setBurstTime(0);
			}
			else
			{
				ganttChart.push_back(GanttChart(readyQueue[0], k, k+quantum));
				increaseTime = quantum;
				readyQueue[0].setBurstTime(readyQueue[0].getBurstTime()-quantum);
			}
			if(clear)
				clear = false;

			//If readyqueue is not empty and the first process burst time is 0, erase the first process
			if(!readyQueue.empty() && readyQueue[0].getBurstTime() == 0)
			{
				readyQueue.erase(readyQueue.begin());
				clear = true;
			}
		}
		cout << "\n\n\nRound Robin" << endl;
		calculateTurnAroundTime(ganttChart, original, turnAroundTime2);
		calculateWaitingTime(original, turnAroundTime2, waitingTime2);
		displayProcessDetail(turnAroundTime2, waitingTime2);
		displayGC(ganttChart);
		cout << "Average Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime2) << endl;
		cout << "Average Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime2) << endl;
	}
	if(method == 3 || method == 5)     //TLQ
	{
		counter = 0;
		firstEnter = true;
		ganttChart.clear();
		increaseTime = 1;

		sortStartingBurstTime(sortVec3);

		for(int k=0; k<totalBurstTime; k=k+increaseTime)
		{
			//To make sure the starting time is the first arrival time
			if(firstEnter)
				k = sortVec3[0].getArrivalTime();
			if(!sortVec3.empty())
			{
				//Add process to different queue if current time is greater than or equal the process arrival time. If priority is 1-2, pushback to tempVec, 3-4 pushback to queue2, 5-6 pushback to queue3
				while(k >= sortVec3[0].getArrivalTime())
				{
					if(sortVec3[0].getPriority() == 1 || sortVec3[0].getPriority() == 2)
						queue1.push_back(sortVec3[0]);
					else if(sortVec3[0].getPriority() == 3 || sortVec3[0].getPriority() == 4)
						queue2.push_back(sortVec3[0]);
					else if(sortVec3[0].getPriority() == 5 || sortVec3[0].getPriority() == 6)
						queue3.push_back(sortVec3[0]);
					sortVec3.erase(sortVec3.begin());
					if(sortVec3.empty())
						break;
				}
			}

			if(!queue1.empty())
			{
				//To make sure the queue1 will not be circulate to behind if is first time run process
				if(!clear && !firstEnter)
				{
					queue1.push_back(queue1[0]);
					queue1.erase(queue1.begin());
				}

				//If process from queue1 burst time is less than the quantum, continue finish the process. If false, continue till quantum time is reach
				if(queue1[0].getBurstTime() < quantum)
				{
					ganttChart.push_back(GanttChart(queue1[0], k, k+queue1[0].getBurstTime()));
					increaseTime = queue1[0].getBurstTime();
					queue1[0].setBurstTime(0);
				}
				else
				{
					ganttChart.push_back(GanttChart(queue1[0], k, k+quantum));
					increaseTime = quantum;
					queue1[0].setBurstTime(queue1[0].getBurstTime()-quantum);
				}

				if(clear)
					clear = false;

				//If queue1 is not empty and the first process burst time is 0, erase the first process
				if(!queue1.empty() && queue1[0].getBurstTime() == 0)
				{
					queue1.erase(queue1.begin());
					clear = true;
				}
			}
			else if(!queue2.empty())
			{
				//If sortVec3 is empty, check more condition. If else, straight continue the first process in queue2 till the burst time finish
				if(!sortVec3.empty())
				{
					//If current time + the first process burst time in queue2 is greater than sortVec3 first process arrival time, continue process till the sortVec3 first process arrival time. If false, continue till the queue2 first process burst time finish
					if(k+queue2[0].getBurstTime() > sortVec3[0].getArrivalTime())
					{
						ganttChart.push_back(GanttChart(queue2[0], k, sortVec3[0].getArrivalTime()));
						increaseTime = sortVec3[0].getArrivalTime()-k;
						queue2[0].setBurstTime(queue2[0].getBurstTime()-increaseTime);//sortVec3[0].getArrivalTime());
					}
					else if(k+queue2[0].getBurstTime() <= sortVec3[0].getArrivalTime())
					{
						ganttChart.push_back(GanttChart(queue2[0], k, k+queue2[0].getBurstTime()));
						increaseTime = queue2[0].getBurstTime();
						queue2[0].setBurstTime(0);
					}
				}
				else
				{
					ganttChart.push_back(GanttChart(queue2[0], k, k+queue2[0].getBurstTime()));
					increaseTime = queue2[0].getBurstTime();
					queue2[0].setBurstTime(0);
				}

				//If the queue2 is not empty and the first process of queue2 burst time is 0, erase the first process
				if(!queue2.empty() && queue2[0].getBurstTime() == 0)
					queue2.erase(queue2.begin());
			}
			else if(!queue3.empty()) //If the queue2 and queue1 is empty and queue3 is not empty, move the queue3 first process to queue2 and rollback time by 1
			{
				queue2.push_back(queue3[0]);
				queue3.erase(queue3.begin());
				increaseTime = 1;
				k--;
			}
			if(firstEnter)
				firstEnter = false;
		}
		cout << "\n\n\nThree-level Queue" << endl;
		calculateTurnAroundTime(ganttChart, original, turnAroundTime3);
		calculateWaitingTime(original, turnAroundTime3, waitingTime3);
		displayProcessDetail(turnAroundTime3, waitingTime3);
		displayGC(ganttChart);
		cout << "Average Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime3) << endl;
		cout << "Average Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime3) << endl;
	}
	if(method == 4 || method == 5)     //STRN
	{
		counter = 0;
		firstEnter = true;
		ganttChart.clear();
		increaseTime = 1;

		sortStartingBurstTime(sortVec4);

		for(int k=0; k<totalBurstTime; k=k+increaseTime)
		{
			//To make sure the starting time is the first arrival time
			if(firstEnter)
			{
				k = sortVec4[0].getArrivalTime();
				firstEnter = false;
			}
			
			if(!sortVec4.empty())
			{
				//Want to make sure multiple processes that have the same arrival time will be sorted with burst time
				counter = 0;
				for(int i=0; i<sortVec4.size(); i++)
					if(k >= sortVec4[i].getArrivalTime())
						counter++;

				for(int i=0; i<counter; i++)
					tempVec.push_back(sortVec4[i]);

				sortBurstTimeWithArrival(tempVec);

				for(int i=0; i<counter; i++)
					sortVec4.erase(sortVec4.begin());
			}

			if(!readyQueue.empty())
			{
				if(sortVec4.empty()) //If readyqueue is not empty and sortVec4 is empty, straight pushback readyqueue till the burst time finish. If false, will check more condition
				{
					ganttChart.push_back(GanttChart(readyQueue[0], k, k+readyQueue[0].getBurstTime()));
					increaseTime = readyQueue[0].getBurstTime();
					readyQueue[0].setBurstTime(0);
				}
				else //If false, check is the tempVec empty. If is not empty, check readyqueue first process burst time is greater than tempVec first process burst time. If true, swap readyqueue first process with tempVec first process
				{
					if(!tempVec.empty())
					{
						if(readyQueue[0].getBurstTime() > tempVec[0].getBurstTime())
						{
							readyQueue.push_back(tempVec[0]);
							tempVec.push_back(readyQueue[0]);
							readyQueue.erase(readyQueue.begin());
							tempVec.erase(tempVec.begin());
							sortBurstTimeWithArrival(tempVec);
						}
						ganttChart.push_back(GanttChart(readyQueue[0], k, k+1));
						increaseTime = 1;
						readyQueue[0].setBurstTime(readyQueue[0].getBurstTime()-1);
					}
					else //pushback the readyqueue first process till the sortVec4 first process arrival time
					{
						ganttChart.push_back(GanttChart(readyQueue[0], k, sortVec4[0].getArrivalTime()));
						increaseTime = sortVec4[0].getArrivalTime()-k;
						readyQueue[0].setBurstTime(readyQueue[0].getBurstTime()-increaseTime);
					}
				}

				//If readyqueue is not empty and readyqueue first process burst time is 0, erase the process
				if(!readyQueue.empty() && readyQueue[0].getBurstTime() == 0)
					readyQueue.erase(readyQueue.begin());
			}
			else if(!tempVec.empty()) //If tempVec is not empty, pushback tempVec first process to readyqueue and rollback time by 1
			{
				readyQueue.push_back(tempVec[0]);
				tempVec.erase(tempVec.begin());
				increaseTime = 1;
				k--;
			}
		}
		cout << "\n\n\nShortest Remaining Time Next" << endl;
		calculateTurnAroundTime(ganttChart, original, turnAroundTime4);
		calculateWaitingTime(original, turnAroundTime4, waitingTime4);
		displayProcessDetail(turnAroundTime4, waitingTime4);
		displayGC(ganttChart);
		cout << "Average Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime4) << endl;
		cout << "Average Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime4) << endl;
	}
	if(method == 5) //To show each turnaround time and waiting time of those methods
	{
		cout << "\n\n\nComparision: " << endl;
		cout << "First Come First Served-based pre-emptive Priority" << endl;
		cout << "\tAverage Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime1) << endl;
		cout << "\tAverage Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime1) << endl << endl;
		cout << "Round Robin" << endl;
		cout << "\tAverage Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime2) << endl;
		cout << "\tAverage Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime2) << endl << endl;
		cout << "Three-level Queue" << endl;
		cout << "\tAverage Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime3) << endl;
		cout << "\tAverage Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime3) << endl << endl;
		cout << "Shortest Remaining Time Next" << endl;
		cout << "\tAverage Turnaround Time: " << fixed << setprecision(2) << calculateAverageTurnaroundTime(turnAroundTime4) << endl;
		cout << "\tAverage Waiting Time: " << fixed << setprecision(2) << calculateAverageWaitingTime(waitingTime4) << endl << endl;

		//To show the lowest turnaround time and waiting time
		avgTurnAroundTime.push_back(calculateAverageTurnaroundTime(turnAroundTime1));
		avgTurnAroundTime.push_back(calculateAverageTurnaroundTime(turnAroundTime2));
		avgTurnAroundTime.push_back(calculateAverageTurnaroundTime(turnAroundTime3));
		avgTurnAroundTime.push_back(calculateAverageTurnaroundTime(turnAroundTime4));

		for(int i=0; i<4; i++)
			schedulingNumber.push_back(i+1);

		for(int i=0; i<4; i++)
			for(int j=i+1; j<4; j++)
				if(avgTurnAroundTime[i] > avgTurnAroundTime[j])
				{
					double temp = avgTurnAroundTime[i];
					avgTurnAroundTime[i] = avgTurnAroundTime[j];
					avgTurnAroundTime[j] = temp;
					int temps = schedulingNumber[i];
					schedulingNumber[i] = schedulingNumber[j];
					schedulingNumber[j] = temp;
				}

		if(schedulingNumber[0] == 1)
			cout << "First Come First Served-based pre-emptive Priority has the lowest turnaround time and waiting time." << endl;
		else if(schedulingNumber[0] == 2)
			cout << "Round Robin has the lowest turnaround time and waiting time." << endl;
		else if(schedulingNumber[0] == 3)
			cout << "Three-level Queue has the lowest turnaround time and waiting time." << endl;
		else if(schedulingNumber[0] == 4)
			cout << "Shortest Remaining Time Next has the lowest turnaround time and waiting time." << endl;
	}
	cout << endl;
	system("pause");
}