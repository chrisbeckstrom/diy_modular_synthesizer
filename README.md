# CB's DIY Modular Synthesizer

## About this project

My admittedly lofty goal was to build a modular synthesizer, from scratch, using basic components (no kits), with zero electronics experience. Turns out, it’s possible! I'm sharing circuits, designs, pictures, and code here to help other folks realize their dream of building a modular synthesizer for themselves.

Read more here: <http://chrisbeckstrom.com/main/the-modular>

Follow on Facebook for more: <https://www.facebook.com/chrisbeckstrom>

## About the circuits

I know very little about how these circuits actually work– 99% of the circuits come from the internet, especially the following places:
– electro-music.com DIY forum <http://electro-music.com/forum/index.php?f=112>  
- electr-music.com Lunetta forum <http://electro-music.com/forum/forum-160.html>  
- Nicholas Collins' "Handmade Electronic Music" (2006)
- Fun with Seamoss <http://www.milkcrate.com.au/_other/sea-moss/>   
– Hackaday Logic Noise series <http://hackaday.com/tag/logic-noise/>  
- Ken Stone's Modular Synth site <http://www.cgs.synth.net/modules/>  
- Yu Synth DIY <http://yusynth.net/index_en.php>  

Thanks to all those folks for sharing their designs! Please don't look at my circuits, go see the originals. Those folks know what they are doing. My circuits are only here for reference, just to show you can build a great-sounding synthesizer with extremely primitive circuits.

## Building these circutis

Don't just build these circuits– breadboard them first! I made many small modifications that may not be reflected in the schematics; also, I barely understand anything about electricity so take everything with a grain of salt. If you know your way around electrical engineering you will probably see about a million things I've done incorrectly. That said, my synthesizer works and sounds awesome, and I haven't blown anything up (except for a handful of ICs, resistors, LEDs, pots, transistors, and other components).

## Code

Included in this repository is some code for various things, mostly my arduino modules. I am still learning how to code for arduino, so just as my circuits are rough, so is this code! Proceed with caution. For more info and specifics about what the code does, check out the code itself; I try to include as many helpful comments as possible.

## My synth "format" and construction

Originally I intended to follow the Eurorack format (which I think is ±12V with +5V for digital modules) but I'm not skilled enough (nor did I have the right wall warts) for that. Instead, my synth uses ±9V (from a +20V wall wart) and +5V (from a +6V wall wart). The size is mostly Eurorack (3U tall) and I've built my cases standard rack size widths (19"). My panels are constructed out of 1/8" plywood, mostly oak, and decorated with sharpie markers.  For connectors I use #6 nuts and bolts and connect them with alligator clip patch cables I make using clips and boat trailer wire I get at the grocery store (comes in cool colors). My general focus has been on building basic modules that can be patched to make cool sounds. I also use a lot of LEDs because blinkenlights are awesome.

As of February 2016 I had about 45 modules that included around 15 oscillators (mostly square waves) and lots of ways to manipulate them (filters, logic modules, shift register, sequencer, comparator, dividers, envelopes, LFOs, amps, etc). I haven't counted recently but I have quite a few more now! 

In addition to the DIY modules, there is also a broken-down Korg Monotron Duo I use primarily for the excellent low pass filter and a Korg Volca Keys I separated from its case and shoved into my rack.

## More info

<http://chrisbeckstrom.com/main/the-modular>

**Videos**

<https://www.youtube.com/playlist?list=PLDs-YUeKgExaY1yC73MqwG61ood_hBC3f>
