// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	//상위 클래스의 Init 함수를 반드시 호출한 후 내 코드를 호출해야 함
	Super::Init();

	//LogTemp: 이 로그의 카테고리
	//Log: 출력 수준. 일반적인 로그 출력은 Log 사용해주면 됨
	//TEXT: 언리얼에서 사용하는 텍스트 매크로.
	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal!"));

	//언리얼 코드 컴파일 방법
	//헤더 파일에만 변경이 발생하면 에디터를 끄고 비주얼 스튜디오에서 컴파일(Ctrl + F5)
	//소스 파일에서 변경이 발생하면 - 라이브 코딩으로 컴파일(Ctrl + Alt + F11)

	//클래스 추가는 반드시 언리얼 에디터상에서 진행할 것.
	//비주얼 스튜디오에서 추가 X
}
