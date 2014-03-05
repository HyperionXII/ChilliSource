/** 
 * File: Accelerometer.h
 * Date: 15/11/2010
 * Description:
 */

/** 
 *
 * Author: Stuart McGaw 
 * Version: 1.0 - MoFlow
 * Copyright ©2010 Tag Games Limited - All rights reserved 
 */

#ifndef MOFLOW_PLATFORM_IOS_ACCELEROMETER_H
#define MOFLOW_PLATFORM_IOS_ACCELEROMETER_H

#include <ChilliSource/ChilliSource.h>
#include <ChilliSource/Backend/Platform/iOS/ForwardDeclarations.h>
#include <ChilliSource/Core/System/SystemConcepts.h>
#include <ChilliSource/Input/Accelerometer/Accelerometer.h>

@class CMMotionManager;

namespace ChilliSource
{
	namespace iOS
	{
		class Accelerometer : public Input::Accelerometer, public Core::IUpdateable
		{
		public:
			//----------------------------------------------------
			/// Constructor
			//----------------------------------------------------
			Accelerometer();
            //----------------------------------------------------
			/// Is A
			///
			/// @return Whether this object is of given type
			//----------------------------------------------------
            bool IsA(Core::InterfaceIDType inInterfaceID) const override;
            //-------------------------------------------------------
            /// Supported By Device
            ///
            /// This checks whether or not the current iOS device
            /// supports accelerometer. This should always be checked before
            /// creating an instance of the class.
            //-------------------------------------------------------
            static bool SupportedByDevice();
            //----------------------------------------------------
			/// Is Updating
			///
			/// @return whether or not the accelerometer is
            /// currently updating.
			//----------------------------------------------------
			bool IsUpdating() const override;
			//----------------------------------------------------
			/// Start Updating
			///
			/// Start listening for accelerometer changes.
			//----------------------------------------------------
			void StartUpdating() override;
            //----------------------------------------------------
            /// Update
            ///
            /// @param Time since last update
            //----------------------------------------------------
            void Update(f32 infDT) override;
			//----------------------------------------------------
			/// Get Acceleration
			///
			/// @return The acceleration in Gs.
			//----------------------------------------------------
            Core::Vector3 GetAcceleration() const override;
			//----------------------------------------------------
			/// Stop Updating
			///
			/// Stop listening for accelerometer changes.
			//----------------------------------------------------
			void StopUpdating() override;;
			//----------------------------------------------------
			/// Destructor
			//----------------------------------------------------
			~Accelerometer();
		protected:
            
            bool mbIsUpdating;
            
            CMMotionManager* m_motionManager;
		};
	}
}

#endif
