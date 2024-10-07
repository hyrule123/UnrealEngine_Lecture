// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//UObject가 아닌 일반 C++ 오브젝트에서 GC 추적을 받도록 하려면 FGCObject를 상속받아주면 된다.
class LECTURE_API FStudentManager : public FGCObject
{
public:
	FStudentManager(class UStudent* InStudent, bool RegisterGC)
		: SafeStudent(InStudent)
		, IsRegisterGC(RegisterGC)
	{
	}

	//override 1: 이 클래스의 이름을 전달
	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}

	//override 2: 추적을 받을 오브젝트를 등록
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	UStudent* GetStudent() { return SafeStudent; }

private:
	class UStudent* SafeStudent = nullptr;
	const bool IsRegisterGC;
};
