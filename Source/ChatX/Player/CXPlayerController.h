// CXPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CXPlayerController.generated.h"

class UCXChatInput;

/**
 *
 */
UCLASS()
class CHATX_API ACXPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

	//클라이언트로 출력하는 RPC
	//Client에서 실행
	//Reliable 무족건 실행
	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	//서버로 보내는 RPC
	//Server에서 실행
	//Reliable 무족건 실행
	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCXChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UCXChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;
};
