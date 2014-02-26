/*
 *  FacebookPostSystem.h
 *  moFlo
 *
 *  Created by Stuart McGaw on 06/06/2011.
 *  Copyright 2011 Tag Games. All rights reserved.
 *
 */

#ifndef _MOFLO_PLATFORM_IOS_SOCIAL_FACEBOOK_FACEBOOKPOSTSYSTEM_H_
#define _MOFLO_PLATFORM_IOS_SOCIAL_FACEBOOK_FACEBOOKPOSTSYSTEM_H_

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Social/Facebook/FacebookPostSystem.h>
#include <ChilliSource/Social/Facebook/FacebookAuthentication.h>

namespace ChilliSource
{
	namespace iOS
	{
		class CFacebookPostSystem : public Social::IFacebookPostSystem
		{
		public:
			CFacebookPostSystem(Social::FacebookAuthenticationSystem* inpAuthSystem);
			
            bool IsA(Core::InterfaceIDType inID) const override;
			
            void TryPost(const Social::FacebookPostDesc& insDesc, const PostResultDelegate& insResultCallback) override;
            
            void TrySendRequest(const Social::FacebookPostDesc& insDesc, const PostResultDelegate& insResultCallback, std::vector<std::string>& inastrRecommendedFriends) override;
			
		private:
            void Post(const Social::FacebookPostDesc& insDesc);
            bool TryPostNative(const Social::FacebookPostDesc& insDesc);
            void PostWebBased(const Social::FacebookPostDesc& insDesc);
            void OnPublishPermissionAuthorised(const Social::FacebookAuthenticationSystem::AuthenticateResponse& insResponse);
			
            Social::FacebookAuthenticationSystem* mpAuthSystem;
            Social::FacebookPostDesc msPostDesc;
		};
	}
}

#endif
