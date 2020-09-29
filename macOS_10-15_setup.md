Setting Up XCode 11.7 for CS106b on macOS 1.15 Catalina
==================================================

Approach
--------

The assignment bundles don't work on newer versions of XCode/macOS because they depend on the bundled static "Stanford Portable Library for C++" helper library that seems to be compiled for older achitectures; and they include outdated XCode project files.

We will re-compile the Stanford helper libraries ourselves, and drop them in as replacements for the old ones.

Build the Stanford Helper Library
---------------------------------

Some of the library depends on Java, so install a recent JDK and make sure the JAVA_HOME environment variable is set, e.g. by following [this](https://www.appsdeveloperblog.com/how-to-set-java_home-on-mac/).
Download and unzip the source code [cpplib.zip](https://cs.stanford.edu/people/eroberts/StanfordCPPLib/cpplib.zip) from [here](https://cs.stanford.edu/people/eroberts/StanfordCPPLib/)

### Fix a couple of issues with the source

You may find you don't need to do these steps, depending on your system, but it doesn't hurt to do them anyway:

* Navigate into cpplib
* Edit src/tests/unittest.cpp, replacing instances of `sin` with `str_in`. This prevents a name clash with an existing math library.
* Edit src/simpio.cpp, replacing instances of `istringstream(line)` with `istringstream(line + " ")`. See [here](https://stackoverflow.com/questions/25820964/why-does-this-simple-getinteger-function-cause-a-stream-failure) for details.

### Make the Library

Open Terminal
```
cd ~/Downloads/cpplib
make
```
This will put the statically compiled library in the `lib/` folder.


### Rearrange the files

The easiest way to make use of the newly-compiled Stanford helper library is to make a copy of it and rearrange it intothe equivalent file structure of the `StanfordCPPLib` directory that comes bundled with the assignments. Then it is simply a case of replacing the bundled `StanfordCPPLib` directory with the new one. This way, there's no need to re-point XCode to the libraries, as the project file is already set up to look for the `StanfordCPPLib` directory.

From having just run `make`:

```
cd ..
cp -R cpplib StanfordCPPLib
cd StanfordCPPLib
mv include/* .
mv lib/libStanfordCPPLib.a .
mv java/spl.jar .
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

### Link the Stanford Library

Copy your newly-compiled Stanford library `StanfordCPPLib` to the same folder where all your Assignment directories will live. Then, for each assignment (e.g. Assignment1-xcode) delete the old libraries and replace them with links to the newly compiled libraries:

```
cd Assignment1-xcode/1 - Consecutive Heads/
rm -r StanfordCPPLib
rm -r spl.jar
ln -s ../../StanfordCPPLib
ln -s ../../StanfordCPPLib/spl.jar
```


Another approach - from Scratch
----------------

Create an XCode Command Line C++ project from scratch.
Add the `<newlib>/include/` directory to the Header Search Paths
Add the `<newlib>/lib/` directory to the Library Search Paths
In Build Phases, Link Binary with Libraries, and add the new libStanfordCPPLib.a here. Alternatively, add the .a file under Other Linker Flags by adding a `-lStanfordCPPLib` (the syntax is -l<lib> without a space).

