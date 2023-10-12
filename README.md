# Social Gaming

### Makefile (Automation)
* The following commands can be executed from the root directory

|            Command             |                                                                   Description                                                                  |
|--------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------|
| `make build-core-game-engine`  | <br>1. Creates a new build directory <br>2. Runs cmake <br><br>                                             |
| `make compile-core-game-engine`| <br>1. Compiles the `core-game-engine` .cpp files<br><br>
|  `make run-core-game-engine`   | <br>1. Executes the `core-game-engine` using `main` binary<br>2. Currently configured to use `rock-paper-scissors.game` copied into `game-files` during the build<br><br> |
| `make clean`                   | <br>1. removes all the build directories<br>                                                                                                           |

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
