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
	mkdir -p $(CLIENT_BUILD_DIR) ; \
	cd $(CLIENT_BUILD_DIR) && cmake ../$(CLIENT_DIR)

# Compiles the C++ code for the project
compile-client:
	@echo "[INFO] Compiling 'client'" ; \
	$(MAKE) -C $(CLIENT_BUILD_DIR) --silent

# Runs the test-suite
test-client:
	@echo "[INFO] client tests commencing..." ; \
	cd $(CLIENT_BUILD_DIR) && bin/tests-client

#******************************
# CLIENT SERVER COMMUNICATION
#******************************
# [INFO] No test suite for this module

CLIENT_SERVER_COMMUNICATION_DIR := $(APP_DIR)/client-server-communication
CLIENT_SERVER_COMMUNICATION_BUILD_DIR := client-server-communication-build

# Creates directory and runs cmake to build the project
build-client-server-communication:
	@echo "[INFO] Building 'client-server-communication'" ; \
	mkdir -p $(CLIENT_SERVER_COMMUNICATION_BUILD_DIR) ; \
	cd $(CLIENT_SERVER_COMMUNICATION_BUILD_DIR) && cmake ../$(CLIENT_SERVER_COMMUNICATION_DIR)

# Compiles the C++ code for the project
compile-client-server-communication:
	@echo "[INFO] Compiling 'client-server-communication'" ; \
	$(MAKE) -C $(CLIENT_SERVER_COMMUNICATION_BUILD_DIR) --silent


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
	mkdir -p $(CORE_GAME_ENGINE_BUILD_DIR) ; \
	cd $(CORE_GAME_ENGINE_BUILD_DIR) && cmake ../$(CORE_GAME_ENGINE_DIR)

# Compiles the C++ code for the project
compile-core-game-engine:
	@echo "[INFO] Compiling 'core-game-engine'" ; \
	$(MAKE) -C $(CORE_GAME_ENGINE_BUILD_DIR) --silent

# Runs the test-suite
test-core-game-engine:
	@echo "[INFO] core-game-engine tests commencing..." ; \
	cd $(CORE_GAME_ENGINE_BUILD_DIR) && bin/tests-core-game-engine


#******************************
# 		GAME CONTAINER
#******************************

GAME_CONTAINER_DIR := $(APP_DIR)/game-container
GAME_CONTAINER_BUILD_DIR := game-container-build
GAME_CONTAINER_TEST_DIR := $(GAME_CONTAINER_DIR)/test

# Creates directory and runs cmake to build the project
build-game-container:
	@echo "[INFO] Building 'game-container'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(GAME_CONTAINER_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(GAME_CONTAINER_TEST_DIR) ; \
	mkdir -p $(GAME_CONTAINER_BUILD_DIR) ; \
	cd $(GAME_CONTAINER_BUILD_DIR) && cmake ../$(GAME_CONTAINER_DIR)

# Compiles the C++ code for the project
compile-game-container:
	@echo "[INFO] Compiling 'game-container'" ; \
	$(MAKE) -C $(GAME_CONTAINER_BUILD_DIR) --silent

# Runs the test-suite
test-game-container:
	@echo "[INFO] game-container tests commencing..." ; \
	$(GAME_CONTAINER_BUILD_DIR)/bin/tests-game-container

#******************************
# 	 GAME CONTAINER MANAGER
#******************************

GAME_CONTAINER_MANAGER_DIR := $(APP_DIR)/game-container-manager
GAME_CONTAINER_MANAGER_BUILD_DIR := game-container-manager-build
GAME_CONTAINER_MANAGER_TEST_DIR := $(GAME_CONTAINER_MANAGER_DIR)/test

# Creates directory and runs cmake to build the project
build-game-container-manager:
	@echo "[INFO] Building 'game-container-manager'" ; \
	echo "[SETUP] Copying '$(TEST_DIR)/gtest' directory to $(GAME_CONTAINER_MANAGER_TEST_DIR)" ; \
	cp -r $(TEST_DIR)/gtest $(GAME_CONTAINER_MANAGER_TEST_DIR) ; \
	mkdir -p $(GAME_CONTAINER_MANAGER_BUILD_DIR) ; \
	cd $(GAME_CONTAINER_MANAGER_BUILD_DIR) && cmake ../$(GAME_CONTAINER_MANAGER_DIR)

# Compiles the C++ code for the project
compile-game-container-manager:
	@echo "[INFO] Compiling 'game-container-manager'" ; \
	$(MAKE) -C $(GAME_CONTAINER_MANAGER_BUILD_DIR) --silent

# Executes the code
run-game-container-manager:
	@echo "[INFO] Running 'game-container-manager'" ; \
	$(GAME_CONTAINER_MANAGER_BUILD_DIR)/game-container-manager

# Runs the test-suite
test-game-container-manager:
	@echo "[INFO] game-container-manager tests commencing..." ; \
	cd $(GAME_CONTAINER_MANAGER_BUILD_DIR) && bin/tests-game-container-manager


#******************************
#		SOCIAL GAMING
#******************************

SOCIAL_GAMING_DIR := $(APP_DIR)
SOCIAL_GAMING_BUILD_DIR := social-gaming-build

# Creates directory and runs cmake to build the project
build-social-gaming:
	@echo "[INFO] Building 'social-gaming'" ; \
	mkdir -p $(SOCIAL_GAMING_BUILD_DIR) ; \
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
	cd $(SOCIAL_GAMING_BUILD_DIR) ; \
	bin/tests-client ; \
	bin/tests-core-game-engine ; \
	bin/tests-game-container ; \
	bin/tests-game-container-manager ; \


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
	$(info 1. build-social-gaming)
	$(info 2. compile-social-gaming)
	$(info 3. test-{{ name }})
	$(info *************************************)


# [INFO]: Removes Build & Test artifacts
clean: 
	@echo "[INFO] Removing Build Directories..."
	@rm -rf *-build
	@echo "[INFO] Removing gtest from Directories..."
	@rm -rf $(CLIENT_TEST_DIR)/gtest
	@rm -rf $(CORE_GAME_ENGINE_TEST_DIR)/gtest
	@rm -rf $(GAME_CONTAINER_TEST_DIR)/gtest
	@rm -rf $(GAME_CONTAINER_MANAGER_TEST_DIR)/gtest
	
# [INFO]: Build all the applications separately 
all-build: build-client build-client-server-communication build-core-game-engine build-game-container build-game-container-manager build-social-gaming

# [INFO]: Compile all the applications separately 
all-compile: compile-client compile-client-server-communication compile-core-game-engine compile-game-container compile-game-container-manager compile-social-gaming

# [INFO]: Runs all the tests separately 
all-tests: test-client test-core-game-engine test-game-container test-game-container-manager test-social-gaming