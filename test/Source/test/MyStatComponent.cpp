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

	bWantsInitializeComponent = true;//PostInitializeComponent랑은 다르게 이걸 트루로 해줘야 실행가능


	Level = 1; //레벨 기본값
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


//현재 레벨에 따른 능력치를 적용
void UMyStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));//싱글톤처럼 언제어디서든 긁어 올 수 있는 개념(여기선 필요할때마다 데이터 매니저에서 찾아옴)

	//MyGameInstance가 존재하면 스텟데이터에서 정보를 꺼내와 적용
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

	//구독해놓은 사람들에게 Hp변경을 브로드 캐스트 시전(OnHpChanged를 구독한 사람을 찾는다.)
	OnHpChanged.Broadcast();
}


//피격시
void UMyStatComponent::OnAttacked(float DamageAmount)
{
	int32 Newhp = Hp - DamageAmount;
	SetHp(Newhp);

	//UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}





