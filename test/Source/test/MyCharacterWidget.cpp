// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterWidget.h"

#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacterWidget::BindHp(class UMyStatComponent* StatComp)
{
	//PB_HpBar123 = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar"); <- 이름을 메타를 맞춰줫으므로 찾아주지 않아도 되지만 다르게 하였다면 이렇게 찾아가서 매핑가능함.
	CurrentStatComp = StatComp;
	//델리게이트로 연결 AddUObject로 내부적으로 정의 된 함수 연결한다. Stat컴포넌트에서 hp가 변동이 일어나면 UpDateHp 함수를 실행한다., OnHpchaged를 구독중 즉 브로드 캐스트를 받는중
	StatComp->OnHpChanged.AddUObject(this, & UMyCharacterWidget::UpDateHp);

	
}


//hp갱신 1씩데미지를 입어도 계속 호출하므로 효율이 구림
void UMyCharacterWidget::UpDateHp()
{
	
	if(CurrentStatComp.IsValid())
	PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	
}
