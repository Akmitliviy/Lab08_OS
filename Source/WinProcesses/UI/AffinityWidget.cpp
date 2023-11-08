// Fill out your copyright notice in the Description page of Project Settings.


#include "AffinityWidget.h"

void UAffinityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NumberOfCores = std::thread::hardware_concurrency();

	BConfirm->OnClicked.AddDynamic(this, &UAffinityWidget::Confirm);
	BExit->OnClicked.AddDynamic(this, &UAffinityWidget::Exit);
}

void UAffinityWidget::Confirm()
{
	unsigned long long AffinityMask(0);
	for(int i = 0; i < Cores.Num(); i++)
	{
		if(Cores[i]->IsChecked())
		{
			AffinityMask += pow(2, i);
		}
	}
	
	SetAffinity.Execute(AffinityMask);

	Exit();
}

void UAffinityWidget::Exit()
{
	SCores->ClearChildren();
	Cores.Empty();
	BConfirm->OnClicked.Clear();
	BExit->OnClicked.Clear();

	this->RemoveFromViewport();
}

void UAffinityWidget::SetupAffinity(unsigned int AffinityMask)
{
	if(CoreClass)
	{
		for(int i = 0; i < NumberOfCores; i++)
		{
		
			UCoreWidget* Core = CreateWidget<UCoreWidget>(GetWorld()->GetFirstPlayerController(), CoreClass);

			if(Core)
			{
				if(AffinityMask & static_cast<unsigned int>(pow(2, i)))
				{
					Core->SetChecked();
				}
				Core->SetName(FString::Printf(TEXT("Core %d"), i));
				Cores.Add(Core);
				SCores->AddChild(Core);
			}
		}
	}
	
}
