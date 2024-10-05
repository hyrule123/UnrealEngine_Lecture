// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

//델리게이트 선언
//UClass를 상속받은 클래스가 아님 = F
//언리얼에서 보통 델리게이트 이름에 Signature라는 이름을 많이 붙임
DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);


/**
 * 
 */
UCLASS()
class LECTURE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
public:
	UCourseInfo();

	FCourseInfoOnChangedSignature OnChanged;
	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	FString Contents;
};
