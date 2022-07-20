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

	//���� ��ġ���� �� �� �ִ� ��������Ʈ �� �ϳ��� �����ִ� ��
	if (NaveSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);

		//�������� �̸� �������� ���� ��Ʈ�� �����Ǹ� �����ϸ��
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")),RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;;
}


