// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GNBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GNB_API AGNBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	class UWDChatting* ChatWD;

	UFUNCTION()
	void FocusChatInputText();
	UFUNCTION()
	void FocusGame();
};
