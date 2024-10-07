// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SerializationTest.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API USerializationTest : public UObject
{
	GENERATED_BODY()
public:
	virtual void Serialize(FArchive& Ar) override;

	UPROPERTY()
	FString Name;
};
