// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessWidget.h"

void UProcessWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BActivate->OnClicked.AddDynamic(this, &UProcessWidget::SetActive);
}

void UProcessWidget::SetActive()
{
	SetWidgetActive.Execute(Info.dwProcessId);
	BActivate->SetBackgroundColor(FLinearColor::Gray);
}

void UProcessWidget::SetupProcess(int Index, FString Name)
{
	Creator = NewObject<UProcessCreator>(this);
	Creator->CreateNewProcess(Index, Info);
	
	TId->SetText(FText::FromString(FString::FromInt(Info.dwProcessId)));
	
	TName->SetText(FText::FromString(Name));

	Status = "R";
	TStatus->SetText(FText::FromString(Status));
	
	TPriority->SetText(FText::FromString(GetPriority()));

	TTime->SetText(FText::FromString(FString::FromInt(Creator->GetTime())));
}

int UProcessWidget::GetId()
{
	return Info.dwProcessId;
}

UProcessCreator* UProcessWidget::GetProcessCreator()
{
	return Creator;
}

void UProcessWidget::UpdateInfo()
{
	if(WaitForSingleObject(Info.hProcess, 0) == 0)
	{
		Creator->CloseProcess();
		DeleteObject(Creator);

		DeleteProcessWidget.Execute(Info.dwProcessId);
	}
	
	TStatus->SetText(FText::FromString(Status));
	
	TPriority->SetText(FText::FromString(GetPriority()));
	
	TTime->SetText(FText::FromString(FString::FromInt(Creator->GetTime())));
}

void UProcessWidget::SetStatus(FString NewStatus)
{
	Status = NewStatus;
}

FString UProcessWidget::GetStatus()
{
	return Status;
}

void UProcessWidget::ResetColor()
{
	BActivate->SetBackgroundColor(FLinearColor::White);
}

FString UProcessWidget::GetPriority()
{
	switch(GetPriorityClass(Info.hProcess))
	{
	case REALTIME_PRIORITY_CLASS:
		return "Realtime";
		
	case HIGH_PRIORITY_CLASS:
		return "High";
		
	case ABOVE_NORMAL_PRIORITY_CLASS:
		return "Above Normal";
		
	case NORMAL_PRIORITY_CLASS:
		return "Normal";
		
	case BELOW_NORMAL_PRIORITY_CLASS:
		return "Below Normal";
		
	case IDLE_PRIORITY_CLASS:
		return "Low";
		
	default:
		return "Unknown";
	}
}

void UProcessWidget::CreatePriorityWidget()
{
	if(PriorityWidget)
	{
		if(!PriorityWidget->IsInViewport())
		{
			PriorityWidget->AddToViewport();
		}
		return;
	}
	
	if(PriorityClass)
	{
		PriorityWidget = CreateWidget<UPriorityWidget>(GetWorld()->GetFirstPlayerController(), PriorityClass);

		if(PriorityWidget)
		{
			PriorityWidget->SetPriority.BindDynamic(this, &UProcessWidget::SetPriority);
			PriorityWidget->AddToViewport();
		}
	}
}

void UProcessWidget::SetPriority(int PriorityIn)
{
	Creator->SetPriority(PriorityIn);
	PriorityWidget->RemoveFromViewport();
}

void UProcessWidget::CreateAffinityWidget()
{
	unsigned long long AffinityMask(0);
	unsigned long long SystemMask(0);
	GetProcessAffinityMask(Info.hProcess, &AffinityMask, &SystemMask);

	if(AffinityWidget)
	{
		if(!AffinityWidget->IsInViewport())
		{
			AffinityWidget->AddToViewport();
			AffinityWidget->SetupAffinity(AffinityMask);
		}
		return;
	}
	
	if(AffinityClass)
	{
		AffinityWidget = CreateWidget<UAffinityWidget>(GetWorld()->GetFirstPlayerController(), AffinityClass);

		if(AffinityWidget)
		{
			AffinityWidget->SetAffinity.BindDynamic(this, &UProcessWidget::SetAffinity);
			AffinityWidget->AddToViewport();
			AffinityWidget->SetupAffinity(AffinityMask);
		}
	}
}

void UProcessWidget::SetAffinity(unsigned int AffinityIn)
{
	Creator->SetAffinity(AffinityIn);
	AffinityWidget->RemoveFromViewport();
}
