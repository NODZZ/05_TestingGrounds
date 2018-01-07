// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrollingGuard.h" // TODO Remove Coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get blackboard component
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	// Get patrol points
	if (!ensure(OwnerComp.GetAIOwner()->GetPawn())) { return EBTNodeResult::Failed; }
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());

	if (!ensure(PatrollingGuard)) { return EBTNodeResult::Failed; }
	TArray<AActor*> PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	// Set next Waypoint
	if (!ensure(BlackBoardComp)) { return EBTNodeResult::Failed; }
	if (!ensure(PatrolPoints.Num() > 0)) { return EBTNodeResult::Failed; } // Handle empty patrol points array
	int Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}


