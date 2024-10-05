// Fill out your copyright notice in the Description page of Project Settings.


#include "Lecture9_Delegate.h"
#include "CourseInfo.h"
#include "Student.h"

ULecture9_Delegate::ULecture9_Delegate()
{
	SchoolName = TEXT("A 학교");
}

void ULecture9_Delegate::Init()
{
	Super::Init();

	//컴포지션 관계를 CDO(생성자)가 아닌 다른 곳에서 선언할 때는
	//NewObject의 인자로 부모가 될 UObject의 주소를 넣어주면 됨.
	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("======================="));

	TArray<UStudent*> Students;
	for (int i = 0; i < 3; ++i) {
		int32 idx = Students.Add(NewObject<UStudent>());
		FString Name = TEXT("학생");
		Name += FString::FromInt(idx + 1);
		Students[i]->SetPersonName(Name);
	}

	//델리게이트에 등록
	for (auto* Student : Students)
	{
		CourseInfo->OnChanged.AddUObject(Student, &UStudent::GetNotification);
	}

	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));
	

	UE_LOG(LogTemp, Log, TEXT("======================="));
}
