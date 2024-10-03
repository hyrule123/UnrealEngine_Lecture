// Fill out your copyright notice in the Description page of Project Settings.


#include "PropertySystem_Example.h"	//자신
#include "Teacher.h"
#include "Student.h"

UPropertySystem_Example::UPropertySystem_Example()
{
	//생성자에서 지정한 학교 이름은 CDO의 기본값이 된다.
	//중요: CDO 기본값을 변경하는 경우에는 에디터를 끄고 재컴파일을 해야함.
	
	//이유
	//CDO의 생성 시점: 에디터 초기화 중(실행 전)
	// 중단점을 걸고 확인하면 에디터가 실행되기 이전임을 알 수 있다.
	
	SchoolName = TEXT("기본 학교이름");
}

void UPropertySystem_Example::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("===================="));

	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UPropertySystem_Example::StaticClass();

	//assertion, crash reporter를 띄움
	check(ClassRuntime == ClassCompile);

	//에러만 띄움
	ensure(ClassRuntime != ClassCompile);
	//에러 메시지까지 띄움
	ensureMsgf(ClassRuntime != ClassCompile, TEXT("일부러 에러를 발생시킨 코드"));

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름: %s"), *ClassRuntime->GetName());

	SchoolName = TEXT("변경한 학교이름");

	UE_LOG(LogTemp, Log, TEXT("현재 학교 이름: %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UPropertySystem_Example>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("===================="));


	//새로운 객체 생성은 NewObject<>()를 사용한다.
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	//C++의 가장 기본적인 Getter/Setter 사용 방식
	Student->SetPersonName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 %s"), *Student->GetPersonName());

	//UPROPERTY system을 통해서 Get/Set - 참고용으로 알아두기
	//프로퍼티 시스템을 사용할 경우 접근 지시자 제한과 상관없이 값을 설정할 수 있다.
	FString CurrentTeacherName;
	FString ChangeTeacherName = TEXT("이득우");

	//변수명을 넣어주면 해당 변수 프로퍼티가 있을 경우 포인터가 반환된다.
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("PersonName"));
	if (NameProp) {
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("Property System으로 가져온 선생님 이름: %s"), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &ChangeTeacherName);
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("Property System으로 다시 설정하고 가져온 선생님 이름: %s"), *CurrentTeacherName);
	}

	Teacher->DoLesson();

	//UFUNCTION을 프로퍼티 시스템을 활용해 호출해 보기
	UFunction* DoLessonFunc = Student->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc) {
		Student->ProcessEvent(DoLessonFunc, nullptr);
	}
}
