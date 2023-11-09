// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessWidget.h"

#include "ObjectTools.h"

void UProcessWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BActivate->OnClicked.AddDynamic(this, &UProcessWidget::SetActive);
}

void UProcessWidget::SetActive()
{
	SetWidgetActive.Execute((int)Info);
	BActivate->SetBackgroundColor(FLinearColor::Gray);
}

void UProcessWidget::SetupProcess(int Index, FString Name)
{
	Creator = NewObject<UProcessCreator>(this);
	Creator->CreateNewProcess(Index, Info);
	
	TId->SetText(FText::FromString(FString::FromInt((int)Info)));
	
	TName->SetText(FText::FromString(Name));

	Status = "R";
	TStatus->SetText(FText::FromString(Status));
	
	TPriority->SetText(FText::FromString(GetPriority()));

	TTime->SetText(FText::FromString(FString::FromInt(Creator->GetTime())));
}

int UProcessWidget::GetId()
{
	return (int)Info;
}

UProcessCreator* UProcessWidget::GetProcessCreator()
{
	return Creator;
}

void UProcessWidget::UpdateInfo()
{
	
	if(waitpid(Info, NULL, WNOHANG) != 0)
	{
		DeleteProcessWidget.Execute((int)Info);
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
	return FString::FromInt(Creator->GetPriority());
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
	// cpu_set_t mask;
	// int AffinityMask = Creator->GetAffinity(mask);
	//
	// if(AffinityWidget)
	// {
	// 	if(!AffinityWidget->IsInViewport())
	// 	{
	// 		AffinityWidget->AddToViewport();
	// 		AffinityWidget->SetupAffinity(AffinityMask);
	// 	}
	// 	return;
	// }
	//
	// if(AffinityClass)
	// {
	// 	AffinityWidget = CreateWidget<UAffinityWidget>(GetWorld()->GetFirstPlayerController(), AffinityClass);
	//
	// 	if(AffinityWidget)
	// 	{
	// 		AffinityWidget->SetAffinity.BindDynamic(this, &UProcessWidget::SetAffinity);
	// 		AffinityWidget->AddToViewport();
	// 		AffinityWidget->SetupAffinity(AffinityMask);
	// 	}
	// }
}

// void UProcessWidget::SetAffinity(unsigned int AffinityIn)
// {
// 	Creator->SetAffinity(AffinityIn);
// 	AffinityWidget->RemoveFromViewport();
// }
