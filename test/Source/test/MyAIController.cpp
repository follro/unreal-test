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

//���� ���������� (�� Ai���� ������ �Ѱ��ָ�ȴ�)
void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//3�ʸ��� �ѹ��� RandomMove ����
	//GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AMyAIController::RandomMove, 3.f, true);

	//�����带 ���� ����
	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			//ToDo
		}
	}
}

//���ǰ� ������ (�������� ������ �������ش�.)
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

	//���� ��ġ���� �� �� �ִ� ��������Ʈ �� �ϳ��� �����ִ� ��
	if(NaveSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
}
