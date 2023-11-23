#******************************
# 		CONFIGURATIONS
#******************************

ROOT_DIR := $(pwd)
APP_DIR := app
BUILD_DIR := *build
TEST_DIR := app

#******************************
#	        CLIENT
#******************************

CLIENT_DIR := $(APP_DIR)/client
CLIENT_BUILD_DIR := client-build
CLIENT_TEST_DIR := $(CLIENT_DIR)/test

# Creates directory and runs cmake to build the project
build-client:
	@echo "[INFO] Building 'client'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(CLIENT_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(CLIENT_TEST_DIR) ; \
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

# Runs the test-suite
test-client:
	@echo "[INFO] client tests commencing..." ; \
	$(CLIENT_BUILD_DIR)/bin/tests-client

#******************************
# CLIENT SERVER COMMUNICATION
#******************************

# TODO

#******************************
#	   CORE GAME ENGINE
#******************************

CORE_GAME_ENGINE_DIR := $(APP_DIR)/core-game-engine
CORE_GAME_ENGINE_BUILD_DIR := core-game-engine-build
CORE_GAME_ENGINE_TEST_DIR := $(CORE_GAME_ENGINE_DIR)/test

# Creates directory and runs cmake to build the project
build-core-game-engine:
	@echo "[INFO] Building 'core-game-engine'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(CORE_GAME_ENGINE_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(CORE_GAME_ENGINE_TEST_DIR) ; \
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
	@echo "[INFO] core-game-engine tests commencing..." ; \
	$(CORE_GAME_ENGINE_BUILD_DIR)/bin/tests-core-game-engine


#******************************
# 		GAME CONTAINER
#******************************

# TODO

#******************************
# 	 GAME CONTAINER MANAGER
#******************************

# TODO


#******************************
#		SOCIAL GAMING
#******************************

SOCIAL_GAMING_DIR := $(APP_DIR)
SOCIAL_GAMING_BUILD_DIR := social-gaming-build

# Creates directory and runs cmake to build the project
build-social-gaming:
	@echo "[INFO] Building 'social-gaming'" ; \
	rm -rf $(SOCIAL_GAMING_BUILD_DIR) ; \
	mkdir $(SOCIAL_GAMING_BUILD_DIR) ; \
	cd $(SOCIAL_GAMING_BUILD_DIR) && cmake ../$(SOCIAL_GAMING_DIR)

# Compiles the C++ code for the project
compile-social-gaming:
	@echo "[INFO] Compiling 'social-gaming'" ; \
	$(MAKE) -C $(SOCIAL_GAMING_BUILD_DIR) --silent

# Executes the code
run-social-gaming:
	@echo "[INFO] Running 'social-gaming'" ; \
	$(SOCIAL_GAMING_BUILD_DIR)/bin/social-gaming

test-social-gaming:
	@echo "[INFO] all tests commencing..."
	$(SOCIAL_GAMING_BUILD_DIR)/core-game-engine/bin/tests-core-game-engine
	$(SOCIAL_GAMING_BUILD_DIR)/client/bin/tests-client


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


# [INFO]: Removes Build & Test artifacts
clean: 
	@echo "[INFO] Removing Build Directories..." ; \
	rm -rf *-build
	@echo "[INFO] Removing gtest from Test Directories..." ; \
	rm -rf $(CORE_GAME_ENGINE_TEST_DIR)/gtest
	rm -rf $(CLIENT_TEST_DIR)/gtest


# [INFO]: Build all the applications
all-build: build-core-game-engine build-client

# [INFO]: Compile all the applications
all-compile: compile-core-game-engine compile-client

# [INFO]: Runs all the tests
all-tests: test-core-game-engine