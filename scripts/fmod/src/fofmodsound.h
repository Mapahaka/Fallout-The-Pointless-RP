#ifndef __FOFMOD_SOUND_H__
#define __FOFMOD_SOUND_H__


#include "fofmoddef.h"
#include "refcount.h"
#include "cachedata.h"

namespace FOFMOD
{
	class System;
	
	class CacheSoundData;
	typedef std::map< std::string, CacheSoundData* > CachedDataMap;
	
	class Sound : public IRefcountable
	{
		protected:
			Sound(); // ban
			FOFMOD::System* system;
			unsigned int refcount;
			FMOD::Sound*   handle;

		public:
			FOFMOD::CacheSoundData* cacheData;
			Sound( FOFMOD::System* system );
			~Sound();
			bool IsValid();
			void Addref() override;
			void Release() override;
			unsigned int GetRefcount() override;
			void SetCache( FOFMOD::CacheSoundData* cdata );
			void SetHandle( FMOD::Sound* snd );
			void GetHandle( FMOD::Sound** ptr );
			unsigned int GetLength();
			void SetLoopCount( int loopCount );
			int GetLoopCount();
			
			void Invalidate();

	};

	
};

#endif // __FOFMOD_SOUND_H__