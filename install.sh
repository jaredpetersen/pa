#!/bin/bash
# Install Personal Assistant

echo "Installing Personal Assistant..."
sudo cp ./pa/pa /usr/local/bin && \
( sudo mkdir /var/pa ; sudo cp ./pa/commands ./LICENSE ./README.md /var/pa ) && \
export PATH=$PATH:/usr/local/bin && \
echo "Installation Complete"
