#include "sound.hpp"

SoundSystem::SoundSystem() {
    const ALfloat listener_ori[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

    device = alcOpenDevice( NULL );
    if ( device == NULL ) {
        game_send_error( alGetString( alGetError() ), EXIT_FAILURE );
    }
    enumeration = alcIsExtensionPresent( NULL, "ALC_ENUMERATION_EXT" );
    if ( enumeration == AL_FALSE ) {
        game_send_error( alGetString( alGetError() ), ERROR_PROBLEM );
    }
    context = alcCreateContext( device, NULL );
    if ( context == NULL ) {
        game_send_error( alGetString( alGetError() ), EXIT_FAILURE );
    }
    alcMakeContextCurrent( context );
    /* openal sound effect configuration */
    alListener3f( AL_POSITION, 0, 0, 1.0f );
    alListener3f( AL_VELOCITY, 0, 0, 0 );
    alListenerfv( AL_ORIENTATION, listener_ori );
    /* openal sound effect configuration */
}

SoundSystem::~SoundSystem() {
    for ( auto & source : audio_source ) {
        alDeleteSources( 1, &source );
    }
    device = alcGetContextsDevice( context );
    alcMakeContextCurrent( NULL );
    alcDestroyContext( context );
    alcCloseDevice( device );
}

int SoundSystem::load( const char * filename ) {
    size_t count = audio_source.size();
    int data_size = 0, size = 0;
    OggVorbis_File ogg_file;
    vorbis_info * info;
    ALuint buffer;
    ALenum format;
    int section;
    FILE * f;

    audio_source.resize( count + 1 );
    auto & source = audio_source[count];
    alGenSources( (ALuint) 1, &( source ) );
    alSourcef( source, AL_PITCH, 1 );
    alSourcef( source, AL_GAIN, 1 );
    alSource3f( source, AL_POSITION, 0, 0, 0 );
    alSource3f( source, AL_VELOCITY, 0, 0, 0 );
    alGenBuffers( (ALuint) 1, &buffer );
    /* load ogg */
    f = fopen( filename, "rb" );
    if ( f == nullptr ) {
        game_send_error( "Can't load sound file", EXIT_FAILURE );
    }
    if ( ov_open( f, &ogg_file, nullptr, 0 ) < 0 ) {
        fclose( f );
        game_send_error( "Ogg load file error", EXIT_FAILURE );
    }
    info = ov_info( &ogg_file, -1 );
    format = info->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    data_size = ov_pcm_total( &ogg_file, -1 ) * info->channels * 2;
    char * raw = new char [data_size];
    while ( size < data_size ) {
        int result = ov_read( &ogg_file, raw + size, data_size - size, 0, 2, 1, &section );
        if ( result > 0 ) {
            size += result;
        } else if ( result < 0 ) {
            delete[] raw;
            game_send_error( "Read data error", EXIT_FAILURE );
        } else {
            break;
        }
    }
    fclose( f );
    /* load ogg */
    alBufferData( buffer, format, raw, data_size, info->rate );
    delete[] raw;
    alSourcei( audio_source[count], AL_BUFFER, buffer );
    alDeleteSources( 1, &buffer );
    return count;
}

void SoundSystem::set_volume( const uint4_t handle, const uint2_t volume ) {
    alSourcef( audio_source[handle], AL_GAIN, (float) volume / 255 );
}

void SoundSystem::play( const uint4_t handle, bool loop ) {
    alSourcei( audio_source[handle], AL_LOOPING, loop ? AL_TRUE : AL_FALSE );
    alSourcePlay( audio_source[handle] );
}

void SoundSystem::pause( const uint4_t handle ) {
    alSourcePause( audio_source[handle] );
}

void SoundSystem::stop( const uint4_t handle ) {
    alSourceStop( audio_source[handle] );
}