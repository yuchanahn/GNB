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
	// �� �Լ��� ���� ���ؼ���,
	// Build ���Ͽ� "UMG" ����� �߰��ϰ�, "Slate", "SlateCore" �ּ��� �����ؾ��Ѵ�.
	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
