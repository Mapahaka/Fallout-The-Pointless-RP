#ifndef __FOFMOD_CHANNEL__
#define __FOFMOD_CHANNEL__

// TODO
#include "fofmodchannel.h"
#include "fofmodchannelAS.h"
#include "stddef.h"
#include "_defines.fos"
#include "fonline.h"
#include "macros.h"

namespace FOFMOD
{
	
	CoreChannelRefcounter::CoreChannelRefcounter(){}//ban
	
	CoreChannelRefcounter::CoreChannelRefcounter( FOFMOD::Channel* subject ) 
	: AAuxiliaryRefcounter < FOFMOD::Channel > ( subject )
	{
	
	}
	
	CoreChannelRefcounter::~CoreChannelRefcounter()
	{
		
	}
	
	void CoreChannelRefcounter::OnZero()
	{
		FOFMOD::Channel* subject = this->subject;
		if( subject )
		{
			if ( !subject->GetRefcount() )
			{
				delete subject;
				FOFMOD_DEBUG_LOG( "core channel release delete \n" );
			}
			
		}
	}
	
	Channel::Channel(){} // ban
	
	Channel::Channel( FOFMOD::System* system )
	{
		this->refcount = 0;
		this->handle = NULL;
		this->sound = NULL;
		this->system = system;
		this->coreRefcounter   = new CoreChannelRefcounter( this );
		this->scriptRefcounter = new ScriptChannelRefcounter( this );
	}
	
	Channel::~Channel()
	{
		this->SetSound( NULL );
		delete( this->coreRefcounter );
		delete( this->scriptRefcounter );
	}
	
	void Channel::Addref()
	{
		this->coreRefcounter->Addref();
	}

	void Channel::Release()
	{
		this->coreRefcounter->Release();
	}
	
	unsigned int Channel::GetRefcount()
	{
		unsigned int result = ( this->coreRefcounter->GetRefcount() ) + ( this->scriptRefcounter->GetRefcount() ) ;
		return result;
	}
	
	void Channel::SetHandle( FMOD::Channel* chn )
	{
		if( chn )
		{
			if( this->handle )
			{
				if( this->handle == chn )
				{
					return;
				}
			}
			
			this->handle = chn;
		}
		else
		{
			if( this->handle )
			{
				this->Invalidate();
			}
		}
	}
	
	void Channel::GetHandle( FMOD::Channel** chn )
	{
		*chn = this->handle;
	}

	void Channel::SetSound( FOFMOD::Sound* snd )
	{
		if( snd )
		{
			if( this->sound )
			{
				if( this->sound == snd )
				{
					return;
				}
				else
				{
					this->sound->Release();
					
				}
			}
			
			this->sound = snd;
			snd->Addref();
			
		}
		else
		{
			if( this->sound )
			{
				this->sound->Release();
				this->sound = NULL;
			}
		}
	}
	


	void Channel::SetPlaybackPosition( unsigned int positionMs )
	{
		if( this->handle )
		{
			this->handle->setPosition( positionMs, FMOD_TIMEUNIT_MS );
		}
	}

	void Channel::GetPlaybackPosition( unsigned int* value )
	{
		if( this->handle )
		{
			this->handle->getPosition( value, FMOD_TIMEUNIT_MS );
		}
	}

	void Channel::GetSound( FOFMOD::Sound** value )
	{
		if( this->sound )
		{
			*value = this->sound;
			(*value)->Addref();
		}
	}

	void Channel::GetPitch( float* value )
	{
		if( this->handle )
		{
			this->handle->getPitch( value );
		}
	}

	void Channel::SetPitch(float pitch)
	{
		if( this->handle )
		{
			this->handle->setPitch( pitch );
		}
	}

	void Channel::IsValid( bool* value )
	{
		// fmod docs say the handle will be invalidated by the system when its done, but it does not define what is "invalidation", assuming NULL;
		*value = ( this->handle != NULL ); 
	}


	void Channel::SetPaused( bool paused )
	{
		if( this->handle )
		{
			this->handle->setPaused( paused );
		}
	}

	void Channel::IsPaused( bool* value )
	{
		if( this->handle )
		{
			this->handle->getPaused( value );
		}
	}

	void Channel::Stop()
	{
		if( this->handle )
		{
			this->handle->stop();
		//	this->handle = NULL;   // making sure ? 
		}
	}


	void Channel::IsPlaying( bool* value )
	{
		if( this->handle )
		{
			this->handle->isPlaying( value );
		}
	}
	
	void Channel::GetPriority( int* value )
	{
		if( this->handle )
		{
			this->handle->getPriority( value );
		}
	}
	
	void Channel::SetPriority( int value )
	{
		if( this->handle )
		{
			this->handle->setPriority( value );
		}
	}
	
	void Channel::SetEffect( int effectType, float* params, unsigned int paramsSize, bool condition )
	{
		if( condition )
		{
			
		}
	}
	
	void Channel::SetFrequency( float hertz )
	{
		if( this->handle )
		{
			this->handle->setFrequency( hertz );
		}
	}
	
	void Channel::GetFrequency( float* value )
	{
		if( this->handle )
		{
			this->handle->getFrequency( value );
		}
	}
	
	void Channel::SetVolumeRamp( bool condition )
	{
		if( this->handle )
		{
			this->handle->setVolumeRamp( condition );
		}
	}
	
	void Channel::GetVolumeRamp( bool* value )
	{
		if( this->handle )
		{
			this->handle->getVolumeRamp( value );
		}
	}
	
	void Channel::SetVolume( float volume )
	{
		if( this->handle )
		{
			this->handle->setVolume( volume );
		}
	}

	void Channel::GetVolume( float* value )
	{
		if( this->handle )
		{
			this->handle->getVolume( value );
		}
	}


	void Channel::Set3DPosition( float x, float y, float z )
	{
		if( this->handle )
		{
			FMOD_VECTOR vec = {x, y, z};
			this->handle->set3DAttributes( &vec , NULL );
		}
	}

	void Channel::Set3DVelocity( float x, float y, float z )
	{
		if( this->handle )
		{
			FMOD_VECTOR vec = {x, y, z};
			this->handle->set3DAttributes( NULL, &vec );
		}
	}

	void Channel::GetLoopCount( int* value )
	{
		if( this->handle )
		{
			this->handle->getLoopCount( value );
		}
	}
	void Channel::SetLoopCount( int count )
	{
		if( this->handle )
		{
			this->handle->setLoopCount( count );
		}
	}

	void Channel::SetLoopPoints( unsigned int loopStart, unsigned int loopStartType, unsigned int loopEnd, unsigned int loopEndType )
	{
		if( this->handle )
		{
			this->handle->setLoopPoints( loopStart, loopStartType, loopEnd, loopEndType );
		}
	}

	void Channel::GetLoopPoints( unsigned int* loopStart, unsigned int loopStartType, unsigned int* loopEnd, unsigned int loopEndType )
	{
		if( this->handle )
		{
			this->handle->getLoopPoints( loopStart, loopStartType, loopEnd, loopEndType );
		}
	}

	void Channel::Set3DMinMaxDistance( float minDistance, float maxDistance )
	{
		if( this->handle )
		{
			this->handle->set3DMinMaxDistance( minDistance, maxDistance );
		}
	}

	void Channel::Get3DMinMaxDistance( float* minDistance, float* maxDistance )
	{
		if( this->handle )
		{
			this->handle->get3DMinMaxDistance( minDistance, maxDistance );
		}
	}

	void Channel::Set3DLevel( float level )
	{
		if( this->handle )
		{
			this->handle->set3DLevel( level );
		}
	}

	void Channel::Get3DLevel( float* value )
	{
		if( this->handle )
		{
			this->handle->get3DLevel( value );
		}
	}

	
	FOFMOD::System* Channel::GetSystem()
	{
		return this->system;
	}
	
	void Channel::Invalidate()
	{
		this->handle = NULL;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
}

#endif // __FOFMOD_CHANNEL__