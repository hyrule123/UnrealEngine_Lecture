// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PackageExample.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API UPackageExample : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY() 
	FString Name;

	UPROPERTY()
	int32 ID;
};
