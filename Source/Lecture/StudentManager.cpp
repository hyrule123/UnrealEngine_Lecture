// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentManager.h"
#include "Student.h"

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	//Collector에 주소를 등록
	if (IsRegisterGC && SafeStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(SafeStudent);
	}
}
