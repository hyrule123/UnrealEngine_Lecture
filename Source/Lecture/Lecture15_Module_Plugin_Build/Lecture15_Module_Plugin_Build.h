// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture15_Module_Plugin_Build.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture15_Module_Plugin_Build : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

private:
	UPROPERTY()
	TObjectPtr<class UModulePerson> PersonAPI;
};
