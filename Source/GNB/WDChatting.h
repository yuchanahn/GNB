// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WDChatting.generated.h"

/**
 * 
 */
UCLASS()
class GNB_API UWDChatting : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void AddChatMessage(const FString& Message);

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* ChatHistoryArea;

	UPROPERTY(Meta = (BindWidget))
	class UEditableText* ChatInputText;

	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void SetChatInputTextMessage(const FText& Text);
};
