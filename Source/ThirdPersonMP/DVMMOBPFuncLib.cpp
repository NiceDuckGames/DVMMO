// Fill out your copyright notice in the Description page of Project Settings.


#include "DVMMOBPFuncLib.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "Networking/Public/Interfaces/IPv4/IPv4Address.h" // not sure why I need the full path
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

class UDPServer : public FRunnable {
public:
	UDPServer(int32 Port) {
		ListenSocket = FUdpSocketBuilder(TEXT("UDPSERVER"))
			.AsNonBlocking()
			.AsReusable()
			.BoundToPort(Port)
			.Build();

		Thread = FRunnableThread::Create(this, TEXT("UDPServer"), 0, TPri_BelowNormal);
	}

	virtual uint32 Run() override {
		while (true) {
			if (ListenSocket) {
				TSharedRef<FInternetAddr> Sender = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
				int32 BytesRead;
				uint8 Data[1024];

				// Receive the data
				bool bReceivedData = ListenSocket->RevcFrom(Data, 1024, BytesRead, *Sender);

				if (bReceivedData) {
					// Received some data, process it here

				}
			}
		}
	}
};

