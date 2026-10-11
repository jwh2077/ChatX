// CXGameStateBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CXGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CHATX_API ACXGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	// NetMulticast를 사용하여 이 Actor가 복제되어 존재하는 클라이언트들에게 메시지를 보내는 RPC 함수
	// 로그인 메시지를 브로드캐스트하는 기능을 수행
	// Reliable로 지정하여 연결이 유지되는 동안 RPC가 유실되지 않도록 신뢰성 있게 전달
	// InNameString 매개변수는 기본값으로 "XXXXXXX" 현재는 정보를 불러오지 않음
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));
};
