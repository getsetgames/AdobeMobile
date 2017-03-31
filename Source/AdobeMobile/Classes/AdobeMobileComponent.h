//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "Components/ActorComponent.h"
#include "AdobeMobileFunctions.h"
#include "AdobeMobileComponent.generated.h"

UCLASS(ClassGroup=Advertising, HideCategories=(Activation, "Components|Activation", Collision), meta=(BlueprintSpawnableComponent))
class UAdobeMobileComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:

	
	void OnRegister() override;
	void OnUnregister() override;
	
private:	
	
};
