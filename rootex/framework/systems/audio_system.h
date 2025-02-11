#pragma once

#include "common/common.h"

#include "components/space/transform_component.h"
#include "components/audio/audio_listener_component.h"

#include "al.h"
#include "alc.h"
#include "alut.h"

#include "system.h"

#ifndef ALUT_CHECK
#ifdef _DEBUG
#define ALUT_CHECK(alutFunction)                                        \
	do                                                                  \
	{                                                                   \
		alutFunction;                                                   \
		AudioSystem::CheckALUTError(#alutFunction, __FILE__, __LINE__); \
	} while (0)
#else
#define ALUT_CHECK(alutFunction) alutFunction
#endif
#endif

#ifndef AL_CHECK
#ifdef _DEBUG
#define AL_CHECK(alFunction)                                        \
	do                                                              \
	{                                                               \
		alFunction;                                                 \
		AudioSystem::CheckALError(#alFunction, __FILE__, __LINE__); \
	} while (0)
#else
#define AL_CHECK(alFunction) alFunction
#endif
#endif

class AudioBuffer;
class StaticAudioBuffer;
class StreamingAudioBuffer;

class AudioSource;
class StreamingAudioSource;

class ResourceFile;

/// Audio System responsible for streaming and static audio
class AudioSystem : public System
{
	ALCdevice* m_Device = nullptr;
	ALCcontext* m_Context = nullptr;

	AudioListenerComponent* m_Listener = nullptr;

	AudioSystem();
	AudioSystem(AudioSystem&) = delete;

public:
	static AudioSystem* GetSingleton();

	/// Returns error string corresponding to AL error codes.
	static String GetALErrorString(int errID);
	/// Returns error string corresponding to ALC error codes.
	static String GetALCErrorString(int errID);
	/// Wrapper over alGetError function.
	static void CheckALError(const char* msg, const char* fname, int line);
	/// Wrapper over alcGetError function.
	static void CheckALCError(const char* msg, const char* fname, int line);
	/// Wrapper over alutGetError function.
	static void CheckALUTError(const char* msg, const char* fname, int line);

	AudioListenerComponent* getListener() const { return m_Listener; }
	void setListener(AudioListenerComponent* listenerComponent);

	void restoreListener();

	bool initialize(const JSON::json& systemData) override;
	void setConfig(const SceneSettings& sceneSettings) override;
	void shutDown();

	void update(float deltaMilliseconds) override;
	void begin() override;
	void end() override;
};
