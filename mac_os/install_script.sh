#/bin/zsh
set -e

echo "Installing ArtSCII for MacOS\n"

# Make sure homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Installing Homebrew"
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi
echo "Homebrew Installed\n"

# libpng
echo "Installing libpng"
brew install libpng &>/dev/null
echo "libpng installed\n"

# ffmpeg
echo "Installing ffmpeg"
brew install ffmpeg &>/dev/null
echo "ffmpeg installed\n"

# move to /usr/local/bin (probably on path)
echo "Moving executable to /usr/local/bin"
sudo mkdir -p /usr/local/bin
sudo rm -f /usr/local/bin/artscii
sudo cp ./artscii /usr/local/bin/artscii
chmod +x /usr/local/bin/artscii
echo "Move complete\n"

echo "Finished installation\n"
