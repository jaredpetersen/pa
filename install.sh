#!/bin/bash
# Install Personal Assistant

echo "Installing Personal Assistant..."
sudo cp ./pa/pa /usr/local/bin && \
sudo mkdir ~/.pa ; \
sudo cp ./pa/commands ./LICENSE ./README.md ~/.pa && \
sudo chmod -R 770 ~/.pa && \
export PATH=$PATH:/usr/local/bin && \
echo "Installation Complete"
