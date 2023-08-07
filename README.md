Chocolate SoLoud
======
ChocolateSoloud aims to be a easy to use and flexible audio engine for games.

It is a friendly (aka hopefully merged back into) fork of jarikomppa's Soloud library with
some moderizations and tweaks. The forcing factor for this fork has been to unlock stuff required for my
own product but would like to keep with the spirit of open source :)

Features include
* Pipewire Support
* Library callbacks for custom loading/allocation systems
* Removal of old backends
* Modernized C++ standards (C++ 2020 refactoring)

Roadmap
* Resonance ambisonics/hrft (80% of the way there)
* Remove existing limitations on voice count
* Use stronger typing for easier error detection
* Logger callbacks
* memory tracker
* More preset filters (eg. pitch, ect)
