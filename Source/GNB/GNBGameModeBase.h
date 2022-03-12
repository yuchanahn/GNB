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



USTRUCT(Atomic, Blueprintable)
struct FAttack
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector pos;
};


USTRUCT(Atomic, Blueprintable)
struct FSpawnCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector pos;
};


USTRUCT(Atomic, Blueprintable)
struct FMouseInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector start_pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector pos;
};

USTRUCT(Atomic, Blueprintable)
struct FCharacterMovement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 number;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector start_pos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector pos;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChattingEvent, FChatMessage, msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGachaEvent, FGachaResult, msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackEvent, FAttack, AttackData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnCharacterEvent, FSpawnCharacter, CharacterData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterMovementEvent, FCharacterMovement, CharacterMovementData);
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

	UPROPERTY(BlueprintAssignable, Category = "NET")
	FSpawnCharacterEvent SpawnCharacterEvent;

	UPROPERTY(BlueprintAssignable, Category = "NET")
	FCharacterMovementEvent CharacterMovementEvent;

	UPROPERTY(BlueprintAssignable, Category = "NET")
	FAttackEvent AttackEvent;

	UFUNCTION(BlueprintCallable, Category = "NET")
	void SendChatting(FString msg);

	UFUNCTION(BlueprintCallable, Category = "NET")
	void GachaStart(int32 cnt);

	UFUNCTION(BlueprintCallable, Category = "NET")
	void SendMouseInput(FMouseInput data);
};
