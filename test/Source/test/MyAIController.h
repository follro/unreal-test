// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:

	void RandomMove();

private:
	FTimerHandle Timerhandle;//GetTimerManager().SetTimer에서 요구하는 핸들, 타이머 핸들을 통해 예약한것을 취소하고 싶을때.
};