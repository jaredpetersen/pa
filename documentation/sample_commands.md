# Sample PA Commands
## General

| PA                   | Linux                                              |
| -------------------- | -------------------------------------------------- |
| `pa whats my ip`     | `ipconfig getifaddr en0 || ipconfig getifaddr en1` |
| `pa what time is it` | `date +"%r"`                                       |
| `pa what day is it`  | `date +"%A, %B %d %Y"`                             |
| `pa shutdown pc`     | `sudo shutdown -h now`                             |
| `pa restart pc`      | `sudo shutdown -r now`                             |
| `pa watch star wars` | `telnet towel.blinkenlights.nl`                    |

## Linux

| PA             | Linux                                         |
| -------------- | --------------------------------------------- |
| `pa update pc` | `sudo apt-get update && sudo apt-get upgrade` |

## Mac OSX

| PA                | Mac OSX                                                               |
| ----------------- | --------------------------------------------------------------------- |
| `pa open browser` | `open http://www.google.com/`                                         |
| `pa open word`    | `open -a "Microsoft Word"`                                            |
| `pa close word`   | `osascript -e 'quit app "Microsoft Word"'`                            |
| `pa open music`   | `open -a iTunes`                                                      |
| `pa play music`   | `open -a iTunes && osascript -e 'tell application "iTunes" to play'`  |
| `pa pause music`  | `open -a iTunes && osascript -e 'tell application "iTunes" to pause'` |
| `pa close music`  | `osascript -e 'quit app "iTunes"'`                                    |
| `pa update pc`    | `sudo softwareupdate -l`                                              |
