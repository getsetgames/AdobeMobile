//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "AdobeMobileSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class UAdobeMobileSettings : public UObject
{
	GENERATED_BODY()
	
public:
	UAdobeMobileSettings(const FObjectInitializer& ObjectInitializer);
};
