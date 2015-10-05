# Personal Assistant
Your teachable, personal computer assistant. Inspired by
[Hallie](https://github.com/mikemelch/hallie).

# Usage
The Personal Assistant (PA) program is a quick way to run programs and generally use your computer via the command line. If you can come up with a linux command or script, you can teach PA to use it.

### Demo
Coming Soon!

### Built in Commands
PA has two built-in commands to help you manage all of the things you want the program to do:
```
$ pa learn command
$ pa forget command
```

### Examples
Here are some things that you can teach your PA to do:

Tell you your IP address
```
$ pa whats my ip
> 192.168.1.165
```

Open programs
```
$ pa open browser
$ pa open word
$ pa open itunes
```

Play music
```
$ pa play music
$ pa pause music
```

# Install
### Easy Install
1. Download the code from GitHub with `git clone https://github.com/jaredpetersen/pa`
2. Navigate to the new directory and run the installation script with `.\install.sh`

### Advanced Install
1. Download the code from GitHub with `git clone https://github.com/jaredpetersen/pa`
2. Navigate to the pa folder within the cloned directory
3. Run `gcc pa.c -o pa` to compile the code yourself
4. Copy your compiled code to `/usr/local/bin` via `sudo cp ./pa /usr/local/bin`
5. Create a directory called `.pa` within your home directory with `sudo mkdir ~/.pa`
6. Copy only the supporting files from the `pa` folder into this new directory via `sudo cp ./pa/commands ./pa/LICENSE ./pa/README.md ~/.pa`
7. Change the file permissions to anything in `~/.pa` via `sudo chmod -R 770 ~/.pa`
8. Add the program to your filepath with `export PATH=$PATH:/usr/local/bin`
