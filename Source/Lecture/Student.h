// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LessonInterface.h"
#include "Person.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class LECTURE_API UStudent : public UPerson, public ILessonInterface
{
	GENERATED_BODY()
public:
	UStudent();

	virtual void DoLesson() override;

	//CourseInfo의 전방선언도, 헤더 인클루드도 없음. 함수 하나 선언으로 끝 
	void GetNotification(const FString& School, const FString& NewCourseInfo);
	int32 GetStudentID() const { return StudentID; }

private:
	UPROPERTY()
	int32 StudentID;
	
};
