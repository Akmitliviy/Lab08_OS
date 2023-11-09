// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AffinityWidget.h"
#include "PriorityWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WinProcesses/C++/ProcessCreator.h"
#include "ProcessWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeleteProcessWidget, int, ProcessNumber);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSetWidgetActive, int, ProcessNumber);

/**
 * 
 */
UCLASS()
class WINPROCESSES_API UProcessWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TId;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TName;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TPriority;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TTime;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TStatus;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BActivate;


	UPROPERTY()
	UProcessCreator* Creator;
	
	pid_t Info;

	FString Status;

	FString Priority;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UPriorityWidget> PriorityClass;

	UPROPERTY()
	UPriorityWidget* PriorityWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UAffinityWidget> AffinityClass;
	
	UPROPERTY()
	UAffinityWidget* AffinityWidget;
	
	FDeleteProcessWidget DeleteProcessWidget;

	FSetWidgetActive SetWidgetActive;
	
	UFUNCTION()
	void SetActive();

	UFUNCTION()
	void SetupProcess(int Index, FString Name);

	UFUNCTION()
	int GetId();

	UFUNCTION()
	UProcessCreator* GetProcessCreator();

	UFUNCTION()
	void UpdateInfo();

	UFUNCTION()
	void SetStatus(FString NewStatus);

	UFUNCTION()
	FString GetStatus();

	UFUNCTION()
	void ResetColor();

	UFUNCTION()
	FString GetPriority();

	UFUNCTION()
	void CreatePriorityWidget();

	UFUNCTION()
	void SetPriority(int PriorityIn);

	UFUNCTION()
	void CreateAffinityWidget();

	// UFUNCTION()
	// void SetAffinity(unsigned int AffinityIn);

};
