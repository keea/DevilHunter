#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"

class FTrapEditor : public FAssetEditorToolkit {
public:
	//소멸자
	virtual ~FTrapEditor();

	//초기화 함수
	void InitTrapEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UObject* InIGC);

	// IToolkit에서 상속받아 구현해야 할 가상함수들.
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetDocumentationLink() const override
	{
		return TEXT("NotAvailable");
	}

private:
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Detail(const FSpawnTabArgs& Args);

private:
	// IGC 에디터가 사용할 고유한 앱의 명칭.
	static const FName IGCEditorAppIdentifier;

	//각 Tab이 사용할 고유 명칭
	static const FName ViewportTabId;
	static const FName DetailTabId;
};