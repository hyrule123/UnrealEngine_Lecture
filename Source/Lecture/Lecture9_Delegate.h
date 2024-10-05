// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture9_Delegate.generated.h"

/**
 * 델리게이트를 관리하는 중간 발행자 역할
 */
UCLASS()
class LECTURE_API ULecture9_Delegate : public UGameInstance
{
	GENERATED_BODY()
public:
	ULecture9_Delegate();
	virtual void Init() override;

private:
	FString SchoolName;

	TObjectPtr<class UCourseInfo> CourseInfo;
};
