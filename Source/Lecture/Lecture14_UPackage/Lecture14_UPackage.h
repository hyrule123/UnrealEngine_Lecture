// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture14_UPackage.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture14_UPackage : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

private:
	void SavePackage() const;
	void LoadPackage() const;
};
