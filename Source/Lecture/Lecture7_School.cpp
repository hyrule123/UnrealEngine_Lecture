// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture7_School.h"

#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

ULecture7_School::ULecture7_School()
{
	SchoolName = TEXT("기본학교");
}

void ULecture7_School::Init()
{
	Super::Init();

	TArray<UPerson*> Persons =
	{ NewObject<UTeacher>(), NewObject<UStudent>(), NewObject<UStaff>() };

	//UPerson 중 수업에 참여한, 즉 ILessonInterface 클래스를 상속한 경우에만
	//DoLesson() 함수를 호출할 수 있게 된다.
	//이를 확인하기 위해서는 Cast<>() 함수를 사용하면 된다.
	UE_LOG(LogTemp, Log, TEXT("=====수업 참여 가능 여부====="));
	for (UPerson* Person : Persons) 
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s 님은 수업에 참여할 수 있습니다."), *Person->GetPersonName());
			LessonInterface->DoLesson();
		}
		else {

			UE_LOG(LogTemp, Log, TEXT("%s 님은 수업에 참여할 수 없습니다."), *Person->GetPersonName());
		}

	}
	UE_LOG(LogTemp, Log, TEXT("====================="));
}
