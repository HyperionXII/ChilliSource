//
// FacebookAuthenticationSystem.h
// Chilli Source
//
// Created by Robert Henning on 03/05/2012
// Copyright 2012 Tag Games Limited - All rights reserved
//

#ifndef _CHILLISOURCE_BACKEND_PLATFORM_ANDROID_SOCIAL_FACEBOOKAUTHENTICATIONSYSTEM_H_
#define _CHILLISOURCE_BACKEND_PLATFORM_ANDROID_SOCIAL_FACEBOOKAUTHENTICATIONSYSTEM_H_

#include <ChilliSource/Backend/Platform/Android/Social/Facebook/FacebookJavaInterface.h>
#include <ChilliSource/Social/Facebook/FacebookAuthenticationSystem.h>

namespace ChilliSource
{
	namespace Android
	{
		//------------------------------------------------
		/// Class for logging in to Facebook using
		/// the Android Facebook SDK. Also handles
		/// the granting of read and write permissions
		///
		/// @author R Henning
		//------------------------------------------------
		class FacebookAuthenticationSystem final : public Social::FacebookAuthenticationSystem
		{
		public:

			CS_DECLARE_NAMEDTYPE(FacebookAuthenticationSystem);

            //----------------------------------------------------
            /// @author S Downie
            ///
            /// @param Interface ID to compare
            ///
            /// @return Whether the interface ID matches this object
            //----------------------------------------------------
            bool IsA(Core::InterfaceIDType in_interfaceID) const override;
            //----------------------------------------------------
            /// Called when the system is created allocating any
			/// resources
            ///
            /// @author S Downie
            //----------------------------------------------------
            void OnInit() override;
            //------------------------------------------------
            /// Log the user into Facebook with the given
            /// read permissions. If no permissions are specified
            /// then only basic read permissions will be granted
            /// on authentication success
            ///
            /// Only one auth request can be active at any time
            /// otherwise an assert will be triggered
            ///
            /// @author S Downie
            ///
            /// @param Read permissions (http://developers.facebook.com/docs/authentication/permissions/)
            /// @param Result delegate
            //------------------------------------------------
            void Authenticate(const std::vector<std::string>& in_readPermissions, const AuthenticationCompleteDelegate& in_delegate) override;
			//------------------------------------------------
            /// @author S Downie
            ///
            /// @return Whether there is an active session
            //------------------------------------------------
            bool IsSignedIn() const override;
            //------------------------------------------------
            /// Request that the user grant additional read
            /// permissions (http://developers.facebook.com/docs/authentication/permissions/)
            ///
            /// Only one auth request can be active at any time
            /// otherwise an assert will be triggered
            ///
            /// @author S Downie
            ///
            /// @param Read permissions
            /// @param Result delegate
            //------------------------------------------------
            void AuthoriseReadPermissions(const std::vector<std::string>& in_readPermissions, const AuthenticationCompleteDelegate& in_delegate) override;
            //------------------------------------------------
            /// Request that the user grant write
            /// permissions (http://developers.facebook.com/docs/authentication/permissions/)
            ///
            /// Only one auth request can be active at any time
            /// otherwise an assert will be triggered
            ///
            /// @author S Downie
            ///
            /// @param Write permissions
            /// @param Result delegate
            //------------------------------------------------
            void AuthoriseWritePermissions(const std::vector<std::string>& in_writePermissions, const AuthenticationCompleteDelegate& in_delegate) override;
            //------------------------------------------------
            /// @author S Downie
            ///
            /// @param Permission to check
            ///
            /// @return Whether the given permission has been
            /// granted by the user
            //------------------------------------------------
            bool HasPermission(const std::string& in_permission) const override;
            //------------------------------------------------
            /// Log the current user out of Facebook and
            /// close the active session
            ///
            /// @author S Downie
            //------------------------------------------------
            void SignOut() override;
            //----------------------------------------------------
            /// Called when the system is destroyed. This
            /// will close any open sessions
            ///
            /// @author S Downie
            //----------------------------------------------------
            void OnDestroy() override;

            //---Internal functions called by JNI
            //----------------------------------------------------
            /// Called by JNI when authentication completes
            /// either with or without success
            ///
            /// @author R Henning
            ///
            /// @param Success
            //----------------------------------------------------
			void OnAuthenticationComplete(bool in_success);
            //----------------------------------------------------
            /// Called by JNI when read permission authoring completes
            /// either with or without success
            ///
            /// @author R Henning
            ///
            /// @param Success
            //----------------------------------------------------
			void OnAuthoriseReadPermissionsComplete(bool in_success);
            //----------------------------------------------------
            /// Called by JNI when write permission authoring completes
            /// either with or without success
            ///
            /// @author R Henning
            ///
            /// @param Success
            //----------------------------------------------------
			void OnAuthoriseWritePermissionsComplete(bool in_success);

		private:
			friend Social::FacebookAuthenticationSystemUPtr Social::FacebookAuthenticationSystem::Create();
            //----------------------------------------------------
            /// Private constructor to force the use of the
            /// factory method.
            ///
            /// @author I Copland
            //----------------------------------------------------
            FacebookAuthenticationSystem(){}
            //----------------------------------------------------
            /// @author R Henning
            ///
            /// @return Token from active session
            //----------------------------------------------------
            std::string GetActiveToken() const;

		private:

			FacebookJavaInterfaceSPtr m_javaInterface;

			AuthenticationCompleteDelegate m_authDelegate;
			AuthenticationCompleteDelegate m_authReadDelegate;
			AuthenticationCompleteDelegate m_authWriteDelegate;
		};
	}
}

#endif