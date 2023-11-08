#******************************
# 		CONFIGURATIONS
#******************************

ROOT_DIR := $(pwd)
BUILD_DIR := *build

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
#	        CLIENT
#******************************

CLIENT_DIR := client
CLIENT_BUILD_DIR := client-build

# Creates directory and runs cmake to build the project
build-client:
	@echo "[INFO] Building 'client'" ; \
	rm -rf $(CLIENT_BUILD_DIR) ; \
	mkdir $(CLIENT_BUILD_DIR) ; \
	cd $(CLIENT_BUILD_DIR) && cmake ../$(CLIENT_DIR)

# Compiles the C++ code for the project
compile-client:
	@echo "[INFO] Compiling 'client'" ; \
	$(MAKE) -C $(CLIENT_BUILD_DIR) --silent

# Executes the code
run-client:
	@echo "[INFO] Running 'client'" ; \
	$(CLIENT_BUILD_DIR)/client

#******************************
#	        TEST
#******************************
# This needs to integrate client and core-game-engine

TEST_DIR := test
TEST_BUILD_DIR := test-build

# Creates directory and runs cmake to build the project
build-test:
	@echo "[INFO] Building 'test'" ; \
	rm -rf $(TEST_BUILD_DIR) ; \
	mkdir $(TEST_BUILD_DIR) ; \
	cd $(TEST_BUILD_DIR) && cmake ../$(TEST_DIR)

# Compiles the C++ code for the project
compile-test:
	@echo "[INFO] Compiling 'test'" ; \
	$(MAKE) -C $(TEST_BUILD_DIR) --silent

# Executes the code
run-test:
	@echo "[INFO] Running 'test'" ; \
	$(TEST_BUILD_DIR)/test


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
clean: 
	@echo "[INFO] Removing Build Directories..." ; \
	rm -rf $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	rm -rf $(BUILD_DIR)


# [INFO]: Runs all the tests
all-tests: test-core-game-engine