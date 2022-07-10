// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;//PostInitializeComponent���� �ٸ��� �̰� Ʈ��� ����� ���డ��


	Level = 1; //���� �⺻��
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}


//���� ������ ���� �ɷ�ġ�� ����
void UMyStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));//�̱���ó�� ������𼭵� �ܾ� �� �� �ִ� ����(���⼱ �ʿ��Ҷ����� ������ �Ŵ������� ã�ƿ�)

	//MyGameInstance�� �����ϸ� ���ݵ����Ϳ��� ������ ������ ����
	if(MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(NewLevel);
		if(StatData)
		{
			Level = StatData->Level;
			SetHp(StatData->MaxHp);
			MaxHp = StatData->MaxHp;
			Attack = StatData->Attack;
		}
	}
}

void UMyStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;

	if (Hp < 0)
		Hp = 0;

	//�����س��� ����鿡�� Hp������ ��ε� ĳ��Ʈ ����(OnHpChanged�� ������ ����� ã�´�.)
	OnHpChanged.Broadcast();
}


//�ǰݽ�
void UMyStatComponent::OnAttacked(float DamageAmount)
{
	int32 Newhp = Hp - DamageAmount;
	SetHp(Newhp);

	//UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}





