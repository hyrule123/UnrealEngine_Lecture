// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerializationTest.h"
#include "SerializationTest_Derived.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API USerializationTest_Derived : public USerializationTest
{
	GENERATED_BODY()
public:
	virtual void Serialize(FArchive& Ar) final;

	UPROPERTY()
	int32 ID;
};
