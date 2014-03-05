/*
 *  RenderTarget.h
 *  moFlo
 *
 *  Created by Scott Downie on 05/10/2010.
 *  Copyright 2010 Tag Games. All rights reserved.
 *
 */

#ifndef _MO_FLO_RENDERING_RENDER_TARGET_H_
#define _MO_FLO_RENDERING_RENDER_TARGET_H_

#include <ChilliSource/ChilliSource.h>

namespace ChilliSource
{
	namespace Rendering
	{
		//=====================================================
		/// Description:
		///
		/// Abstract render target. Contains data about a 
		/// render target.
		//=====================================================
		class RenderTarget
		{
		public:
			RenderTarget(){}
			virtual ~RenderTarget(){}
			
            //------------------------------------------------------
            /// Set Target Textures
            ///
            /// Sets the textures which will be rendered into. If the
            /// depth texture is nullptr a depth buffer will be
            /// created. If the colour texture is nullptr only the
            /// depth texture will be attached.
            ///
            /// @param The colour texture.
            /// @param The depth texture.
            //------------------------------------------------------
			virtual void SetTargetTextures(const TextureSPtr& inpColourTexture, const TextureSPtr& inpDepthTexture) = 0;
            //------------------------------------------------------
            /// Bind
            ///
            /// Bind the frame buffer to the context
            //------------------------------------------------------
			virtual void Bind() = 0;
            //------------------------------------------------------
            /// Discard
            ///
            /// Discard the frame buffer contents
            //------------------------------------------------------
			virtual void Discard() = 0;
            //------------------------------------------------------
            /// Get Width
            ///
            /// @return Width of render target
            //------------------------------------------------------
			inline u32 GetWidth() const {return mudwWidth;}
            //------------------------------------------------------
            /// Get Height
            ///
            /// @return Height of render target
            //------------------------------------------------------
			inline u32 GetHeight() const {return mudwHeight;}
            //------------------------------------------------------
            /// Destroy
            ///
            /// Release the buffers
            //------------------------------------------------------
			virtual void Destroy() = 0;
			
		protected:
			u32 mudwWidth;
			u32 mudwHeight;
		};
	}
}

#endif
