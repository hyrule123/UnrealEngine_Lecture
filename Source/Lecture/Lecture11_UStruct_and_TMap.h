// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture11_UStruct_and_TMap.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("홍길동");
		ID = 0;
	}

	//구조체는 NewObject를 사용해서 만드는 것이 아니므로
	//인자를 가진 생성자를 자유롭게 사용해도 된다.
	FStudentData(FString InName, int32 InOrder)
		: Name(InName)
		, ID(InOrder)
	{
	}

	//TSet, TMap의 키값으로 사용하기 위한 함수
	//== operator
	bool operator==(const FStudentData& InStudentData) const
	{
		return this->Name == InStudentData.Name;
	}
	//GetTypeHash 함수(언리얼 API인 GetTypeHash를 호출)
	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Name);
	}

	//UPROPERTY 매크로를 넣을 때는 넣는 목적이 있어야 한다.
	//1. 블루프린트에 표시한다던지
	//2. 프로퍼티 시스템에 등록한다던지
	//	-> 특히 UObject 포인터의 경우에는 프로퍼티 시스템에 반드시 등록해줘야 함
	UPROPERTY()
	FName Name;	//해시 키값으로도 사용될 예정이므로 FString이 아닌 FName 형태로 저장한다.

	UPROPERTY()
	int32 ID;
};

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
