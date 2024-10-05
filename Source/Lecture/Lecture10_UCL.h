// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture10_UCL.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture10_UCL : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

private:
	void TArray_Example();
	void TSet_Example();
};
