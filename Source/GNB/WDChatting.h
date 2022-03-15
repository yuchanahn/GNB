// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "WDChatting.generated.h"

/**
 * 
 */
UCLASS()
class GNB_API UWDChatting : public UWidgetBlueprint
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* ChatHistoryArea;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* ChatInputText;
	// 이 함수를 쓰기 위해서는,
	// Build 파일에 "UMG" 모듈을 추가하고, "Slate", "SlateCore" 주석을 해제해야한다.
	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
