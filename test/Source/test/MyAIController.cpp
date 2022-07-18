// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AMyAIController::AMyAIController()
{
	
}

//���� ���������� (�� Ai���� ������ �Ѱ��ָ�ȴ�)
void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//3�ʸ��� �ѹ��� RandomMove ����
	GetWorld()->GetTimerManager().SetTimer(Timerhandle, this, &AMyAIController::RandomMove, 3.f, true);
}

//���ǰ� ������ (�������� ������ �������ش�.)
void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(Timerhandle);
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
