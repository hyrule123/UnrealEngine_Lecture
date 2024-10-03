// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TCHAR_FString_Example.generated.h"

/**
 * TCHAR과 FString 각종 코드 예시 모음
 */
UCLASS()
class LECTURE_API UTCHAR_FString_Example : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
};
