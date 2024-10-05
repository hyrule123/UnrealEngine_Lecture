// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

class UCard;

/**
 * 
 */
UCLASS()
class LECTURE_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();
	
	const FString& GetPersonName() const;
	void SetPersonName(const FString& InName);

	UCard* GetCard() const { return Card; }

protected:
	UPROPERTY()
	FString PersonName;

	UPROPERTY()
	int32 Year;

	UPROPERTY()
	TObjectPtr<UCard> Card;
};
