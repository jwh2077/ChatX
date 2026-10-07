// CXPlayerController.cpp

#include "Player/CXPlayerController.h"
#include "UI/CXChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ChatX.h"


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

	PrintChatMessageString(ChatMessageString);
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);

	//FString NetModeString = ChatXFunctionLibrary::GetNetModeString(this);
	//FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
	//ChatXFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.f);
	// 문제 상황이 생기면, 위와 같은 로깅 함수로 다양한 변수의 값들과 함수이름을 확인해서 
	// 문제의 원인을 적극적으로 찾아보세요!
	
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);

}