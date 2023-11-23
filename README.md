# Social Gaming

### Makefile (Automation)
* The following commands can be executed from the root directory

|Client Commands|Description|
|:---|:---|
|`make build-client`|Creates a new build directory, then runs cmake|
|`make compile-client`|Compiles the `client` .cpp files|
|`make run-client`|Executes the `client` using `main` binary|

|Client Server Communication Commands|Description|
|:---|:---|
|`make build-client-server-communication`|Creates a new build directory, then runs cmake|
|`make compile-client-server-communication`|Compiles the `client-server-communication` .cpp files|
| `TODO` | Will need to talk to @Jerry/@Andy about integration|

|Core Game Engine Commands|Description|
|:---|:---|
|`make build-core-game-engine`|Creates a new build directory, then runs cmake|
|`make compile-core-game-engine`|Compiles the `core-game-engine` .cpp files|
|`make test-core-game-engine`|Executes the `core-game-engine` test suite (must be built and compiled)|

|Game Container Commands|Description|
|:---|:---|
|`make build-game-container`|Creates a new build directory, then runs cmake|
|`make compile-game-container`|Compiles the `game-container` .cpp files|
|`make test-game-container`|Executes the `game-container` test suite (must be built and compiled)|

|Game Container Manager Commands|Description|
|:---|:---|
|`make build-game-container-manager`|Creates a new build directory, then runs cmake|
|`make compile-game-container-manager`|Compiles the `game-container-manager` .cpp files|
|`make test-game-container-manager`|Executes the `game-container-manager` test suite (must be built and compiled)|

|Social Gaming (Integrated Application) Commands|Description|
|:---|:---|
|`make build-social-gaming`|Creates a new build directory, then runs cmake|
|`make compile-social-gaming`|Compiles the `social-gaming` .cpp files|
|`make test-social-gaming`|Executes the test suites for all the applications (must be built and compiled)|

|General Commands|Description|
|:---|:---|
|`all-build`  |Builds all the subdirectories in the Repository separately|
|`all-compile`|Compiles all the subdirectories in the Repository separately|
|`all-tests`  |Runs all Unit Tests for Repository (must be built and compiled) separately| 
|`make clean` |Removes all the build artifacts and gtest directories from test directories|

## Unit Tests
* Application(s) must be built prior (using `make build-{application}` or `make all-build`) -- this copies the `gtest` directory into the the location of the test-suite prior to making a build directory and running CMake on the application
### Steps:
1. `make build-{application}` or `make all-build`
2. `make compile-{application}` or `make all-compile`
3. `make test-{application}` or `make all-tests`

## Special note for unit tests in the client:
Run tests using CMake and Make.
Since we don't have a Makefile implementation for it,
this will eventually be changed to follow the format of having tests 
directly in their respective folders instead of the outer folder.


## Git Development 
### Git Setup
Make sure to 
- `git config user.name sfu_id`  
- `git config user.email sfu_id@sfu.ca`  
check that you have configured properly with `git config --list`

### Git Branches 
No development should be done directy on the master branch. 
Make a branch, push it to origin, then do a pull request.

After any pull request, do NOT delete the branch! They are needed to calculate code contribution.

### Git Commits 
Try to make every Commit an isolated work item. If you fix a bug in candy.cpp, and added a new test to the get_username() function, these should be in two different commits. 

In every commit message, provide a brief overview of the changes you made, and credit any contributors to that commit. For example, a commit message might look like: 
'Added unit tests for get_username(). Authors: Andy and Mike'


### Merge Requests
Before making a merge request to `master`, make sure to merge in remote master to the local feature branch you want to make a MR for.

This is to ensure there are no merge conflicts when trying to merge into master! 

## Running Client
When running the client and prompted to enter the name of the game configuration file, enter `../docs/rock-paper-scissors.game`. This file can be found in the docs folder at the root of the repository. 

## Team Frobscottle Contributors 
- Andy 
- Mike
- Chirag
- Jerry
- Kamal
- Misha
- Jack
