#/bin/zsh
set -e

echo "Installing ArtSCII for MacOS\n"

# Make sure artscii is in the same dir
if [ ! -f ./artscii ]; then
    echo "Error: cannot find artscii"
    exit 1
fi

# Make sure homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Installing Homebrew"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi
echo "Homebrew Installed\n"

# Dependencies
echo "Installing dependencies"
brew install libpng ffmpeg &>/dev/null
echo "libpng installed\n"

# move to /usr/local/bin (probably on path)
echo "Moving executable to /usr/local/bin"
sudo mkdir -p /usr/local/bin
sudo rm -f /usr/local/bin/artscii
sudo cp ./artscii /usr/local/bin/artscii
chmod +x /usr/local/bin/artscii
echo "Move complete\n"

if command -v artscii &>/dev/null; then
    echo "Installation completed"
else
    echo "Installation failed"
    exit 1
fi

