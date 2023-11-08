// Fill out your copyright notice in the Description page of Project Settings.


#include "PriorityWidget.h"

void UPriorityWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BRealtime->OnClicked.AddDynamic(this, &UPriorityWidget::SetRealtime);
	BHigh->OnClicked.AddDynamic(this, &UPriorityWidget::SetHigh);
	BAboveNormal->OnClicked.AddDynamic(this, &UPriorityWidget::SetAboveNormal);
	BNormal->OnClicked.AddDynamic(this, &UPriorityWidget::SetNormal);
	BBelowNormal->OnClicked.AddDynamic(this, &UPriorityWidget::SetBelowNormal);
	BLow->OnClicked.AddDynamic(this, &UPriorityWidget::SetLow);
	BExit->OnClicked.AddDynamic(this, &UPriorityWidget::Exit);
}

void UPriorityWidget::SetRealtime()
{
	SetPriority.Execute(-20);
	Exit();
}

void UPriorityWidget::SetHigh()
{
	SetPriority.Execute(-15);
	Exit();
}

void UPriorityWidget::SetAboveNormal()
{
	SetPriority.Execute(-5);
	Exit();
}

void UPriorityWidget::SetNormal()
{
	SetPriority.Execute(0);
	Exit();
}

void UPriorityWidget::SetBelowNormal()
{
	SetPriority.Execute(5);
	Exit();
}

void UPriorityWidget::SetLow()
{
	SetPriority.Execute(19);
	Exit();
}

void UPriorityWidget::Exit()
{
	BRealtime->OnClicked.Clear();
	BHigh->OnClicked.Clear();
	BAboveNormal->OnClicked.Clear();
	BNormal->OnClicked.Clear();
	BBelowNormal->OnClicked.Clear();
	BLow->OnClicked.Clear();
	BExit->OnClicked.Clear();
	
	this->RemoveFromViewport();
}
