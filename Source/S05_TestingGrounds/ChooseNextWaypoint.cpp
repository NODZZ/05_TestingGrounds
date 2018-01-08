// Copyright Thomas Corlett 2018

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Classes/AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get blackboard component
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	// Get patrol points
	if (!ensure(OwnerComp.GetAIOwner()->GetPawn())) { return EBTNodeResult::Failed; }
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>(); // Search through pawn for component
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Set next Waypoint
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (!ensure(BlackBoardComp)) { return EBTNodeResult::Failed; }
	if (!ensure(PatrolPoints.Num() > 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points")) // Handle empty patrol points array
			return EBTNodeResult::Failed;
	}
	int Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackBoardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}


