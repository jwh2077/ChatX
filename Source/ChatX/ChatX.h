// ChatX.h

#pragma once

#include "CoreMinimal.h"

class ChatXFunctionLibrary
{
public:
	//PrintString 구현
	//InWorldContextActor 월드와 연결된 액터
	//InString 출력할 문자열
	//InTimeToDisplay 출력할 시간
	//InColor 출력할 색상
	static void MyPrintString(const AActor* InWorldContextActor, const FString& InString, float InTimeToDisplay = 1.f, FColor InColor = FColor::Cyan)
	{
		if (IsValid(GEngine) == true && IsValid(InWorldContextActor) == true)
		{
			if (InWorldContextActor->GetNetMode() == NM_Client || InWorldContextActor->GetNetMode() == NM_ListenServer)
			{
				// 클라이언트에서는 화면에 출력
				GEngine->AddOnScreenDebugMessage(-1, InTimeToDisplay, InColor, InString);
			}
			else
			{
				// 서버에서는 로그로 출력
				UE_LOG(LogTemp, Log, TEXT("%s"), *InString);
			}
		}
	}

	// GetNetMode 함수의 통해 얻음 값을 문자열로 변환하여 반환
	static FString GetNetModeString(const AActor* InWorldContextActor)
	{
		FString NetModeString = TEXT("None");

		if (IsValid(InWorldContextActor) == true)
		{
			ENetMode NetMode = InWorldContextActor->GetNetMode();
			if (NetMode == NM_Client)
			{
				NetModeString = TEXT("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{
					NetModeString = TEXT("StandAlone");
				}
				else
				{
					NetModeString = TEXT("Server");
				}
			}
		}

		return NetModeString;
	}

};

