Setting Up XCode 11.7 for CS106b on macOS 1.15 Catalina
==================================================

Approach
--------

The assignment bundles don't work on newer versions of XCode/macOS because they depend on the bundled static "Stanford Portable Library for C++" helper library that seems to be compiled for older achitectures; and they include outdated XCode project files.

Rather than trying to fix the bundles the approach is to use them only the sourcecode for the assignments, and include the Stanford helper library into the XCode project manually. We will download and build the helper library directly, rather than rely on the bundle, to ensure it works with our system.

Build the Stanford Helper Library
---------------------------------

Some of the library depends on Java, so install a recent JDK and make sure the JAVA_HOME environment variable is set, e.g. by following [this](https://www.appsdeveloperblog.com/how-to-set-java_home-on-mac/).
Download and unzip the source code [cpplib.zip](https://cs.stanford.edu/people/eroberts/StanfordCPPLib/cpplib.zip) from [here](https://cs.stanford.edu/people/eroberts/StanfordCPPLib/)
Open Terminal
```
cd ~/Downloads/cpplib
make
```
This will put the statically compiled library in the `lib/` folder.
When I ran the built-in tests with `./TestStanfordCPPLib` the `getInteger()` function was broken - it would always say "Illegal integer format. Try again." no matter what the input. The fix for this is [here](https://stackoverflow.com/questions/25820964/why-does-this-simple-getinteger-function-cause-a-stream-failure), which is to edit `cpplib/src/simpio.cpp` and replace two instances of `istringstream stream(line);` with `istringstream stream(line + " ");`. Then rebuild with
```
make clean
make
```

Download an Assignment
----------------------

Use the download page [here](http://stanford.edu/class/archive/cs/cs106b/cs106b.1136/). This is the 2013 site, which seems more up to date than the original 2008 course materials (so assumed more likely to work with macOS10) but is not the "QT Ctreator" version which the course seems to have moved to for the most recent iterations. The assumption is the QT Creator content won't match up as well with the 2008 course material, but this may not be true.

Download and unzip [Assignment 1](http://stanford.edu/class/archive/cs/cs106b/cs106b.1136/assignments/Assignment1-xcode.zip), this is the "10.6 and 10.8 Files" version, but it should not matter as we're not depending on any precompiled libraries, or the XCode project file.

Start XCode 11.7
On the Welcome screen choose "Open another project..."
Open `Assignment1-xcode/1 - Consecutive Heads/Consecutive Heads.xcodeproj`
Hit the Play button to Build and Run, you should get this error:
`The linked library 'libStanfordCPPLib.a' is missing one or more architectures required by this target: x86_64.`. I think the .a file is compiled for a 32-bit Intel architecture.

Add the Stanford Library
------------------------

Go to the Project Navigator, open Resources folder, Right-click libStanfordCPPLib.a > Show File Inspector
In the inspector under location click the folder and change it to `cpplib/lib/libStanfordCPPLib.a`
Some parts of the project are still pointing to the old lib.
Open the project settings by clicking on the top level "ConsecutiveHeads" folder in the Project Navigator
Go to Build Settings
Go to User-Defined AND edit LIBRARY_SEARCH_PATHS_QUOTED_1 to point to the `cpplib/lib` directory.
Go to Search Paths and edit Library Search Paths, removing the $(inherited) entry and leaving in place the entry that points to the user-defined LIBRARY_SEARCH_PATHS_QUOTED_1.

Hit the Play button to Build and Run

The project should now build. If you get a linker error, go to the project settings again, Build Phases, Link Binary with Libraries, and add the new libStanfordCPPLib.a here.

Another approach - from Scratch
----------------

Create an XCode Command Line C++ project from scratch.
Add the `cpp/include/` directory to the Header Search Paths
Add the `cpp/lib/` directory to the Library Search Paths
In Build Phases, Link Binary with Libraries, and add the new libStanfordCPPLib.a here. Alternatively, add the .a file under Other Linker Flags by adding a `-lStanfordCPPLib` (the syntax is -l<lib> without a space).

