#******************************
# 		CONFIGURATIONS
#******************************

ROOT_DIR := $(pwd)

#******************************
#	   CORE GAME ENGINE
#******************************

CORE_GAME_ENGINE_DIR := core-game-engine
CORE_GAME_ENGINE_BUILD_DIR := core-game-engine-build

# Creates directory and runs cmake to build the project
build-core-game-engine:
	@echo "[INFO] Building 'core-game-engine'" ; \
	rm -rf $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	mkdir $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	cd $(CORE_GAME_ENGINE_BUILD_DIR) && cmake ../$(CORE_GAME_ENGINE_DIR)

# Compiles the C++ code for the project
compile-core-game-engine:
	@echo "[INFO] Compiling 'core-game-engine'" ; \
	$(MAKE) -C $(CORE_GAME_ENGINE_BUILD_DIR) --silent

# Executes the code
run-core-game-engine:
	@echo "[INFO] Running 'core-game-engine'" ; \
	$(CORE_GAME_ENGINE_BUILD_DIR)/bin/main $(CORE_GAME_ENGINE_BUILD_DIR)/game-files/rock-paper-scissors.game

# Runs the test-suite
test-core-game-engine:
	@echo "TODO: core-game-engine testing..."


#******************************
# 			GENERIC
#******************************

# [INFO]: Runs by default if 'make' has no target 
all:
	$(info 'all' is disable by default...)
	$(info 'make help')


# [INFO]: Display helpful information in CLI
help:
	$(info [INFO] To execute commands, type 'make' followed by any of commands below:)
	$(info *************************************)
	$(info 1. build-{{ name }})
	$(info 2. compile-{{ name }})
	$(info 3. run-{{ name }})
	$(info 4. test-{{ name }})
	$(info *************************************)


# [INFO]: Removes Build Directories
clean-core-game-engine: 
	@echo "[INFO] Removing Build Directories..." ; \
	rm -rf $(CORE_GAME_ENGINE_BUILD_DIR)


# [INFO]: Runs all the tests
all-tests: test-core-game-engine