#include "pxt.h"
#include "MicroBit.h"

#if MICROBIT_CODAL
#include "StreamRecording.h"
#endif

#include "sounds/sounds.h"

using namespace pxt;

namespace customaudio {

#if MICROBIT_CODAL

/*
 * Die drei Audioquellen liegen direkt im Flash.
 *
 * Die Daten sind:
 *
 *   unsigned 8 bit
 *   mono
 *   8000 Hz
 *
 * 128 = ungefähr Stille.
 */

static bool audioStarted = false;

static void initAudio()
{
    if (audioStarted)
        return;

    audioStarted = true;

    MicroBitAudio::requestActivation();
}

/*
 * Diese Funktion benutzt die MakeCode/CODAL-Audiokette.
 *
 * Die Daten werden in kleinen Blöcken vom Flash gelesen.
 */
static void playPCM(
    const unsigned char *data,
    unsigned int length
)
{
    initAudio();

    /*
     * Für den ersten funktionsfähigen Prototypen
     * werden die Samples blockweise verarbeitet.
     *
     * 8000 Hz / 8 bit / mono
     */
    const unsigned int blockSize = 128;

    unsigned char buffer[blockSize];

    unsigned int position = 0;

    while (position < length)
    {
        unsigned int remaining = length - position;

        unsigned int count =
            remaining < blockSize
                ? remaining
                : blockSize;

        memcpy(
            buffer,
            data + position,
            count
        );

        /*
         * Rest eines letzten Blocks mit Stille auffüllen.
         */
        if (count < blockSize)
        {
            memset(
                buffer + count,
                128,
                blockSize - count
            );
        }

        /*
         * TODO:
         *
         * Hier wird der CODAL-Audio-Output
         * mit dem PCM-Block verbunden.
         *
         * Die genaue Funktion ist abhängig von
         * der verwendeten pxt-microbit/CODAL-Version.
         */

        position += count;

        fiber_sleep(16);
    }
}

#endif


/**
 * Play power-on sound
 */
//% block="play power-on sound"
//% group="Sounds"
//% weight=30
void playPowerOn()
{
#if MICROBIT_CODAL
    playPCM(
        audio_power_on,
        audio_power_on_length
    );
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}


/**
 * Play alarm sound
 */
//% block="play alarm sound"
//% group="Sounds"
//% weight=20
void playAlarm()
{
#if MICROBIT_CODAL
    playPCM(
        audio_alarm,
        audio_alarm_length
    );
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}


/**
 * Play anti-stalking sound
 */
//% block="play anti-stalking sound"
//% group="Sounds"
//% weight=10
void playAntiStalking()
{
#if MICROBIT_CODAL
    playPCM(
        audio_anti_stalking,
        audio_anti_stalking_length
    );
#else
    target_panic(PANIC_VARIANT_NOT_SUPPORTED);
#endif
}

} // namespace customaudio
