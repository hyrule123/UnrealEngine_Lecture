// Fill out your copyright notice in the Description page of Project Settings.
#include "PluginPersonFactory.h"

#include "PluginPerson_Impl.h"

IPluginPerson* UPluginPersonFactory::CreatePluginPerson()
{
	//내부 PluginPerson을 리턴해준다.
	//TSharedPtr<IPluginPerson>을 리턴해주려 했으나, IPluginPerson이 UObject를 상속받고 있지 않아서 컴파일 에러가 발생함.
	//UObject를 상속받은 중간 클래스를 하나 추가로 등록해줘야 하는듯.
	return NewObject<UPluginPerson_Impl>();
}
