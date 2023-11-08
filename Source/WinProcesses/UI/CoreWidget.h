// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "CoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class WINPROCESSES_API UCoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UCheckBox* CCheck;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TCore;

public:
	UFUNCTION()
	bool IsChecked();
	
	UFUNCTION()
	void SetChecked();

	UFUNCTION()
	void SetName(FString Name);
};
