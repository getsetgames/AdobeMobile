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
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Offline Tracking"))
    bool OfflineTracking;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Lifecycle Timeout"))
    uint32 LifecycleTimeout;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="App Name"))
    FString AppName;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Tracking Report Suite ID (RSID) - Development"))
    FString TrackingRSIDDevelopment;
   
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Tracking Report Suite ID (RSID) - Shipping"))
    FString TrackingRSIDShipping;
    
    UPROPERTY(Config, EditAnywhere, Category=General, meta=(DisplayName="Tracking Server"))
    FString TrackingServer;
};
