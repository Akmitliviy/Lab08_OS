// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "thread"
#include "AffinityWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSetAffinity, unsigned int, AffinityMask);

/**
 * 
 */
UCLASS()
class WINPROCESSES_API UAffinityWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UScrollBox* SCores;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BExit;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BConfirm;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UCoreWidget> CoreClass;

	UPROPERTY()
	TArray<UCoreWidget*> Cores;
	
	int NumberOfCores;

	FSetAffinity SetAffinity;
	
	UFUNCTION()
	void Confirm();
	
	UFUNCTION()
	void Exit();

	UFUNCTION()
	void SetupAffinity(unsigned int AffinityMask);
};
