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
	SetPriority.Execute(REALTIME_PRIORITY_CLASS);
	Exit();
}

void UPriorityWidget::SetHigh()
{
	SetPriority.Execute(HIGH_PRIORITY_CLASS);
	Exit();
}

void UPriorityWidget::SetAboveNormal()
{
	SetPriority.Execute(ABOVE_NORMAL_PRIORITY_CLASS);
	Exit();
}

void UPriorityWidget::SetNormal()
{
	SetPriority.Execute(NORMAL_PRIORITY_CLASS);
	Exit();
}

void UPriorityWidget::SetBelowNormal()
{
	SetPriority.Execute(BELOW_NORMAL_PRIORITY_CLASS);
	Exit();
}

void UPriorityWidget::SetLow()
{
	SetPriority.Execute(IDLE_PRIORITY_CLASS);
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
