// Fill out your copyright notice in the Description page of Project Settings.
#include "Lecture12_MemoryManagement.h"

#include "Student.h"
#include "StudentManager.h"

void CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
	//콘텐츠 제작 단계에서는 ::IsValid() 라는 함수를 사용하지만, 
	//더 깊숙히 알아보기 위해 로우레벨 API를 사용
	//정의부로 들어가보면 GUObjectArray를 참조하는 것을 확인할 수 있다.
	if (InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	//콘텐츠 제작 단계에서는 ::IsValid() 라는 함수를 사용하지만, 
	//더 깊숙히 알아보기 위해 로우레벨 API를 사용
	//정의부로 들어가보면 GUObjectArray를 참조하는 것을 확인할 수 있다.
	if (nullptr != InObject)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] is NOT nullptr"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] is nullptr"), *InTag);
	}
}

void ULecture12_MemoryManagement::Init()
{
	Super::Init();

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	StudentManager_GCTraceEnabled = new FStudentManager(NewObject<UStudent>(), true);
	StudentManager_GCTraceDisabled = new FStudentManager(NewObject<UStudent>(), false);
}

void ULecture12_MemoryManagement::Shutdown()
{
	Super::Shutdown();

	//GC 추적을 받지 못하는 포인터에 저장했으므로, GC에서는 쓰레기값이라고 판단하여 회수했을 것임.
	{
		const UStudent* StudentPtrInManager = StudentManager_GCTraceEnabled->GetStudent();

		delete StudentManager_GCTraceEnabled;
		StudentManager_GCTraceEnabled = nullptr;

		//댕글링 포인터 문제 발생
		CheckUObjectIsNull(StudentPtrInManager, TEXT("GC 추적에 등록한 C++ 클래스의 Student"));
		CheckUObjectIsValid(StudentPtrInManager, TEXT("GC 추적에 등록한 C++ 클래스의 Student"));
	}

	//GC 추적을 받는 상태
	{
		const UStudent* StudentPtrInManager = StudentManager_GCTraceDisabled->GetStudent();

		//클래스를 삭제해도
		delete StudentManager_GCTraceDisabled;
		StudentManager_GCTraceDisabled = nullptr;

		//포인터 상태는 정상 -> 다음 GC가 돌 때 제거될 예정
		CheckUObjectIsNull(StudentPtrInManager, TEXT("GC 추적에 등록하지 않은 C++ 클래스의 Student"));
		CheckUObjectIsValid(StudentPtrInManager, TEXT("GC 추적에 등록하지 않은 C++ 클래스의 Student"));
	}


	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));
	/*로그에는 다음과 같이 찍히는 것을 확인할 수 있다.
	LogTemp: [NonPropStudent] is NOT nullptr
	LogTemp: [NonPropStudent] 유효하지 않은 언리얼 오브젝트
	LogTemp: [PropStudent] is NOT nullptr
	LogTemp: [PropStudent] 유효한 언리얼 오브젝트
	*/
}
