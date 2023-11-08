// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessCreator.h"

bool UProcessCreator::CreateNewProcess(int index, PROCESS_INFORMATION& info)
{
	STARTUPINFO si;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	wchar_t tabulation[150];
	swprintf_s(tabulation, L"D:\\OS\\Lab03_OS\\FirstPart\\Tabulation\\x64\\Debug\\Tabulation.exe -100000 100000 2");
	wchar_t Steam[150];
	swprintf_s(Steam, L"C:\\Program Files (x86)\\Steam\\steam.exe");
	wchar_t Regedit[150];
	swprintf_s(Regedit, L"regedit");
	wchar_t Sort[150];
	swprintf_s(Sort, L"D:\\OS\\Lab03_OS\\Sort\\x64\\Debug\\Sort.exe");

	LPTSTR szCmdline;
	switch(index)
	{
	case 0:
		szCmdline = tabulation;
		break;
	case 1:
		szCmdline = Steam;
		break;
	case 2:
		szCmdline = Regedit;
		break;
	case 3:
		szCmdline = Sort;
		break;
	default:
		szCmdline = tabulation;
	}

	StartPoint = std::chrono::high_resolution_clock::now();
	if (!CreateProcess( nullptr, szCmdline, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi ))
	{
		return false;
	}

	Priority = REALTIME_PRIORITY_CLASS;
	SetPriorityClass(pi.hProcess, Priority);
	info = pi;
	return true;
}

int UProcessCreator::Suspend()
{
	return SuspendThread(pi.hThread);
}

int UProcessCreator::Resume()
{
	return ResumeThread(pi.hThread);
}

bool UProcessCreator::SetAffinity(unsigned int AffinityIn)
{
	return SetProcessAffinityMask(pi.hProcess, AffinityIn);
}

bool UProcessCreator::SetPriority(int PriorityIn)
{
	Priority = PriorityIn;
	return SetPriorityClass(pi.hProcess, Priority);
}

void UProcessCreator::CloseProcess()
{
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int UProcessCreator::GetTime(){
	std::chrono::high_resolution_clock::time_point EndPoint = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds EvaluatedTime = std::chrono::duration_cast<std::chrono::microseconds>(EndPoint - StartPoint);
	return static_cast<int>(EvaluatedTime.count()) * pow(10.0, -6);
}
