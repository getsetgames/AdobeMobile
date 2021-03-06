//
//  Created by Robert Segal on 2016-03-31.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "AdobeMobileSettings.h"
#include "AdobeMobilePrivatePCH.h"

UAdobeMobileSettings::UAdobeMobileSettings(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, OfflineTracking(false)
, LifecycleTimeout(900)
, AppName("")
, TrackingRSIDDevelopment("")
, TrackingRSIDShipping("")
, TrackingServer("")
{
}
