# Social Gaming

### Makefile (Automation)
* The following commands can be executed from the root directory

|            Command            |                                                                   Description                                                                  |
|:-----------------------------:|:----------------------------------------------------------------------------------------------------------------------------------------------:|
| `make build-core-game-engine` | 1. Creates a new build directory <br><br>2. Runs cmake <br><br>3. Changes into build directory and runs nested makefile<br>                    |
| `make run-core-game-engine`   | 1. Executes the `core-game-engine` using `demo` binary<br><br>2. Uses `rock-paper-scissors.game` copied into `game-files` during the build<br> |
| `make clean`                  | 1. removes all the build directories                                                                                                           |

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

## Team Frobscottle Contributors 
- Andy 
- Mike
- Chirag
- Jerry
