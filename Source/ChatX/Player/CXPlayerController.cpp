// CXPlayerController.cpp

#include "Player/CXPlayerController.h"
#include "UI/CXChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatX.h"
#include "EngineUtils.h"


void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!IsLocalController())
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass))
	{
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance))
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	//PrintChatMessageString(InChatMessageString);
	
	//매세지 전송은 로컬(내 컴퓨터)에서 전송
	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);

	//FString NetModeString = ChatXFunctionLibrary::GetNetModeString(this);
	//FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
	//ChatXFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.f);

	
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
	// 서버에서 모든 클라이언트에게 메시지를 전송
	// 클라이언트 커넥션이 있는 ACXPlayerController를 어떻게 찾을 수 있을까? 
	// TActorIterator를 사용하면 된다. TActorIterator는 특정 클래스의 모든 액터를 순회할 수 있는 반복자이다. 
	// GetWorld()를 통해 현재 월드를 가져오고, 
	// 그 월드에서 ACXPlayerController를 순회한다.
	// 변수It는 반복문이 배열의 각 요소를 가리킬때 사용되는 반복자이다
	for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
	{
		ACXPlayerController* CXPlayerController = *It;
		if (IsValid(CXPlayerController) == true)
		{
			// 서버에서 클라이언트로 RPC 호출
			CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
		}
	}
}