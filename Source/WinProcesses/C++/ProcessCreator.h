// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <chrono>
#include "ProcessCreator.generated.h"

/**
 * 
 */
UCLASS()
class WINPROCESSES_API UProcessCreator : public UObject
{
	GENERATED_BODY()
	
public:
	bool CreateNewProcess(int index, PROCESS_INFORMATION& info);
	int Suspend();
	int Resume();
	bool SetAffinity(unsigned int AffinityIn);
	bool SetPriority(int PriorityIn);
	void CloseProcess();
	int GetTime();
	
	PROCESS_INFORMATION pi;
	DWORD Priority;
	std::chrono::high_resolution_clock::time_point StartPoint;
};
