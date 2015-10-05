#!/bin/bash
# Uninstall Personal Assistant

echo "Uninstalling Personal Assistant..."
sudo rm /usr/local/bin/pa && \
sudo rm -r ~/.pa && \
export PATH=$PATH:/usr/local/bin && \
echo "Uninstallation Complete"
