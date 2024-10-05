// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture8_Composition.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture8_Composition : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
};
