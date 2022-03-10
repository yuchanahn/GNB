// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "yc_thread_safe_queue.hpp"

#include <functional>

#include "GNBGameModeBase.generated.h"



USTRUCT(Atomic, Blueprintable)
struct FChatMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString msg;
};

USTRUCT(Atomic, Blueprintable)
struct FGachaResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> r;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChattingEvent, FChatMessage, msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGachaEvent, FGachaResult, msg);
/**
 * 
 */
UCLASS()
class GNB_API AGNBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	class TCPClient* clnt;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	yc_net::thread_safe_queue<std::function<void()>> jobs;


	UPROPERTY(EditAnywhere, Category = "NET")
	FString serverIP;
	UPROPERTY(EditAnywhere, Category = "NET")
	int port;

	UPROPERTY(BlueprintAssignable, Category = "NET")
	FChattingEvent ChattingEvent;

	UPROPERTY(BlueprintAssignable, Category = "NET")
	FGachaEvent GachaEvent;

	UFUNCTION(BlueprintCallable, Category = "NET")
	void SendChatting(FString msg);

	UFUNCTION(BlueprintCallable, Category = "NET")
	void GachaStart(int32 cnt);
};
