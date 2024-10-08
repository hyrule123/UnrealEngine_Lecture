// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ModulePerson.generated.h"


/**
 * 
 */
UCLASS()
class MODULEEXAMPLE_API UModulePerson : public UObject
{
	GENERATED_BODY()
public:
	UModulePerson();
	
	const FString& GetName() const;
	int32 GetID() const;

private:
	//Impl 부분을 완전히 숨기는 것도 가능.
	UPROPERTY()
	TObjectPtr<class UPersonImpl> PersonPrivate;
};
