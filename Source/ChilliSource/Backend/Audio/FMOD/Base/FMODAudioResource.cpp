/*
 * File: FMODSoundEffect.cpp
 * Date: 16/11/2010 2010 
 * Description: 
 */

/*
 * Author: Scott Downie
 * Version: v 1.0
 * Copyright ©2010 Tag Games Limited - All rights reserved 
 */

#include <ChilliSource/Backend/Audio/FMOD/Base/FMODAudioResource.h>
#include <ChilliSource/Backend/Audio/FMOD/Base/FMODSystem.h>

namespace ChilliSource
{
	namespace iOS
	{
		//-------------------------------------------------
		/// Constructor
		//-------------------------------------------------
		CFMODAudioResource::CFMODAudioResource() : mpFMODSound(nullptr)
		{
            Audio::IAudioResource::SetStreamed(false);
		}
        //-------------------------------------------------
        /// Is A
        //-------------------------------------------------
        bool CFMODAudioResource::IsA(ChilliSource::Core::InterfaceIDType inInterfaceID) const
        {
            return (inInterfaceID == Audio::IAudioResource::InterfaceID);
        }
		//--------------------------------------------------
		/// Get Length
		//--------------------------------------------------
		f32 CFMODAudioResource::GetLength()
		{
            u32 udwLengthInMs = 0;
            
            if (mpFMODSound != nullptr)
            {
                mpFMODSound->getLength(&udwLengthInMs, FMOD_TIMEUNIT_MS);
            }
            
			f32 fLengthInSecs = udwLengthInMs * 0.001f;
			return fLengthInSecs;
		}
        //--------------------------------------------------
        /// Set Looping
        //--------------------------------------------------
        void CFMODAudioResource::SetLooping(bool inbShouldLoop)
        {
            if (mpFMODSound != nullptr)
            {
                inbShouldLoop ? mpFMODSound->setMode(FMOD_LOOP_NORMAL) : mpFMODSound->setMode(FMOD_LOOP_OFF);
            }
        }
		//--------------------------------------------------
		/// Destructor
		//--------------------------------------------------
		CFMODAudioResource::~CFMODAudioResource()
		{
            if (mpFMODSound != nullptr)
            {
                mpFMODSound->release();
            }
		}
	}
}