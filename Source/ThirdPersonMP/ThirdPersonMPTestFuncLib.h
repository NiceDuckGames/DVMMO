// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ThirdPersonMPTestFuncLib.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONMP_API UThirdPersonMPTestFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category="Math|Random")
	static int32 RandomInteger(int32 max);

	UFUNCTION(BlueprintCallable, Category="Misc")
	static void Foo();

	UFUNCTION(BlueprintCallable, Category="Vulns|BufferOverflow")
	static void Login(const FString& UserName, const FString& Password);
};
