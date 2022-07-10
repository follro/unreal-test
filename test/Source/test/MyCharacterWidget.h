// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UMyCharacterWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void BindHp(class UMyStatComponent* StatComp);

	void UpDateHp();
private:

	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;//����Ʈ �����͸� ����ϴ� ���� ����
	//class UMyStatComponent* CurrentStatComp;

	//meta�� ���������� �̸����� �˾Ƽ� ã�Ƽ� �����̵ȴ�
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;
};
