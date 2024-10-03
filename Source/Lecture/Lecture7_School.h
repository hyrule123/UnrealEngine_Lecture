// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture7_School.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture7_School : public UGameInstance
{
	GENERATED_BODY()
public:
	ULecture7_School();
	virtual void Init() override;

private:
	UPROPERTY()
	FString SchoolName;
};
