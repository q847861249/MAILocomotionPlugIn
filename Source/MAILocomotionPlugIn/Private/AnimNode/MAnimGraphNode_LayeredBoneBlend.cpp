// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNode/MAnimGraphNode_LayeredBoneBlend.h"
#include "./Anim/UM_AnimInstance.h"

#include "ToolMenus.h"
#include "Kismet2/BlueprintEditorUtils.h"

#include "AnimGraphCommands.h"
#include "ScopedTransaction.h"

#include "DetailLayoutBuilder.h"
#include "Kismet2/CompilerResultsLog.h"
#include "UObject/UE5ReleaseStreamObjectVersion.h"


#define LOCTEXT_NAMESPACE "A3Nodes"


UMAnimGraphNode_LayeredBoneBlend::UMAnimGraphNode_LayeredBoneBlend(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	M_Node.AddPose();
}

void UMAnimGraphNode_LayeredBoneBlend::Serialize(FArchive& Ar)
{
	Super::Super::Serialize(Ar);
	Ar.UsingCustomVersion(FUE5ReleaseStreamObjectVersion::GUID);
	if (Ar.IsLoading() && Ar.CustomVer(FUE5ReleaseStreamObjectVersion::GUID) < FUE5ReleaseStreamObjectVersion::AnimLayeredBoneBlendMasks)
	{
		if (M_Node.BlendMode == ELayeredBoneBlendMode::BlendMask && M_Node.BlendMasks.Num() != M_Node.BlendPoses.Num())
		{
			M_Node.BlendMasks.SetNum(M_Node.BlendPoses.Num());
		}
	}
}

void UMAnimGraphNode_LayeredBoneBlend::PostLoad()
{
	Super::Super::PostLoad();
	// Post-load our blend masks, in case they've been pre-loaded, but haven't had their bone references initialized yet.
	if (M_Node.BlendMode == ELayeredBoneBlendMode::BlendMask)
	{
		int32 NumBlendMasks = M_Node.BlendMasks.Num();
		for (int32 MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			if (UBlendProfile* BlendMask = M_Node.BlendMasks[MaskIndex])
			{
				BlendMask->ConditionalPostLoad();
			}
		}
	}

}

FLinearColor UMAnimGraphNode_LayeredBoneBlend::GetNodeTitleColor() const
{
	return FLinearColor(0.2f, 0.8f, 0.2f);
}

FText UMAnimGraphNode_LayeredBoneBlend::GetTooltipText() const
{
	return LOCTEXT("AnimGraphNode_LayeredBoneBlend_Tooltip", "M_LayeredBlendPerBone");
}

FText UMAnimGraphNode_LayeredBoneBlend::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("AnimGraphNode_LayeredBoneBlend_Title", "M_LayeredBlendPerBone");
}

void UMAnimGraphNode_LayeredBoneBlend::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName PropertyName = (PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None);
	// Reconstruct node to show updates to PinFriendlyNames.
	if (PropertyName == GET_MEMBER_NAME_STRING_CHECKED(FAnimNode_LayeredBoneBlend, BlendMode))
	{
		// If we  change blend modes, we need to resize our containers
		FScopedTransaction Transaction(LOCTEXT("ChangeBlendMode", "Change Blend Mode"));
		Modify();

		const int32 NumPoses = M_Node.BlendPoses.Num();
		if (M_Node.BlendMode == ELayeredBoneBlendMode::BlendMask)
		{
			M_Node.LayerSetup.Reset();
			M_Node.BlendMasks.SetNum(NumPoses);
		}
		else
		{
			M_Node.BlendMasks.Reset();
			M_Node.LayerSetup.SetNum(NumPoses);
		}

		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
	}

	Super::Super::PostEditChangeProperty(PropertyChangedEvent);
	
}

void UMAnimGraphNode_LayeredBoneBlend::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	Super::Super::GetNodeContextMenuActions(Menu, Context);

	if (!Context->bIsDebugging)
	{
		{
			FToolMenuSection& Section = Menu->AddSection("AnimGraphNodeLayeredBoneblend", LOCTEXT("LayeredBoneBlend", "Layered Bone Blend"));
			if (Context->Pin != NULL)
			{
				// we only do this for normal BlendList/BlendList by enum, BlendList by Bool doesn't support add/remove pins
				if (Context->Pin->Direction == EGPD_Input)
				{
					//@TODO: Only offer this option on arrayed pins
					Section.AddMenuEntry(FAnimGraphCommands::Get().RemoveBlendListPin);
				}
			}
			else
			{
				Section.AddMenuEntry(FAnimGraphCommands::Get().AddBlendListPin);
			}
		}
	}
	
}

FString UMAnimGraphNode_LayeredBoneBlend::GetNodeCategory() const
{
	return TEXT("Animation|Blends");
}

void UMAnimGraphNode_LayeredBoneBlend::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	TSharedRef<IPropertyHandle> NodeHandle = DetailBuilder.GetProperty(FName(TEXT("M_Node")), GetClass());

	if (M_Node.BlendMode != ELayeredBoneBlendMode::BranchFilter)
	{
		DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_LayeredBoneBlend, LayerSetup)));
	}

	if (M_Node.BlendMode != ELayeredBoneBlendMode::BlendMask)
	{
		DetailBuilder.HideProperty(NodeHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FAnimNode_LayeredBoneBlend, BlendMasks)));
	}

	Super::Super::CustomizeDetails(DetailBuilder);

}

void UMAnimGraphNode_LayeredBoneBlend::PreloadRequiredAssets()
{

	// Preload our blend profiles in case they haven't been loaded by the skeleton yet.
	if (M_Node.BlendMode == ELayeredBoneBlendMode::BlendMask)
	{
		int32 NumBlendMasks = M_Node.BlendMasks.Num();
		for (int32 MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			UBlendProfile* BlendMask = M_Node.BlendMasks[MaskIndex];
			PreloadObject(BlendMask);
		}
	}

	Super::Super::PreloadRequiredAssets();

}

void UMAnimGraphNode_LayeredBoneBlend::ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog)
{
	
	Super::Super::ValidateAnimNodeDuringCompilation(ForSkeleton, MessageLog);

	bool bCompilationError = false;
	// Validate blend masks
	if (M_Node.BlendMode == ELayeredBoneBlendMode::BlendMask)
	{
		int32 NumBlendMasks = M_Node.BlendMasks.Num();
		for (int32 MaskIndex = 0; MaskIndex < NumBlendMasks; ++MaskIndex)
		{
			const UBlendProfile* BlendMask = M_Node.BlendMasks[MaskIndex];
			if (BlendMask == nullptr && !GetAnimBlueprint()->bIsTemplate)
			{
				MessageLog.Error(*FText::Format(LOCTEXT("LayeredBlendNullMask", "@@ has null BlendMask for Blend Pose {0}. "), FText::AsNumber(MaskIndex)).ToString(), this, BlendMask);
				bCompilationError = true;
			}

			if (BlendMask && BlendMask->Mode != EBlendProfileMode::BlendMask)
			{
				MessageLog.Error(*FText::Format(LOCTEXT("LayeredBlendProfileModeError", "@@ is using a BlendProfile(@@) without a BlendMask mode for Blend Pose {0}. "), FText::AsNumber(MaskIndex)).ToString(), this, BlendMask);
				bCompilationError = true;
			}
		}
	}

	// Don't rebuild the node's data if compilation failed. We may be attempting to do so with invalid data.
	if (bCompilationError)
	{
		return;
	}


}

#undef LOCTEXT_NAMESPACE