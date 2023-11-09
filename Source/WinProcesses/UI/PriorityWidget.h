// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PriorityWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSetPriority, int, Priority);

/**
 * 
 */
UCLASS()
class WINPROCESSES_API UPriorityWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BRealtime;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BHigh;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BAboveNormal;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BNormal;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BBelowNormal;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BLow;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BExit;
	

	UFUNCTION()
	void SetRealtime();

	UFUNCTION()
	void SetHigh();

	UFUNCTION()
	void SetAboveNormal();

	UFUNCTION()
	void SetNormal();

	UFUNCTION()
	void SetBelowNormal();

	UFUNCTION()
	void SetLow();

	UFUNCTION()
	void Exit();

public:
	FSetPriority SetPriority;
};
