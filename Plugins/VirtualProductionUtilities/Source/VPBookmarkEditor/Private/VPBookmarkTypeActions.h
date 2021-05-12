// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Bookmarks/IBookmarkTypeActions.h"
#include "VPBookmark.h"

class AActor;
class FEditorViewportClient;
class UBookmarkBase;
struct FBookmarkBaseJumpToSettings;

DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkActivated, UVPBookmark*);
DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkDeactivated, UVPBookmark*);

/** IBookmarkTypeActions
* Actions that can be applied to or completed with bookmarks.
* Must be registered, see IBookmarkTypeTools.
*/

class FVPBookmarkTypeActions : public IBookmarkTypeActions
{
private:
	TWeakObjectPtr<UVPBookmark> LastActiveBookmark;

public:
	FVPBookmarkActivated OnBookmarkActivated;
	FVPBookmarkDeactivated OnBookmarkDeactivated;

private:
	void ActivateBookmark(UVPBookmark* Bookmark, FEditorViewportClient& Client);
	void DeactivateBookmark(UVPBookmark* Bookmark, FEditorViewportClient& Client);

public:
	/**
	* Gets the class of bookmarks with which these actions can be used.
	* Must match exactly with the desired bookmark class.
	*/
	virtual TSubclassOf<UBookmarkBase> GetBookmarkClass() override;

	/**
	* Called to initialize the given bookmark from the given Viewport.
	*
	* @param InBookmark		The bookmark to initialize.
	* @param InViewportClient	The client that can be used for initialization.
	*/
	virtual void InitFromViewport(UBookmarkBase* InBookmark, FEditorViewportClient& InViewportClient) override;

	/**
	* Called to jump to the given bookmark.
	*
	* @param InBookmark		The bookmark that should be jumped to / activated.
	* @param InSettings		Optional settings, dependent on the bookmark class.
	* @param InViewportClient	The viewport that will be updated.
	*/
	virtual void JumpToBookmark(UBookmarkBase* Bookmark, const TSharedPtr<FBookmarkBaseJumpToSettings> InSettings, FEditorViewportClient& InViewportClient) override;

	static AActor* SpawnBookmark(FEditorViewportClient& InViewportClient, const TSubclassOf<AActor> InActorClass, const FVPBookmarkCreationContext& InCreationContext, const FVector& InOffset, const bool bInFlattenRotation);
};