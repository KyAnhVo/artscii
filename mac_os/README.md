# Installing guide on MacOS
Expectation: **Apple Silicon MacOS**
## guide
Download the 2 files into a directory (need not be empty, but no conflict name),
open the terminal pointed to that file then run the code below:
```bash
sudo chmod +x ./install_script.sh
./install_script.sh
```
This should install your artscii program correctly to the /usr/local/bin/ directory.
You can then call `artscii [FILE] [-z zoom_amount] [-b brightness]` where zoom_amount
ranges from 1 to however large you like, and brightness is non-0, but preferably 0.3-2.2.
