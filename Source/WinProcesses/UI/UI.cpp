// Fill out your copyright notice in the Description page of Project Settings.


#include "UI.h"

#include "Materials/MaterialExpressionChannelMaskParameter.h"

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

	ActiveProcess = 0;
	
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
		LocalProcess->SetWidgetActive.BindDynamic(this, &UUI::UUI::SetActiveWidget);
		
		SProcessesList->AddChild(LocalProcess);
		Processes.Add(LocalProcess->GetId(), LocalProcess);
	}
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
