// CXPlayerController.cpp

#include "Player/CXPlayerController.h"
#include "UI/CXChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatX.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/CXGameModeBase.h"
#include "CXPlayerState.h"
#include "Net/UnrealNetwork.h"


ACXPlayerController::ACXPlayerController()
{
	bReplicates = true;
}

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ACXPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	{
		ChatMessageString = InChatMessageString;

		if (IsLocalController() == true)
		{
			ACXPlayerState* CXPS = GetPlayerState<ACXPlayerState>();
			if (IsValid(CXPS) == true)
			{
				FString CombinedMessageString = CXPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

				ServerRPCPrintChatMessageString(CombinedMessageString);
			}
		}
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{	
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

//_Implementation를 붙여야 한다. 붙이지 않으면 RPC가 작동하지 않는다.일종의 규칙(문법)이다.
void ACXPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	// 클라이언트에서 메시지를 출력
	PrintChatMessageString(InChatMessageString);
}

void ACXPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ACXGameModeBase* CXGM = Cast<ACXGameModeBase>(GM);
		if (IsValid(CXGM) == true)
		{
			CXGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}