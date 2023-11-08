// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WinProcesses/UI/UI.h"
#include "GameController.generated.h"

/**
 * 
 */
UCLASS()
class WINPROCESSES_API AGameController : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUI> UIClass;

	UPROPERTY()
	UUI* UIWidget;
};
