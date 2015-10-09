# Personal Assistant
Your teachable, personal computer assistant. Written in C, compatible with any Unix-based operating system.

## Usage
The Personal Assistant (PA) program is a quick way to run programs and generally use your computer via the command line. If you can come up with a linux command or script, you can teach PA to use it.

### Built in Commands

![Play/Pause Music GIF](https://github.com/jaredpetersen/pa/raw/master/documentation/gifs/learncommand.gif)

You need to teach your PA everything you want it to do, which you can accomplish by running `pa learn command`. You will then be prompted for the name of the command that you would like to teach it and then the linux command that you want it to run.

If you want your PA to forget a certain command, just run `pa forget command` and give it the name of the command that you would like it to forget when prompted.

### Examples
Here are some things that you can teach your PA to do:

**Open/Close Programs**

![Open Programs GIF](https://github.com/jaredpetersen/pa/raw/master/documentation/gifs/app.gif)
```
$ pa open browser
$ pa close browser
$ pa open word
$ pa close word
```

**Play Music**

![Play/Pause Music GIF](https://github.com/jaredpetersen/pa/raw/master/documentation/gifs/music.gif)
```
$ pa play music
$ pa pause music
```

An expanded list of sample PA commands that you might want to use and their related linux commands can be found in the `documentation` folder.

## Installation
### Easy Install
1. Download the code from GitHub with `git clone https://github.com/jaredpetersen/pa`
2. Navigate to the new directory and run the installation script with `.\install.sh`

### Advanced Install
1. Download the code from GitHub with `git clone https://github.com/jaredpetersen/pa`
2. Navigate to the pa folder within the cloned directory
3. Run `gcc pa.c -o pa -std=gnu99` to compile the code yourself
4. Copy your compiled code to `/usr/local/bin` via `sudo cp ./pa /usr/local/bin`
5. Create a directory called `.pa` within your home directory with `sudo mkdir ~/.pa`
6. Copy only the supporting files from the `pa` folder into this new directory via `sudo cp ./pa/commands ./pa/LICENSE ./pa/README.md ~/.pa`
7. Change the file permissions to anything in `~/.pa` via `sudo chmod -R 777 ~/.pa/*`
8. Add the program to your filepath with `export PATH=$PATH:/usr/local/bin`
