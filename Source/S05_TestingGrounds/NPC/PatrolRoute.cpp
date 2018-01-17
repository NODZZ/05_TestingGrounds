// Copyright Thomas Corlett 2018

#include "PatrolRoute.h"

UPatrolRoute::UPatrolRoute()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<AActor*> UPatrolRoute::GetPatrolPoints() const
{
	return PatrolPoints;
}