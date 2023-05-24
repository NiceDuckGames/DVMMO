// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "DVMMOBPFuncLib.generated.h" // always include this last

/**
 * 
 */
UCLASS()
class THIRDPERSONMP_API UDVMMOBPFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Networking")
	static bool StartUDPServer(int32 Port);
};

class UDPServer : public FRunnable {
public:
	UDPServer(int32 Port);

	virtual uint32 Run() override;

private:
	FSocket* ListenSocket;
	FRunnableThread* Thread;
};
