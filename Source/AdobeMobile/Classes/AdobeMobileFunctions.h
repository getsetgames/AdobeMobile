//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#pragma once

#include "AdobeMobileFunctions.generated.h"


UCLASS(NotBlueprintable)
class UAdobeMobileFunctions : public UObject {
	GENERATED_BODY()
	
public:
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "adobe mobile advertising"), Category = "AdobeMobile")
    static void AdobeMobileTrackState(FString state, TArray<FString> dataKeys, TArray<FString> dataValues);
    
    UFUNCTION(BlueprintCallable, meta = (Keywords = "adobe mobile advertising"), Category = "AdobeMobile")
    static void AdobeMobileTrackAction(FString state, TArray<FString> dataKeys, TArray<FString> dataValues);
};
