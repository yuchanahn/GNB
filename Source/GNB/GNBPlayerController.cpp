// Fill out your copyright notice in the Description page of Project Settings.


#include "GNBPlayerController.h"
#include "WDChatting.h"
#include "Components/EditableText.h"

void AGNBPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGNBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("ChatStartEnd"), EInputEvent::IE_Pressed, this, &AGNBPlayerController::FocusChatInputText);
}

void AGNBPlayerController::FocusChatInputText()
{
	if (!ChatWD->HasKeyboardFocus()) {
		FInputModeGameAndUI mode;
		mode.SetWidgetToFocus(ChatWD->ChatInputText->TakeWidget());
		mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(mode);
	} else {

	}
}

void AGNBPlayerController::FocusGame()
{
	FInputModeGameAndUI mode;
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(mode);
	//SetInputMode(FInputModeGameOnly());
}