// Copyright Epic Games, Inc. All Rights Reserved.

#include "VPBookmarkEditorModule.h"
#include "VPBookmarkTypeActions.h"
#include "Modules/ModuleManager.h"

#include "Bookmarks/IBookmarkTypeTools.h"


DEFINE_LOG_CATEGORY(LogVPBookmarkEditor);


void FVPBookmarkEditorModule::StartupModule()
{
	BookmarkTypeActions = MakeShared<FVPBookmarkTypeActions>();

	/** virtual void RegisterBookmarkTypeActions(const TSharedRef<class IBookmarkTypeActions>& InActions) = 0;
	* Registers the given Bookmark Type Actions so they can be used by the editor.
	*
	* @param InActions			The Actions to register.		
	*/
	IBookmarkTypeTools::Get().RegisterBookmarkTypeActions(BookmarkTypeActions.ToSharedRef());
}


void FVPBookmarkEditorModule::ShutdownModule()
{
	/** virtual void UnregisterBookmarkTypeActions(const TSharedRef<class IBookmarkTypeActions>& InActions) = 0;
	* Unregisters the given Bookmark Type Actions so they are no longer considered by the editor.
	*
	* @param InActions			The Actions to unregister.		
	*/
	IBookmarkTypeTools::Get().UnregisterBookmarkTypeActions(BookmarkTypeActions.ToSharedRef());
	BookmarkTypeActions.Reset();
}


IMPLEMENT_MODULE(FVPBookmarkEditorModule, VPBookmarkEditor)
