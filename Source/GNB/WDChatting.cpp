// Fill out your copyright notice in the Description page of Project Settings.


#include "WDChatting.h"
#include "Widgets/SWidget.h"
#include "GNBGameModeBase.h"

#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "GNBPlayerController.h"


void UWDChatting::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	AGNBGameModeBase* GM = Cast<AGNBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	AGNBPlayerController* PC = Cast<AGNBPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (GM == nullptr) return;
	if (PC == nullptr) return;

	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		if (!Text.IsEmpty()) {
			GM->SendChatting(Text.ToString());
			SetChatInputTextMessage(FText::GetEmpty());
			PC->FocusGame();
		}
		break;
	case ETextCommit::OnUserMovedFocus:
		break;
	case ETextCommit::OnCleared:
		break;
	}
}

void UWDChatting::SetChatInputTextMessage(const FText& Text)
{
	ChatInputText->SetText(Text);
}

void UWDChatting::NativeConstruct()
{
	Super::NativeConstruct();
	AGNBGameModeBase* GM = Cast<AGNBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	AGNBPlayerController* PC = Cast<AGNBPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	if (GM == nullptr) return;
	if (PC == nullptr) return;

	PC->ChatWD = this;

	FScriptDelegate d;
	d.BindUFunction(this, TEXT("AddChatMessage"));
	GM->ChattingEvent.Add(d);
	ChatInputText->OnTextCommitted.AddDynamic(this, &UWDChatting::OnChatTextCommitted);
}

void UWDChatting::AddChatMessage(const FString& Message)
{
	// Text 오브젝트를 생성하고, ScrollBox에 추가한다.
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatHistoryArea);
	NewTextBlock->SetText(FText::FromString(Message));

	ChatHistoryArea->AddChild(NewTextBlock);
	ChatHistoryArea->ScrollToEnd();
}