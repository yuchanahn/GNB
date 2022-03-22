// Fill out your copyright notice in the Description page of Project Settings.


#include "WDChatting.h"
#include "Widgets/SWidget.h"
#include "GNBGameModeBase.h"

#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"


void UWDChatting::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	AGNBGameModeBase* GM = Cast<AGNBGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (GM == nullptr) return;

	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		if (Text.IsEmpty() == false)
		{
			GM->SendChatting(Text.ToString()); // 메시지 보냄.
			SetChatInputTextMessage(FText::GetEmpty()); // 메세지 전송했으니, 비워줌.
		}
		PC->SetInputMode(FInputModeGameOnly());
		break;
	case ETextCommit::OnCleared:
		PC->SetInputMode(FInputModeGameOnly());
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
	APlayerController* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (GM == nullptr) return;
	FScriptDelegate d;
	d.BindUFunction(this, TEXT("AddChatMessage"));
	GM->ChattingEvent.Add(d);
	ChatInputText->OnTextCommitted.AddDynamic(this, &UWDChatting::OnChatTextCommitted);
	PC->InputComponent->BindAction(TEXT("ChatStartEnd"), IE_Pressed, ChatInputText, &UWidget::SetFocus);
}

void UWDChatting::AddChatMessage(const FString& Message)
{
	// Text 오브젝트를 생성하고, ScrollBox에 추가한다.
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatHistoryArea);
	NewTextBlock->SetText(FText::FromString(Message));

	ChatHistoryArea->AddChild(NewTextBlock);
	ChatHistoryArea->ScrollToEnd(); // 가장 최근 채팅을 보기 위해, 스크롤을 가장 아래로 내린다.
}