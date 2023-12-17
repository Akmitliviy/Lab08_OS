// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcessWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/ScrollBox.h"
#include "ctime"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "UI.generated.h"

class APlayerController;
/**
 * 
 */
UCLASS()
class WINPROCESSES_API UUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BCreateProcess;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BSuspend;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BResume;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BSetAffinity;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BSetPriority;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UScrollBox* SProcessesList;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UButton* BDenyAccess;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UTextBlock* TDenyAccess;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	UComboBoxString* DSelector;

	UPROPERTY()
	TMap<int, UProcessWidget*> Processes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UProcessWidget> ProcessWidgetClass;

	int ActiveProcess;
	
	FTimerHandle Handle;
	
	const char* LOG_PATH;

	int LogFile;
	
	bool bDenyAccess = true;

	UFUNCTION()
	void SetActiveWidget(int ProcessNumberIn);
	
	UFUNCTION()
	void Create();

	UFUNCTION()
	void Suspend();

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void SetAffinity();

	UFUNCTION()
	void SetPriority();

	UFUNCTION()
	void DeleteProcess(int ProcessNumberIn);

	UFUNCTION()
	void UpdateInfo();

	UFUNCTION()
	void DenyAccess();

	bool OpenLogFile();

	bool WriteLogFile(std::string Message);

    std::string GetDateTime();
};
