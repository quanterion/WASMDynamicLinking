# WASMDynamicLinking
This is an example project of how to setup dynamic linking and loading for Web Assembly using Emscripten.

This project assumes you have emscripten already installed and setup. If you haven't set it up already, you follow the setup guide [here](https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install).
The scripts have been setup for Linux and MacOS, but they can also be run by windows, you can either just copy the commands from the script files and paste them in the terminal, or change the files from .sh to .bat and remove the `#!/bin/bash`.

## Testing
To test the building process, in linux or MacOS you can just run the scripts like `./CmakeGenerateAndBuild.sh` and `./CompileToWasm.sh`. Make sure to setup the emscripten environment in your terminal session beforehand, by running `./emsdk_env.sh` from the location where escripten is installed.
The windows process is the same, you need to run `emsdk_env.bat` from your emscripten install folder. Then copy the commands from the file you want to run or run the bat script.

When hosting the files to test your build, your hosting site needs COEP and COOP headers, otherwise dlopen is not allowed to load files. For this a script has been setup in the build folder. You can run `python3 Server.py` from the build folder to host the site, it will be hosted on port 8000.

## Finding issues
The example project has been setup with a few functions that will show you if a specific step during loading or executing is going wrong.
The normal output should look like what is shown below:
```
Loading wasm lib
Init during load
Handle: 161248
Found Symbol: _ZN4Calc3addEii
Finished loading, testing libraries!
Add 3 + 5 = 8
subtract 5 - 3 = 2
```

If something went wrong, you can check which error happened depending on the logs. You can also check the browser console to find out more info about the issue.

- If only `Loading wasm lib` and `Finished loading, testing libraries!` show up, the calc library failed to load, either the file couldn't be found or it wasn't allowed to be loaded due to something else, like pthreads not being enabled or allowed on the current site.
- If `Init during load` appears before `Loading wasm lib`, then the calc library was automatically loaded and not by dlopen.
- If the symbols weren't found, there likely isn't anything wrong, but the name is just mangled differently for your compilation then what is defined in main.cpp.
- If only the `Add` and `subract` lines are missing, it is likely that shared memory is not enabled or RTLD_GLOBAL was not used in dlopen.
