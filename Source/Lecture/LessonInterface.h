// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LessonInterface.generated.h"

// This class does not need to be modified.
//타입 정보를 보관하기 위해 생성한 클래스. 변경 필요 없음.
UINTERFACE(MinimalAPI)
class ULessonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 요걸 수정해야 함
 * 이 클래스를 다중상속 받으면 구현을 강제할 수 있게 된다.
 */
class LECTURE_API ILessonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//인터페이스 함수: 순수가상함수로도 구현할수도 있고
	//virtual void DoLesson() = 0;
	//일반 가상함수로도 구현 가능하다.(모던 언어 추상클래스와의 차이점)
	virtual void DoLesson();
};
