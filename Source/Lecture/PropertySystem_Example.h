// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PropertySystem_Example.generated.h"

/**
 * 실습 예제 클래스. 클래스 구조는 아래 링크 참고
 * https://www.notion.so/hyrule1/114cb63f18c18082b796d9b912a7d642?pvs=4
 */
UCLASS()
class LECTURE_API UPropertySystem_Example : public UGameInstance
{
	GENERATED_BODY()
public:
	UPropertySystem_Example();
	virtual void Init() override;

private:
	UPROPERTY()
	FString SchoolName;
};
