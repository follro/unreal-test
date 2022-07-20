// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"

#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	
}


EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrenPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(CurrenPawn==nullptr)
	{
		return EBTNodeResult::Failed;
	}


	UNavigationSystemV1* NaveSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NaveSystem == nullptr)
		return EBTNodeResult::Failed;;

	FNavLocation RandomLocation;

	//현재 위치에서 갈 수 있는 랜덤포인트 중 하나를 집어주는 것
	if (NaveSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);

		//블랙보드의 미리 만들어놓은 변수 패트롤 포지션만 수정하면됨
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")),RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;;
}


