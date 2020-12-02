#include "..\Public\TrapEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Interfaces/IMainFrameModule.h"

const FName FTrapEditor::IGCEditorAppIdentifier = FName(TEXT("TrapEditorApp"));
const FName FTrapEditor::ViewportTabId = FName(TEXT("IGC Viewport"));
const FName FTrapEditor::DetailTabId = FName(TEXT("IGC Detail"));

#define LOCTEXT_NAMESPACE "TrapEditor"

FTrapEditor::~FTrapEditor()
{

}

void FTrapEditor::InitTrapEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject * InIGC)
{
	// 툴바가 들어갈 기본 레이아웃 설계.

	const TSharedRef<FTabManager::FLayout> EditorDefaultLayout = FTabManager::NewLayout("IGCEditor_Layout_v2")
		->AddArea
		(
			/*FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
			->Split
			(*/
				FTabManager::NewPrimaryArea()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6)
					->AddTab(ViewportTabId, ETabState::OpenedTab)->SetHideTabWell(true)
					->AddTab(DetailTabId, ETabState::ClosedTab)
				)
				/*->Split
				(
					FTabManager::NewStack()
					->AddTab(DetailTabId, ETabState::OpenedTab)
				)*/
			//)
		);

	// 에디터 초기화.
	const bool bCreateDefaultStandaloneMenu = false;
	const bool bCreateDefaultToolbar = false;

	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, IGCEditorAppIdentifier, EditorDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InIGC);
}

void FTrapEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_IGCAssetEditor", "IGC Asset Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);

	TabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FTrapEditor::SpawnTab_Viewport))
		.SetGroup(WorkspaceMenuCategoryRef);

	TabManager->RegisterTabSpawner(DetailTabId, FOnSpawnTab::CreateSP(this, &FTrapEditor::SpawnTab_Detail))
		.SetGroup(WorkspaceMenuCategoryRef);
}

void FTrapEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);

	TabManager->UnregisterTabSpawner(ViewportTabId);
	TabManager->UnregisterTabSpawner(DetailTabId);
}

FName FTrapEditor::GetToolkitFName() const
{
	return FName("Trap Editor");
}

FText FTrapEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Trap Editor");;
}

FString FTrapEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Trap ").ToString();
}

FLinearColor FTrapEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.0f, 0.0f, 0.2f, 0.5f);
}
TSharedRef<SDockTab> FTrapEditor::SpawnTab_Viewport(const FSpawnTabArgs & Args)
{
	check(Args.GetTabId() == ViewportTabId);
	return SNew(SDockTab);
}
TSharedRef<SDockTab> FTrapEditor::SpawnTab_Detail(const FSpawnTabArgs & Args)
{
	check(Args.GetTabId() == DetailTabId);
	return SNew(SDockTab);
}
#undef LOCTEXT_NAMESPACE 