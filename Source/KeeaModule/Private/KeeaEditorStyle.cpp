// Fill out your copyright notice in the Description page of Project Settings.


#include "KeeaEditorStyle.h"
#include "SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Text/SlateTextRun.h"
#include "IPluginManager.h"
#include "SlateApplication.h"

TSharedPtr<FSlateStyleSet> KeeaEditorStyle::StyleInstance = NULL;

//인스턴스를 생성하고 레지스트
void KeeaEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid()) {
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

//인스턴스를 언레지스트하고 리셋
void KeeaEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

//파일로부터 슬레이트 스타일을 정의해주는 매크로.
#define IMAGE_BRUSH(RelativePath, ...)	FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
// 40x40 이미지 사이즈
const FVector2D Icon40(40.0f, 40.0f);

TSharedRef<class FSlateStyleSet> KeeaEditorStyle::Create()
{
	//스타일 인스턴스 생성
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet("MyEditorStyle"));

	//이미지를 로드할 경로 정의(경로가 틀리면 OutputLog에 로드 실패 경고가 출력된다.)
	Style->SetContentRoot(FPaths::GameSourceDir() / TEXT("KeeaModule/Resources"));

	//아이콘 이미지 파일 로드
	Style->Set("Monster_icon_64", new IMAGE_BRUSH(TEXT("Monster_icon_64"), Icon40));
	Style->Set("Adventure_Map_icon_64", new IMAGE_BRUSH(TEXT("Adventure_Map_icon_64"), Icon40));
	Style->Set("Bomb_icon_64", new IMAGE_BRUSH(TEXT("Bomb_icon_64"), Icon40));

	return Style;
}
#undef IMAGE_BRUSH

//텍스쳐를 리로드
void KeeaEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized() && FSlateApplication::Get().GetRenderer()) {
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle & KeeaEditorStyle::Get()
{
	return *StyleInstance;
}


