// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterWidget.h"

#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacterWidget::BindHp(class UMyStatComponent* StatComp)
{
	//PB_HpBar123 = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar"); <- �̸��� ��Ÿ�� ����Z���Ƿ� ã������ �ʾƵ� ������ �ٸ��� �Ͽ��ٸ� �̷��� ã�ư��� ���ΰ�����.
	CurrentStatComp = StatComp;
	//��������Ʈ�� ���� AddUObject�� ���������� ���� �� �Լ� �����Ѵ�. Stat������Ʈ���� hp�� ������ �Ͼ�� UpDateHp �Լ��� �����Ѵ�., OnHpchaged�� ������ �� ��ε� ĳ��Ʈ�� �޴���
	StatComp->OnHpChanged.AddUObject(this, & UMyCharacterWidget::UpDateHp);

	
}


//hp���� 1���������� �Ծ ��� ȣ���ϹǷ� ȿ���� ����
void UMyCharacterWidget::UpDateHp()
{
	
	if(CurrentStatComp.IsValid())
	PB_HpBar->SetPercent(CurrentStatComp->GetHpRatio());
	
}
