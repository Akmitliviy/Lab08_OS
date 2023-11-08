// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessCreator.h"

bool UProcessCreator::CreateNewProcess(int index, pid_t& Pid)
{
    pid_t ProcessId = fork();

    if(ProcessId < 0) {
        return false;
    }
    else if(ProcessId == 0) {

        char name[200];
        switch (index) {
            case 0:
                sprintf(name, "/home/akmitliviy/CLionProjects/tabulation/cmake-build-debug/tabulation");

                if (execl(name, name, std::to_string(0).c_str(), std::to_string(10000000).c_str(), std::to_string(2).c_str(), NULL) == -1) {
                    exit(EXIT_FAILURE);
                }
                break;
            case 1:
                sprintf(name, "/usr/bin/qterminal");

                if (execl(name, name, NULL) == -1) {
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                exit(EXIT_FAILURE);
        }

    }
    StartPoint = std::chrono::high_resolution_clock::now();
    signal(SIGCHLD, WaitForProcess);

    Pid = ProcessId;
    return true;
}

int UProcessCreator::Suspend()
{
    return kill(pi, SIGSTOP);
}

int UProcessCreator::Resume()
{
    return kill(pi, SIGCONT);
}

unsigned int UProcessCreator::GetAffinity(cpu_set_t& mask)
{
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    unsigned int dMask(0);

    sched_getaffinity(pi, sizeof(mask), &mask);
    for(int i = 0; i < numCPU; i++){
        if(CPU_ISSET(i, &mask) != 0){
            dMask += pow(2, i);
        }
    }
    return dMask;
}

bool UProcessCreator::SetAffinity(unsigned int AffinityIn)
{
    int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t mask;
    CPU_ZERO(&mask);

    for (int i = 0; i < numCPU; i++) {
        if (AffinityIn & static_cast<unsigned int>(pow(2, i))) {
            CPU_SET(i, &mask);
        }
    }

    return sched_setaffinity(pi, sizeof(mask), &mask);
}

int UProcessCreator::GetPriority()
{
    Priority = getpriority(PRIO_PROCESS, pi);
    return Priority;
}

bool UProcessCreator::SetPriority(int PriorityIn)
{
    Priority = PriorityIn;
    return setpriority(PRIO_PROCESS, pi, PriorityIn);
}

void UProcessCreator::CloseProcess()
{
    kill(pi, SIGKILL);
}

int UProcessCreator::GetTime()
{
    std::chrono::high_resolution_clock::time_point EndPoint = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds EvaluatedTime = std::chrono::duration_cast<std::chrono::microseconds>(EndPoint - StartPoint);
    return static_cast<int>(EvaluatedTime.count()) * pow(10.0, -6);
}

void UProcessCreator::WaitForProcess(int signum){
    wait(NULL);
}
