#pragma once
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>
#include "draw.hpp"

typedef unsigned short uint2_t;
typedef unsigned int uint4_t;
typedef std::vector< ALuint > audio_v;

class SoundSystem {
public:
    SoundSystem();
    ~SoundSystem();
    int load( const char * filename);
    void set_volume( const uint4_t handle, const uint2_t volume );
    void play( const uint4_t handle, bool loop );
    void pause( const uint4_t handle );
    void stop( const uint4_t handle );
private:
    ALboolean enumeration;
    ALCcontext * context;
    ALCdevice * device;
    audio_v audio_source;
};