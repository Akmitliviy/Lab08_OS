// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define _GNU_SOURCE

#include <cstdio>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <cstdlib>
#include <csignal>
#include <cmath>
#include <sched.h>
#include <sys/resource.h>
#include<sys/wait.h>
#include <iostream>
#include "ProcessCreator.generated.h"



/**
 * 
 */
UCLASS()
class WINPROCESSES_API UProcessCreator : public UObject
{
	GENERATED_BODY()
	
public:
	bool CreateNewProcess(int index, pid_t& info);
	int Suspend();
	int Resume();
	//bool SetAffinity(unsigned int AffinityIn);
	bool SetPriority(int PriorityIn);
	void CloseProcess();
	int GetTime();
	//unsigned int GetAffinity(cpu_set_t& mask);
	int GetPriority();
	
	int Priority;
	pid_t pi;
	std::chrono::high_resolution_clock::time_point StartPoint;
};
