// Copyright Epic Games, Inc. All Rights Reserved.


#include "GNBGameModeBase.h"
#include "TCPClient.h"
// test

void AGNBGameModeBase::BeginPlay()
{
	clnt = new TCPClient();
	clnt->Init(this);

	clnt->ConnectServer(TCHAR_TO_ANSI(*serverIP), port);
}

void AGNBGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	std::vector<std::function<void()>> worker;
	
	while (jobs.size() > 0) 
		worker.push_back(std::move(jobs.dequeue()));
	
	for (auto& f : worker) f();
}

void AGNBGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	delete clnt;
}

void AGNBGameModeBase::SendChatting(FString msg)
{
	clnt->SendChatting(*msg);
}

void AGNBGameModeBase::GachaStart(int32 cnt)
{
	clnt->GachaStart(static_cast<char>(cnt));
}