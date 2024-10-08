// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
//FStreamableManager는 멤버에 Value 변수로 선언하기 때문에 헤더 포함이 필요
#include "Engine/StreamableManager.h"
#include "Lecture14_UPackage.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture14_UPackage : public UGameInstance
{
	GENERATED_BODY()
public:
	ULecture14_UPackage();
	virtual void Init() override;

private:
	void SavePackage() const;
	void LoadPackage() const;
	void LoadExampleObject() const;
	void LoadExampleObjectAsync();

private:
	//비동기 로딩 관리 클래스
	FStreamableManager StreamableManager;

	//비동기 로딩 관련
	TSharedPtr<FStreamableHandle> Handle;
};
