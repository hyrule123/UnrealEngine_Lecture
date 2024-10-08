// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PersonImpl.generated.h"

/**
 * 외부에는 공개하기 싫은 내부 클래스
 */
UCLASS()
class UPersonImpl : public UObject
{
	GENERATED_BODY()
public:
	UPersonImpl();

	void SetName(const FString& InName) { Name = InName; }
	const FString& GetName() { return Name; }
	void SetID(int32 InID) { ID = InID; }
	int32 GetID() const { return ID; }

private:
	FString Name;
	int32 ID;
};
