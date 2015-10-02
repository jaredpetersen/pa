# Personal Assistant
Your teachable, personal computer assistant. Inspired by
[Hallie](https://github.com/mikemelch/hallie).

# Install
### Easy Install
1. Download the code from GitHub with `git clone https://github.com/jaredpetersen/pa`
2. Navigate to the new directory and run the installation script with `.\install.sh`

### Advanced Install
1. Download the code from GitHub with `git clone https://github.com/jaredpetersen/pa`
2. Navigate to the pa folder within the cloned directory
3. Run `gcc pa.c -o pa` to compile the code yourself
4. Copy your compiled code to `/usr/local/bin` via `sudo cp ./pa /usr/local/bin`
5. Create a directory called `pa` within `/var/` with `sudo mkdir /var/pa`
6. Copy the only the supporting files from the `pa` folder into this new directory via `sudo cp ./pa/commands ./pa/LICENSE ./pa/README.md /var/pa`
7. Add the program to your filepath with `export PATH=$PATH:/usr/local/bin`
