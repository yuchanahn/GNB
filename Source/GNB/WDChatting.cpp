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
			GM->SendChatting(Text.ToString()); // �޽��� ����.
			SetChatInputTextMessage(FText::GetEmpty()); // �޼��� ����������, �����.
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
	// Text ������Ʈ�� �����ϰ�, ScrollBox�� �߰��Ѵ�.
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(ChatHistoryArea);
	NewTextBlock->SetText(FText::FromString(Message));

	ChatHistoryArea->AddChild(NewTextBlock);
	ChatHistoryArea->ScrollToEnd(); // ���� �ֱ� ä���� ���� ����, ��ũ���� ���� �Ʒ��� ������.
}