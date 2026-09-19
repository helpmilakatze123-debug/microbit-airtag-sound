namespace customaudio {

    /**
     * Play the power-on sound.
     */
    //% block="play power-on sound"
    //% weight=30
    export function playPowerOn(): void {
        basic.pause(1)
    }

    /**
     * Play the alarm sound.
     */
    //% block="play alarm sound"
    //% weight=20
    export function playAlarm(): void {
        basic.pause(1)
    }

    /**
     * Play the anti-stalking sound.
     */
    //% block="play anti-stalking sound"
    //% weight=10
    export function playAntiStalking(): void {
        basic.pause(1)
    }

}
