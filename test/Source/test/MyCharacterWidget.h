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

	TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;//스마트 포인터를 사용하는 것이 적합
	//class UMyStatComponent* CurrentStatComp;

	//meta를 맞춰줌으로 이름으로 알아서 찾아서 매핑이된다
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;
};
