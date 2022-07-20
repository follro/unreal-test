// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"



AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/BT_MyCharacter.BT_MyCharacter'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/BB_MyCharacter.BB_MyCharacter'"));
	if(BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}

	

}

//빙의 시작했을때 (즉 Ai관련 정보를 넘겨주면된다)
void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//3초마다 한번씩 RandomMove 실행
	//GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AMyAIController::RandomMove, 3.f, true);

	//블랙보드를 통한 제어
	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			//ToDo
		}
	}
}

//빙의가 끝날때 (끝났으면 정보를 해제해준다.)
void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	//GetWorld()->GetTimerManager().ClearTimer(Timerhandle);
}

void AMyAIController::RandomMove()
{
	auto CurrenPawn = GetPawn();

	UNavigationSystemV1* NaveSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(NaveSystem==nullptr)
		return;

	FNavLocation RandomLocation;

	//현재 위치에서 갈 수 있는 랜덤포인트 중 하나를 집어주는 것
	if(NaveSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
}
