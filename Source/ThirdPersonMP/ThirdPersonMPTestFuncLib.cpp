// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonMPTestFuncLib.h"

int32 UThirdPersonMPTestFuncLib::RandomInteger(int32 max)
{
	return 1;
}

void UThirdPersonMPTestFuncLib::Foo()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello from Foo"));
}

void UThirdPersonMPTestFuncLib::Login(const FString& UserName, const FString& Password)
{
	int* p = 0;
	*p = 1;
}
