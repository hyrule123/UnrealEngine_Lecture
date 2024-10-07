// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "StudentData.h"

#include "Lecture11_UStruct_and_TMap.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture11_UStruct_and_TMap : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

private:
	void CreateRandomStudentsData();
	void Algo_Transform_Example();
	void TSet_TMap_Example();
	void TMultiMap_MultiFind_Example();
	void Custom_Struct_Key_Example();

private:
	//블루프린트에 보여지는가? X
	//언리얼 시스템으로 동적할당된 포인터 주소를 저장하는가? X
	//->UPROPERTY()가 필요 없다.
	TArray<FStudentData> StudentsData;
};
