// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * Game Instance
 * 싱글턴 패턴의 클래스. 각 게임마다 단 하나의 인스턴스를 가지고 있다.
 * 기본적으로 GameInstance 클래스가 언리얼에서 사용되는데, 
 * 이걸 직접 만든 MyGameInstance로 바꾸는 것이 목표
 */
UCLASS()
class LECTURE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY() //언리얼 클래스 상속 시 반드시 작성
public:
	virtual void Init() override;
};
