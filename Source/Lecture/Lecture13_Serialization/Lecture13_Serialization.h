// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Lecture13_Serialization.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API ULecture13_Serialization : public UGameInstance
{
	GENERATED_BODY()
public:
	ULecture13_Serialization();
	virtual void Init() override;

private:
	void Serialize_Struct(const FString& FilePath);
	void Deserialize_Struct(const FString& FilePath);

	/* 하면서 발견한 주의점
	* UPROPERTY()로 다른 UObject 주소를 멤버변수로 가지고 있는 클래스의 경우 아래 함수의 방법으로는 할 수 없다. 에러 발생함.
	* FArchiveUObject 라는 다른 클래스를 활용해야 함
	*/
	void Serialize_UObject(const FString& FilePath);
	void Deserialize_UObject(const FString& FilePath);

	//프로퍼티 시스템을 통해서 직렬화하는 것이므로 
	// UPROPERTY()가 등록되지 않은 멤버변수는 제외된다.
	void Serialize_Json(const FString& FilePath);
	void DeSerialize_Json(const FString& FilePath);

private:
	UPROPERTY()
	TObjectPtr<class USerializationTest_Derived> SerSrc;
};
