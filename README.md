# Social Gaming

### Makefile (Automation)
* The following commands can be executed from the root directory

|Core Game Engine Commands|Description|
|:---|:---|
|`make build-core-game-engine`|Creates a new build directory, then runs cmake|
|`make compile-core-game-engine`|Compiles the `core-game-engine` .cpp files|
|`make run-core-game-engine`|Executes the `core-game-engine` using `main` binary <br> Currently configured to use `rock-paper-scissors.game` copied into `game-files` during the build|
|`make test-core-game-engine`|Executes the `core-game-engine` test suite (must be built and compiled)|

|Client Commands|Description|
|:---|:---|
|`make build-client`|Creates a new build directory, then runs cmake|
|`make compile-client`|Compiles the `client` .cpp files|
|`make run-client`|Executes the `client` using `main` binary|

|General Commands|Description|
|:---|:---|
|`all-build`  |Builds all the subdirectories in the Repository|
|`all-compile`|Compiles all the subdirectories in the Repository|
|`all-tests`  |Runs all Unit Tests for Repository (must be built and compiled)| 
|`make clean` |Removes all the build artifacts and gtest directories from test directories|

## Unit Tests
* Application(s) must be built prior (using `make build-{application}` or `make all-build`) -- this copies the `gtest` directory into the the location of the test-suite prior to making a build directory and running CMake on the application
### Steps:
1. `make build-{application}` or `make all-build`
2. `make compile-{application}` or `make all-compile`
3. `make test-{application}` or `make all-tests`

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
