// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "DVMMOBPFuncLib.generated.h" // always include this last


class FUDPServer : public FRunnable {
public:
	FUDPServer(int32 Port);

	virtual uint32 Run() override;
	virtual ~FUDPServer();

private:
	FSocket* ListenSocket;
	FRunnableThread* Thread;
};

USTRUCT(BlueprintType)
struct FGameMessageStruct {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 MessageID;

	UPROPERTY(BlueprintReadWrite)
	int32 MessageType; // TODO: Define enum for this 1 input, 2 position, 3 chat message, etc

	UPROPERTY(BlueprintReadWrite)
	FString MessageBody; // JSON?
};

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

	UFUNCTION(BlueprintCallable, Category = "Networking")
	static bool SendGameMessageToServer(int32 Port, FGameMessageStruct Message);
};