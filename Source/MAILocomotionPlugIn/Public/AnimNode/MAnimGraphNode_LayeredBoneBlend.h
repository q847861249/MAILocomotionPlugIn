// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_LayeredBoneBlend.h"

#include"./M_LayeredBoneBlend.h"

#include "MAnimGraphNode_LayeredBoneBlend.generated.h"

/**
 * 
 */
UCLASS()
class MAILOCOMOTIONPLUGIN_API UMAnimGraphNode_LayeredBoneBlend : public UAnimGraphNode_LayeredBoneBlend
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(EditAnywhere, Category = Settings)
	FUM_LayeredBoneBlend M_Node;

	// UObject interface
	void Serialize(FArchive& Ar) override;
	virtual void PostLoad() override;
	// End of UObject interface

	// UEdGraphNode interface
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UEdGraphNode interface

	// UK2Node interface
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	// End of UK2Node interface

	// UAnimGraphNode_Base interface
	virtual FString GetNodeCategory() const override;
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
	virtual void PreloadRequiredAssets() override;
	// End of UAnimGraphNode_Base interface
	virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;

};
