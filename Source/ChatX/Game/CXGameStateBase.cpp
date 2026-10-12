// CXGameStateBase.cpp


#include "CXGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/CXPlayerController.h"

void ACXGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	// 서버가 아닌 경우에만 실행
	if (HasAuthority() == false)
	{
		//0번 서버가 아닌 로컬에서의 컨트롤러를 가져옴 즉 내 로컬플레이어컨트롤러를 가져옴
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			// 유효할시 CXPlayerController로 캐스팅
			ACXPlayerController* CXPC = Cast<ACXPlayerController>(PC);
			// 유효할시 채팅 메시지 출력
			if (IsValid(CXPC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				CXPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}