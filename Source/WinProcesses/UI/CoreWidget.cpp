// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreWidget.h"

void UCoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UCoreWidget::IsChecked()
{
	return CCheck->IsChecked();
}

void UCoreWidget::SetChecked()
{
	CCheck->SetIsChecked(true);
}

void UCoreWidget::SetName(FString Name)
{
	TCore->SetText(FText::FromString(Name));
}
