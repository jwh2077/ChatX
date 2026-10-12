// CXGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CXGameModeBase.generated.h"

class ACXPlayerController;

/**
 *
 */
UCLASS()
class CHATX_API ACXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	//중간에서 정답을 체가지 못하도록 서버에서 정답을 생성하고 관리
	//정답 숫자 생성
	FString GenerateSecretNumber();

	//사용자가 입력한 숫자 문자열이 3자리인지, 중복된 숫자가 없는지, 0이 포함되어 있는지 확인
	//즉 유효한 입력 확인
	bool IsGuessNumberString(const FString& InNumberString);

	//사용자가 입력한 숫자 문자열과 정답 숫자 문자열을 비교하여 결과를 반환
	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	virtual void BeginPlay() override;

	void PrintChatMessageString(ACXPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	void IncreaseGuessCount(ACXPlayerController* InChattingPlayerController);

	void ResetGame();

	void JudgeGame(ACXPlayerController* InChattingPlayerController, int InStrikeCount);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<ACXPlayerController>> AllPlayerControllers;

};