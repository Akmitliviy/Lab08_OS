// Fill out your copyright notice in the Description page of Project Settings.


#include "UI.h"

#include <string>


void UUI::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly());
	}

	BCreateProcess->OnClicked.AddDynamic(this, &UUI::Create);
	BSuspend->OnClicked.AddDynamic(this, &UUI::Suspend);
	BResume->OnClicked.AddDynamic(this, &UUI::Resume);
	//BSetAffinity->OnClicked.AddDynamic(this, &UUI::SetAffinity);
	BSetPriority->OnClicked.AddDynamic(this, &UUI::SetPriority);
	BDenyAccess->OnClicked.AddDynamic(this, &UUI::DenyAccess);

	ActiveProcess = 0;
	LOG_PATH = "/Users/Shared/Log.txt";
	
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &UUI::UpdateInfo, 1.f, true);
}

void UUI::SetActiveWidget(int ProcessNumberIn)
{
	if(ActiveProcess)
	{
		UProcessWidget* LocalProc = *Processes.Find(ActiveProcess);
		if(LocalProc)
		{
			LocalProc->ResetColor();
		}
	}
	ActiveProcess = ProcessNumberIn;
}

void UUI::Create()
{
	UProcessWidget* LocalProcess = Cast<UProcessWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), ProcessWidgetClass));
	if(LocalProcess){
		LocalProcess->SetupProcess(DSelector->GetSelectedIndex(), DSelector->GetSelectedOption());
		LocalProcess->DeleteProcessWidget.BindDynamic(this, &UUI::DeleteProcess);
		LocalProcess->SetWidgetActive.BindDynamic(this, &UUI::SetActiveWidget);
		
		SProcessesList->AddChild(LocalProcess);
		Processes.Add(LocalProcess->GetId(), LocalProcess);
	}

	std::string LogMessage; 
	LogMessage += std::to_string(LocalProcess->GetId()) + "\t" + TCHAR_TO_UTF8(*DSelector->GetSelectedOption()) + "\n" + GetDateTime();

	WriteLogFile(LogMessage);
}

void UUI::Suspend()
{
	if(ActiveProcess)
	{
		UProcessWidget* LocalProc = *Processes.Find(ActiveProcess);
		if(LocalProc)
		{
			if(LocalProc->GetStatus() != "S")
			{
				LocalProc->GetProcessCreator()->Suspend();
				LocalProc->SetStatus("S");
			}
			
		}
	}
}

void UUI::Resume()
{
	if(ActiveProcess)
	{
		UProcessWidget* LocalProc = *Processes.Find(ActiveProcess);
		if(LocalProc)
		{
			if(LocalProc->GetStatus() != "R")
			{
				LocalProc->GetProcessCreator()->Resume();
				LocalProc->SetStatus("R");
			}
		}
	}
}

void UUI::SetAffinity()
{
	// if(ActiveProcess)
	// {
	// 	UProcessWidget* LocalProc = *Processes.Find(ActiveProcess);
	// 	if(LocalProc)
	// 	{
	// 		LocalProc->CreateAffinityWidget();
	// 	}
	// }
}

void UUI::SetPriority()
{
	if(ActiveProcess)
	{
		UProcessWidget* LocalProc = *Processes.Find(ActiveProcess);
		if(LocalProc)
		{
			LocalProc->CreatePriorityWidget();
		}
	}
}

void UUI::DeleteProcess(int ProcessNumberIn)
{
	(*Processes.Find(ProcessNumberIn))->RemoveFromViewport();
	Processes.Remove(ProcessNumberIn);

	if(ActiveProcess == ProcessNumberIn)
	{
		ActiveProcess = 0;
	}
	
}

void UUI::UpdateInfo()
{
	TArray<UProcessWidget*> ProcArray;
	Processes.GenerateValueArray(ProcArray);

	if(ProcArray.Num() != 0)
	{
		for(UProcessWidget* LocalProc : ProcArray)
		{
			LocalProc->UpdateInfo();
		}
	}
}

void UUI::DenyAccess()
{
	if (bDenyAccess) {
		if (chmod(LOG_PATH, 0000770) == -1) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to set access mask!"));
			return;
		}
		TDenyAccess->SetText(FText(FText::FromString("Allow Access")));
	} else {
		if (chmod(LOG_PATH, 0000777) == -1) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to set access mask!"));
			return;
		}
		
		TDenyAccess->SetText(FText(FText::FromString("Deny Access")));
	}
	bDenyAccess = !bDenyAccess;
}

bool UUI::OpenLogFile()
{
	LogFile = open(LOG_PATH, O_WRONLY | O_APPEND | O_CREAT, 0000777);
	if (LogFile == -1) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to open log file!"));
		return false;
	}
	return true;
}

bool UUI::WriteLogFile(std::string Message)
{
	if (OpenLogFile()) {
		auto bytesWritten = write(LogFile, Message.c_str(), strlen(Message.c_str()));
		if (bytesWritten == -1) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to write to log file!"));
			close(LogFile);
			return false;
		}
		close(LogFile);
		return true;
	}

	return false;
}

std::string UUI::GetDateTime()
{
	std::time_t currentTime = std::time(nullptr);
	return std::ctime(&currentTime);
}
