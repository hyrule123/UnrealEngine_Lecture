// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture12_MemoryManagement.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture12_MemoryManagement : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
	UPROPERTY()
	TObjectPtr<class UStudent> PropStudent;
	//UPROPERTY()를 빼고 선언하여 GC에서 추적되지 않도록 만든다.
	TObjectPtr<class UStudent> NonPropStudent;

	//배열도 마찬가지로 UPROPERTY()가 붙지 않으면 GC 추적이 되지 않는다.
	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> PropStudents;
	TArray<TObjectPtr<class UStudent>> NotPropStudents;

	class FStudentManager* StudentManager_GCTraceEnabled = nullptr;
	class FStudentManager* StudentManager_GCTraceDisabled = nullptr;

};
