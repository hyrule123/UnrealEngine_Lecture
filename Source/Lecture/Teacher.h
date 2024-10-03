// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.h"
#include "Teacher.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API UTeacher : public UPerson
{
	GENERATED_BODY()
public:
	UTeacher();

	//override 한 경우 UFUNCTION()을 중복 작성할 필요는 없다.
	//UFUNCTION 내부 파라미터를 변경할 경우에는 작성 가능
	virtual void DoLesson() override;
	
private:
	UPROPERTY()
	int32 TeacherID;
};
