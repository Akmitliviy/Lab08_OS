// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"

void AGameController::BeginPlay()
{
	Super::BeginPlay();

	if(UIClass)
	{
		UIWidget = CreateWidget<UUI>(this, UIClass);
		if(UIWidget)
		{
			UIWidget->AddToViewport();
		}
	}
	
	
}
