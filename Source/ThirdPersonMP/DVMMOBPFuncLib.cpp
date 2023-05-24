// Fill out your copyright notice in the Description page of Project Settings.


#include "DVMMOBPFuncLib.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h" // not sure why I need the full path
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Serialization/MemoryWriter.h"

FUDPServer::FUDPServer(int32 Port) {
	ListenSocket = FUdpSocketBuilder(TEXT("UDPSERVER"))
		.AsNonBlocking()
		.AsReusable()
		.BoundToPort(Port)
		.Build();

	Thread = FRunnableThread::Create(this, TEXT("UDPServer"), 0, TPri_BelowNormal);
}

FUDPServer::~FUDPServer() {
	Thread->Kill(true);
	delete Thread;
	ListenSocket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
}

uint32 FUDPServer::Run() {
	while (true) {
		if (ListenSocket) {
			TSharedRef<FInternetAddr> Sender = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
			int32 BytesRead;
			uint8 Data[1024];

			// Receive the data
			bool bReceivedData = ListenSocket->RecvFrom(Data, 1024, BytesRead, *Sender);

			if (bReceivedData) {
				// Received some data, process it here

			}
		}
	}
	return 0;
};

bool UDVMMOBPFuncLib::StartUDPServer(int32 Port) {
	FUDPServer* Server = new FUDPServer(Port);
	return Server != nullptr;
}

bool UDVMMOBPFuncLib::SendGameMessageToServer(FString IPAddress, int32 Port, FGameMessageStruct Message) {
	// Create a socket
	FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_DGram, TEXT("default"), false);

	// Create an internet address
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid;
	addr->SetIp(*IPAddress, bIsValid);
	if (!bIsValid) {
		return false;
	}
	addr->SetPort(Port);

	// Serialize the struct to a byte array
	TArray<uint8> Bytes;
	FMemoryWriter MemoryWriter(Bytes, true);
	MemoryWriter << Message;

	// Send the bytes
	int32 BytesSent;
	bool bSuccess = Socket->SendTo(Bytes.GetData(), Bytes.Num(), BytesSent, *addr);

	// Clean up the socket
	Socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);

	return bSuccess;
}